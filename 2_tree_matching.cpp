// vicfred
// https://cses.fi/problemset/task/1130
// Find the most edges with no shared endpoints.
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// dp[u][matched_to_parent] is the maximum matching size
// inside u's subtree, excluding the edge to its parent.
// State 0: u may match with no child or exactly one child.
// State 1: u is matched to its parent and cannot match
// any child. Matches further down remain allowed.
//
// Each adjacency list is scanned a constant number of
// times: O(n) total time and O(n) total space.
// Recursion depth is the tree height; a long chain may
// exhaust the call stack.
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
  // Child subtrees are disjoint, so add their answers.
  int64_t S = 0;
  for (int64_t v : graph[u]) {
    if (v == parent) {
      continue;
    }
    S += dp[v][0];
  }

  // State 1 allows only this option. State 0 starts with
  // it before considering a match with each child.
  // For a leaf, S is zero and both states remain zero.
  dp[u][1] = S;
  dp[u][0] = S;
  for (int64_t v : graph[u]) {
    if (v == parent) {
      continue;
    }

    // Select (u, v), counting that edge with the added 1.
    // S already includes dp[v][0]; replace it with
    // dp[v][1], since v is now matched to its parent.
    // All other child contributions remain unchanged.
    // Reusing S avoids rescanning siblings per candidate.
    int64_t candidate = 1 + dp[v][1] + S - dp[v][0];

    // Keep the best complete option, selecting at most
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

  // The root has no parent, so use the unoccupied state.
  cout << dp[1][0] << endl;

  return 0;
}
