// vicfred
// https://cses.fi/problemset/task/1674
// Count each employee's direct and indirect subordinates.
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// Complete the answers for u and every descendant of u.
void dfs(int64_t u, const vector<vector<int64_t>> &graph,
         vector<int64_t> &subordinates) {
  for (int64_t v : graph[u]) {
    // Finish the child's subtree before using its answer.
    dfs(v, graph, subordinates);

    // Count the child itself and everyone below it.
    // Child subtrees are disjoint, so nobody is counted
    // twice.
    subordinates[u] += 1 + subordinates[v];
  }
  // A leaf keeps its initial answer of zero.
}

int main() {
  int64_t n;
  cin >> n;

  // Edges go from boss to child; employee 0 is the root.
  vector graph(n, vector<int64_t>());
  for (int64_t i = 1; i < n; ++i) {
    int64_t p;
    cin >> p;

    // Convert the boss to our zero-based indexing.
    p -= 1;
    graph[p].push_back(i);
  }

  vector<int64_t> subordinates(n, 0);

  // Every non-root employee has exactly one parent.
  // One traversal reaches everyone exactly once.
  dfs(0, graph, subordinates);

  for (int64_t count : subordinates) {
    cout << count << " ";
  }
  cout << endl;

  return 0;
}
