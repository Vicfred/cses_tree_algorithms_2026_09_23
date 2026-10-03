// vicfred
// https://cses.fi/problemset/task/1131
// Find the maximum number of edges on a path in a tree.
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Two BFS passes find the longest path's length.
// A farthest vertex from any starting vertex is an
// endpoint of some diameter. Starting there, the greatest
// distance reaches another endpoint and gives its length.
// Time: O(n). Total space: O(n).
int main() {
  int64_t n;
  cin >> n;

  vector tree(n + 1, vector<int64_t>());
  for (int64_t i = 1; i < n; ++i) {
    int64_t a, b;
    cin >> a >> b;
    tree[a].push_back(b);
    tree[b].push_back(a);
  }

  // Vertex 1 is an arbitrary starting point.
  // -1 means unvisited; distances count edges, not
  // vertices.
  vector<int64_t> distance_from_one(n + 1, -1);
  distance_from_one[1] = 0;

  queue<int64_t> q;
  q.push(1);

  while (!q.empty()) {
    int64_t u = q.front();
    q.pop();

    for (int64_t v : tree[u]) {
      if (distance_from_one[v] != -1) {
        continue;
      }
      // Mark on discovery so each vertex is queued once.
      // BFS visits vertices in increasing distance order.
      distance_from_one[v] = distance_from_one[u] + 1;
      q.push(v);
    }
  }

  // Any farthest vertex works, including when there is a
  // tie.
  int64_t max_distance = -1;
  int64_t farthest = -1;
  for (int64_t u = 1; u <= n; ++u) {
    if (distance_from_one[u] > max_distance) {
      max_distance = distance_from_one[u];
      farthest = u;
    }
  }

  // Measure distances again, now from a diameter endpoint.
  vector<int64_t> distance_from_farthest(n + 1, -1);
  distance_from_farthest[farthest] = 0;

  // The first BFS emptied q, so it can be reused directly.
  q.push(farthest);

  while (!q.empty()) {
    int64_t u = q.front();
    q.pop();

    for (int64_t v : tree[u]) {
      if (distance_from_farthest[v] != -1) {
        continue;
      }
      distance_from_farthest[v] =
        distance_from_farthest[u] + 1;
      q.push(v);
    }
  }

  // The tree has a unique simple path between each pair.
  // From this endpoint, the largest distance is its
  // diameter. A single-vertex tree correctly gives zero
  // edges.
  int64_t diameter = -1;
  for (int64_t u = 1; u <= n; ++u) {
    diameter = max(diameter, distance_from_farthest[u]);
  }

  cout << diameter << endl;

  return 0;
}
