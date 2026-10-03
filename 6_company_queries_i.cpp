// vicfred
// https://cses.fi/problemset/task/1687
// Find an employee's ancestor a given number of levels up.
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
  int64_t n, queries;
  cin >> n >> queries;

  // Store both directions so BFS can root the tree at 1.
  vector tree(n + 1, vector<int64_t>());
  for (int64_t i = 2; i <= n; ++i) {
    int64_t e;
    cin >> e;
    tree[i].push_back(e);
    tree[e].push_back(i);
  }

  // Column j represents a jump of 2^j parent edges.
  // LOG columns can represent every depth below n.
  int64_t LOG = 1;
  while ((int64_t{1} << LOG) <= n) {
    LOG += 1;
  }

  // up[u][j] is u's ancestor 2^j edges above it.
  // Vertex 0 means that ancestor does not exist.
  vector<vector<int64_t>> up(n + 1, vector<int64_t>(LOG));
  vector<int64_t> depth(n + 1, -1);

  // BFS establishes each depth and the immediate parent.
  // A depth of -1 means the vertex is still unvisited.
  queue<int64_t> q;
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

  // Join two jumps of 2^(j-1) edges to make one
  // jump of 2^j edges. Earlier columns are ready first.
  // Row 0 stays zero, even for jumps beyond the root.
  for (int64_t j = 1; j < LOG; ++j) {
    for (int64_t u = 1; u <= n; ++u) {
      int64_t middle = up[u][j - 1];
      up[u][j] = up[middle][j - 1];
    }
  }

  for (int64_t i = 0; i < queries; ++i) {
    int64_t u, k;
    cin >> u >> k;

    // Depth counts the edges available before reaching
    // the root. This also handles very large values of k.
    if (k > depth[u]) {
      cout << -1 << endl;
      continue;
    }

    // Write k as a sum of powers of two. Each set bit
    // moves from the current vertex by exactly 2^j edges.
    // When k is zero, u remains its own zeroth ancestor.
    for (int64_t j = 0; j < LOG; ++j) {
      if ((k & (int64_t{1} << j)) != 0) {
        u = up[u][j];
      }
    }
    cout << u << endl;
  }

  return 0;
}
