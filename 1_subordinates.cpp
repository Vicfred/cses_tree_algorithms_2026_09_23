// vicfred
// https://cses.fi/problemset/task/1674
// Count each employee's direct and indirect subordinates.
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

// Return the number of descendants of u, excluding u.
int64_t dfs(int64_t u, const vector<vector<int64_t>> &graph,
            vector<int64_t> &memo) {
  // Reuse completed answers instead of revisiting subtrees.
  if (memo[u] != -1) {
    return memo[u];
  }

  // A leaf has no children, so its answer remains zero.
  int64_t subordinates = 0;
  for (int64_t v : graph[u]) {
    // Finish the child's answer before using it here.
    // Count v itself and all descendants below v.
    // Different child subtrees contain no shared employees.
    subordinates += 1 + dfs(v, graph, memo);
  }

  // Store the answer only after all children are processed.
  memo[u] = subordinates;
  return memo[u];
}

int main() {
  int64_t n;
  cin >> n;

  // Store edges from boss to child; employee 0 is the root.
  // We never walk towards a parent, so no visited is
  // needed.
  vector graph(n, vector<int64_t>());
  for (int64_t i = 1; i < n; ++i) {
    int64_t p;
    cin >> p;

    // Convert the boss to our zero-based indexing.
    p -= 1;
    graph[p].push_back(i);
  }

  // -1 means unknown; zero is a valid completed answer.
  vector<int64_t> memo(n, -1);

  // The first call visits the whole tree and saves answers.
  // Later calls return the stored answers immediately.
  for (int64_t i = 0; i < n; ++i) {
    cout << dfs(i, graph, memo) << " ";
  }
  cout << endl;

  return 0;
}
