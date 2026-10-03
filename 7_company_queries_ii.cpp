// vicfred
// https://cses.fi/problemset/task/1688
// Find the deepest common ancestor of two employees.
#include <cstdint>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int main() {
  int64_t n, queries;
  cin >> n >> queries;

  // Column j stores ancestors 2^j edges above a vertex.
  // These columns cover every possible depth in the tree.
  int64_t LOG = 1;
  while ((int64_t{1} << LOG) <= n) {
    LOG += 1;
  }

  // The input gives each employee's boss. Store both
  // directions so BFS can establish depths from the root.
  vector tree(n + 1, vector<int64_t>());
  for (int64_t i = 2; i <= n; ++i) {
    int64_t e;
    cin >> e;

    tree[i].push_back(e);
    tree[e].push_back(i);
  }

  // up[u][j] is 0 when that ancestor does not exist.
  // depth[u] counts edges from employee 1 to u.
  vector up(n + 1, vector<int64_t>(LOG));
  vector<int64_t> depth(n + 1, -1);
  queue<int64_t> q;

  depth[1] = 0;
  q.push(1);

  // Discover each employee once and store its parent
  // as the jump of length one.
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

  // Two jumps of length 2^(j-1) make a jump of 2^j.
  // Earlier columns are ready before later ones.
  // Row 0 stays zero, including above the root.
  for (int64_t j = 1; j < LOG; ++j) {
    for (int64_t u = 1; u <= n; ++u) {
      int64_t middle = up[u][j - 1];
      up[u][j] = up[middle][j - 1];
    }
  }

  for (int64_t query = 0; query < queries; ++query) {
    int64_t a, b;
    cin >> a >> b;

    // Keep b at least as deep as a.
    if (depth[a] > depth[b]) {
      swap(a, b);
    }

    // Decompose the depth difference into powers of two.
    // Both vertices have equal depth after these jumps.
    int64_t delta = depth[b] - depth[a];
    for (int64_t j = 0; j < LOG; ++j) {
      if ((delta & (int64_t{1} << j)) != 0) {
        b = up[b][j];
      }
    }

    // One employee may be an ancestor of the other.
    if (a == b) {
      cout << a << endl;
      continue;
    }

    // Keep a and b distinct and at equal depth, strictly
    // below their common ancestor. Take the largest jumps
    // that leave them on separate branches.
    for (int64_t j = LOG - 1; j >= 0; --j) {
      if (up[a][j] != up[b][j]) {
        a = up[a][j];
        b = up[b][j];
      }
    }

    // No one-edge jump can keep them distinct: their
    // shared parent is the lowest common ancestor.
    cout << up[a][0] << endl;
  }

  return 0;
}
