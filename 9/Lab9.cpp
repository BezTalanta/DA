#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using matrix = vector<vector<long long>>;

const long long MAX_CAP = 1000 * 1000 * 1000;

class Graph {
public:
    Graph(int _n, int _m) {
        n = _n;
        m = _m;
        capacity.resize(n, vector<long long>(n));
        adjacency_list.resize(n); // Список смежности
    }

    void AddEdge(int from, int to, int cap) {
        capacity[from][to] += cap;
        adjacency_list[from].push_back(to);
        adjacency_list[to].push_back(from);
    }

    long long TrySaturation(int start, int finish, vector<int> &parent,
                            vector<bool> &used, long long cur_flow) { // Проверка насыщенности
        parent[start] = -1;
        used.assign(n, false);
        queue<int> q;
        q.push(start);
        used[start] = true;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto &to : adjacency_list[cur]) {
                long long remainder = capacity[cur][to];
                if (remainder <= 0 || used[to] == true) {
                    continue;
                }
                parent[to] = cur;
                used[to] = true;
                cur_flow = min(cur_flow, remainder); // Текущий поток
                if (to == finish) {
                    return cur_flow;
                }
                q.push(to);
            }
        }
        return 0;
    }

    long long FindMaxFlow(int start, int finish) {
        long long maxFlow = 0;
        long long add = 1;
        vector<int> parent(n, -1);
        vector<bool> used(n);
        while (add > 0) {
            add = TrySaturation(start, finish, parent, used, MAX_CAP);
            maxFlow += add;
            for (int cur = finish; parent[cur] != -1; cur = parent[cur]) {
                capacity[parent[cur]][cur] -= add;
                capacity[cur][parent[cur]] += add;
            }
        }
        return maxFlow;
    }

private:
    int n;
    int m;
    matrix capacity;
    matrix adjacency_list;
};

int main() {
    int n; // Вершин
    int m; // Ребер
    cin >> n >> m;

    Graph graph(n, m);

    for (int i = 0; i < m; ++i) {
        int from;
        int to;
        int cap;
        cin >> from >> to >> cap;
        --from;
        --to;
        graph.AddEdge(from, to, cap);
    }

    int start = 0;
    int finish = n - 1;

    cout << graph.FindMaxFlow(start, finish) << "\n";

    return 0;
}