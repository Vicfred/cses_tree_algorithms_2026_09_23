// vicfred
// https://cses.fi/problemset/task/1137
// Update vertex values and find sums of rooted subtrees.
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct FenwickTree {
private:
  // Position zero is unused.
  // fenwick[i] sums the block [i - (i & -i) + 1, i].
  vector<int64_t> fenwick;

public:
  // Represent n zero values. Time and space: O(n).
  explicit FenwickTree(int64_t n) : fenwick(n + 1) {
  }

  // Input is 0-indexed; operations are 1-indexed.
  // Build in O(n) time using O(n) space.
  explicit FenwickTree(const vector<int64_t> &values)
      : fenwick(values.size() + 1) {
    int64_t n = static_cast<int64_t>(values.size());

    for (int64_t i = 1; i <= n; ++i) {
      // Earlier blocks may already contribute here.
      fenwick[i] += values[i - 1];

      // This block is complete; pass it to its parent.
      int64_t parent = i + (i & -i);
      if (parent <= n) {
        fenwick[parent] += fenwick[i];
      }
    }
  }

  // Add delta at position i, where 1 <= i <= n.
  // Time: O(log n).
  void update(int64_t i, int64_t delta) {
    // Visit every stored block containing this position.
    while (i < static_cast<int64_t>(fenwick.size())) {
      fenwick[i] += delta;
      i += i & -i;
    }
  }

  // Sum [1, i], where 0 <= i <= n.
  // The empty prefix at i = 0 has sum zero.
  // Time: O(log n).
  int64_t prefix_sum(int64_t i) const {
    int64_t sum = 0;

    // Remove disjoint blocks from the remaining prefix.
    while (i > 0) {
      sum += fenwick[i];
      i -= i & -i;
    }

    return sum;
  }

  // Sum [l, r], where 1 <= l <= r <= n.
  // Both endpoints are included. Time: O(log n).
  int64_t range_sum(int64_t l, int64_t r) const {
    return prefix_sum(r) - prefix_sum(l - 1);
  }
};

void dfs(int64_t u, int64_t p,
         const vector<vector<int64_t>> &tree,
         vector<int64_t> &tin, vector<int64_t> &tout,
         int64_t &timer) {
  // Each vertex receives one position, on entry only.
  tin[u] = timer;
  timer += 1;

  for (int64_t v : tree[u]) {
    // Exclude the parent to visit only children.
    if (v == p) {
      continue;
    }
    dfs(v, u, tree, tin, tout, timer);
  }

  // DFS finishes all descendants before leaving u.
  // Its subtree occupies [tin[u], tout[u]).
  // tout[u] is the first position outside that interval.
  tout[u] = timer;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int64_t n, q;
  cin >> n >> q;

  vector<int64_t> v(n + 1);
  for (int64_t i = 1; i <= n; ++i) {
    cin >> v[i];
  }

  vector tree(n + 1, vector<int64_t>());
  for (int64_t i = 1; i < n; ++i) {
    int64_t a, b;
    cin >> a >> b;

    tree[a].push_back(b);
    tree[b].push_back(a);
  }

  vector tin(n + 1, int64_t{0});
  vector tout(n + 1, int64_t{0});
  vector flat(n + 1, int64_t{0});
  int64_t timer = 1;

  // Root the tree at 1 and assign subtree intervals.
  dfs(1, 0, tree, tin, tout, timer);

  // Rearrange values so each subtree is contiguous.
  for (int64_t u = 1; u <= n; ++u) {
    flat[tin[u]] = v[u];
  }

  // Exclude the unused zero to match the constructor.
  // Fenwick position i then represents flat[i].
  vector<int64_t> values(flat.begin() + 1, flat.end());
  FenwickTree ft(values);

  // Buffer answers to avoid flushing cout per query.
  ostringstream output;

  for (int64_t query = 1; query <= q; ++query) {
    int64_t t;
    cin >> t;

    if (t == 1) {
      int64_t s, x;
      cin >> s >> x;

      // Assignment becomes addition of the difference.
      // Use the DFS position, not the vertex number.
      int64_t value = flat[tin[s]];
      ft.update(tin[s], x - value);

      // Remember the new value for future assignments.
      flat[tin[s]] = x;
    } else {
      int64_t s;
      cin >> s;

      // Convert the subtree to an inclusive interval.
      output << ft.range_sum(tin[s], tout[s] - 1) << endl;
    }
  }

  cout << output.str();

  return 0;
}
