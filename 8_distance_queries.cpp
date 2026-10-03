// vicfred
// https://cses.fi/problemset/task/1135
// Find the number of edges between pairs of tree vertices.
#include <cstdint>
#include <iostream>
#include <queue>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

int main() {
  // Collect answers and write them together at the end.
  ostringstream output;
  int64_t n, queries;
  cin >> n >> queries;

  // up[u][j] will jump 2^j edges towards the root.
  // These columns cover every possible tree depth.
  int64_t LOG = 1;
  while ((int64_t{1} << LOG) <= n) {
    LOG += 1;
  }

  vector tree(n + 1, vector<int64_t>());
  for (int64_t i = 1; i <= n - 1; ++i) {
    int64_t a, b;
    cin >> a >> b;

    tree[a].push_back(b);
    tree[b].push_back(a);
  }

  // Vertex 0 represents a missing ancestor.
  // A depth of -1 means the vertex is unvisited.
  vector up(n + 1, vector<int64_t>(LOG));
  vector<int64_t> depth(n + 1, -1);
  queue<int64_t> q;

  // Root the tree at 1. BFS records each vertex's
  // depth and its immediate parent in up[u][0].
  depth[1] = 0;
  q.push(1);

  while (!q.empty()) {
    int64_t u = q.front();
    q.pop();

    for (int64_t v : tree[u]) {
      if (depth[v] != -1) {
        continue;
      }
      depth[v] = depth[u] + 1;
      up[v][0] = u;
      q.push(v);
    }
  }

  // Two jumps of length 2^(j-1) form one of length 2^j.
  // Earlier columns are complete before later ones.
  for (int64_t j = 1; j < LOG; ++j) {
    for (int64_t u = 1; u <= n; ++u) {
      int64_t middle = up[u][j - 1];
      up[u][j] = up[middle][j - 1];
    }
  }

  for (int64_t query = 1; query <= queries; ++query) {
    int64_t a, b;
    cin >> a >> b;

    // Keep b at least as deep as a. Save the original
    // endpoint depths before either vertex is moved.
    if (depth[a] > depth[b]) {
      swap(a, b);
    }

    int64_t depth_a = depth[a];
    int64_t depth_b = depth[b];

    // Lift b by the depth difference, one jump per set
    // bit. Afterwards a and b have the same depth.
    int64_t delta = depth[b] - depth[a];
    for (int64_t j = 0; j < LOG; ++j) {
      if ((delta & (int64_t{1} << j)) != 0) {
        b = up[b][j];
      }
    }

    // If b has reached a, a is their common ancestor.
    int64_t lca = a;
    if (a != b) {
      // Move lca and b together while their ancestors
      // remain different. They stay at the same depth
      // and strictly below their common ancestor.
      for (int64_t j = LOG - 1; j >= 0; --j) {
        if (up[lca][j] != up[b][j]) {
          lca = up[lca][j];
          b = up[b][j];
        }
      }
      // Their parents now coincide at the LCA.
      lca = up[lca][0];
    }

    // The unique path climbs to the LCA and descends
    // to the other endpoint. Depth differences count edges.
    output << depth_a + depth_b - 2 * depth[lca] << '\n';
  }

  cout << output.str();

  return 0;
}
