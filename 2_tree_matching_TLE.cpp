// vicfred
// https://cses.fi/problemset/task/1130
// Find the most edges with no shared endpoints.
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// Intentional TLE teaching version: O(n^2) worst-case time.
// Each candidate rescans the other children for clarity.
// Total space is O(n), including the recursion stack.
// A long chain may also exhaust the call stack.
//
// dp[u][matched_to_parent] counts matching edges entirely
// inside u's subtree. The edge to its parent is excluded.
// dp[u][0]: u may match with no child or exactly one child.
// dp[u][1]: u is matched to its parent; no child is allowed.
void dfs(int64_t u, int64_t parent,
         const vector<vector<int64_t>> &graph,
         vector<vector<int64_t>> &dp) {
  // Complete both states of every child before using them.
  for (int64_t v : graph[u]) {
    if (v == parent) {
      continue;
    }
    dfs(v, u, graph, dp);
  }

  // Select no edge from u to a child. Each child can then
  // choose its own matching without being occupied by u.
  int64_t S = 0;
  for (int64_t v : graph[u]) {
    if (v == parent) {
      continue;
    }
    S += dp[v][0];
  }

  // An occupied u has no other option. An unoccupied u
  // starts with this option before trying each child.
  // For a leaf, S is zero and both states remain zero.
  dp[u][1] = S;
  dp[u][0] = S;
  for (int64_t v : graph[u]) {
    if (v == parent) {
      continue;
    }

    // Select (u, v): count this edge here, and prevent v
    // from also matching with one of its own children.
    int64_t candidate = 1 + dp[v][1];

    // Other child subtrees have disjoint vertices, so add
    // all their answers. Their parent edges stay unused.
    // This repeated summation is deliberately retained.
    for (int64_t w : graph[u]) {
      if (w == parent || w == v) {
        continue;
      }
      candidate += dp[w][0];
    }

    // Compare complete alternatives, each using at most
    // one child edge incident to u.
    dp[u][0] = max(dp[u][0], candidate);
  }
}

int main() {
  int64_t n;
  cin >> n;

  vector graph(n + 1, vector<int64_t>());
  for (int64_t i = 1; i < n; ++i) {
    int64_t a, b;
    cin >> a >> b;

    // Input edges are undirected; DFS determines parents.
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  vector dp(n + 1, vector<int64_t>(2));

  // Root at 1. Vertex 0 is only a no-parent sentinel.
  dfs(1, 0, graph, dp);

  // The root has no parent, so it starts unoccupied.
  cout << dp[1][0] << endl;

  return 0;
}
