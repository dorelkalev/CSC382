#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct node {
    int vertex;
    node* next;
    node(int v = 0) : vertex(v), next(nullptr) {}
};

class Graph {
private:
    int n;               
    int e;               
    node* headnodes;     
    vector<bool> visited;
    vector<int> parent;
    vector<pair<int,int>> cycleEdges;
    bool cycleFound;

    bool dfsCycle(int v) {
        visited[v] = true;
        for (node* adj = headnodes[v].next; adj; adj = adj->next) {
            int u = adj->vertex;
            if (!visited[u]) {
                parent[u] = v;
                if (dfsCycle(u))
                    return true;
            }
            else if (u != parent[v] && cycleEdges.empty()) {
                int curr = v;
                cycleEdges.emplace_back(v, u);
                while (curr != u) {
                    int p = parent[curr];
                    cycleEdges.emplace_back(p, curr);
                    curr = p;
                }
                return true;
            }
        }
        return false;
    }

public:
    Graph(int nodes) : n(nodes), e(0), cycleFound(false) {
        headnodes = new node[n];
        for (int i = 0; i < n; i++) {
            headnodes[i] = node(i);
        }
    }

    ~Graph() {
        for (int i = 0; i < n; i++) {
            node* cur = headnodes[i].next;
            while (cur) {
                node* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
        delete[] headnodes;
    }

    void Creates(int edges) {
        e = edges;
        cout << "Enter each edge as two vertex indices (u v), 0-based:" << endl;
        for (int i = 0; i < e; i++) {
            int u, v;
            cin >> u >> v;
            node* nu = new node(v);
            nu->next = headnodes[u].next;
            headnodes[u].next = nu;
            node* nv = new node(u);
            nv->next = headnodes[v].next;
            headnodes[v].next = nv;
        }
    }

    void analyze() {
        visited.assign(n, false);
        parent.assign(n, -1);

        int compCount = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                compCount++;
                dfsCycle(i);
            }
        }
        cout << "Number of connected components: " << compCount << endl;
          
        if (!cycleEdges.empty()) {
            cout << "Cycle: ";
            for (size_t i = 0; i < cycleEdges.size(); i++) {
                auto &pr = cycleEdges[i];
                cout << "(" << pr.second << "," << pr.first << ")";
                if (i + 1 < cycleEdges.size()) cout << ", ";
            }
            cout << endl;
        } else {
            cout << "No cycle found in the graph." << endl;
        }
    }
};

int main() {
    int nodes, edges;
    cout << "Enter number of vertices: ";
    cin >> nodes;
    cout << "Enter number of edges: ";
    cin >> edges;

    Graph g(nodes);
    g.Creates(edges);
    g.analyze();

    return 0;
}
