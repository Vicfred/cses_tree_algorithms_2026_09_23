# CSES Tree Algorithms Practice

C++ solutions for the [CSES Tree Algorithms problem set](https://cses.fi/problemset/list/).

The main priority of this repository is **learning tree algorithms** through explicit roots, parent/child relationships, precise states, processing order and arguments that explain why each step is valid. The solutions favour readable implementations and solid fundamentals. Optimisation follows after the intuitive approach and its limitations are understood.

The archived implementations cover descendant counting, tree dynamic programming, diameter computation, binary lifting, lowest common ancestors, distance queries, DFS flattening and Fenwick trees. Separate traversal, preprocessing and query stages are retained where they make the reasoning clearer.

The table includes all **16 problems** in the supplied Tree Algorithms ranking: **7 Core, 3 Important, 1 Useful and 5 Advanced**. All **7 Core** problems have archived solutions, covering **9 C++ files**, including one intentional TLE teaching version. The remaining **9 problems** are marked **Not yet**. Here, **Solved** means a solution is included in this archive; it does not claim a fresh compilation, test run or verification of a CSES submission. The ratings describe this repository's learning priorities, rather than official CSES difficulty ratings.

## Problems

| Index | Problem | Main idea | Rating | Status |
|:---:|---|---|:---:|:---:|
| 1 | [Subordinates](https://cses.fi/problemset/task/1674) | Count descendants with memoised DFS or one child-before-parent traversal. | 🧱 **Core** | ✅ Solved |
| 2 | [Tree Matching](https://cses.fi/problemset/task/1130) | Tree DP with states recording whether a vertex is matched to its parent; reuse child totals when considering a match. | 🧱 **Core** | ✅ Solved |
| 3 | [Tree Diameter](https://cses.fi/problemset/task/1131) | Use two BFS traversals: find a diameter endpoint, then its greatest distance. | 🧱 **Core** | ✅ Solved |
| 4 | [Tree Distances I](https://cses.fi/problemset/task/1132) | Find each vertex's maximum distance using diameter endpoints or tree DP. | ⭐ **Important** | ⏳ Not yet |
| 5 | [Tree Distances II](https://cses.fi/problemset/task/1133) | Compute each vertex's sum of distances to all other vertices using rerooting DP. | 🧠 **Advanced** | ⏳ Not yet |
| 6 | [Company Queries I](https://cses.fi/problemset/task/1687) | Find the k-th ancestor by decomposing k into binary-lifting jumps. | 🧱 **Core** | ✅ Solved |
| 7 | [Company Queries II](https://cses.fi/problemset/task/1688) | Find the LCA by equalising depths, then lifting both vertices while their ancestors differ. | 🧱 **Core** | ✅ Solved |
| 8 | [Distance Queries](https://cses.fi/problemset/task/1135) | Use original endpoint depths and their LCA: depth[a] + depth[b] − 2 × depth[LCA(a, b)]. | 🧱 **Core** | ✅ Solved |
| 9 | [Counting Paths](https://cses.fi/problemset/task/1136) | Count query paths through each vertex using LCA and tree difference accumulation. | ⭐ **Important** | ⏳ Not yet |
| 10 | [Subtree Queries](https://cses.fi/problemset/task/1137) | Flatten subtrees into DFS intervals and maintain their sums with a Fenwick tree. | 🧱 **Core** | ✅ Solved |
| 11 | [Path Queries](https://cses.fi/problemset/task/1138) | Maintain root-to-vertex path sums using an Euler-tour representation and a Fenwick/segment tree. | ⭐ **Important** | ⏳ Not yet |
| 12 | [Path Queries II](https://cses.fi/problemset/task/2134) | Maintain arbitrary path maxima using heavy-light decomposition and a segment tree. | 🧠 **Advanced** | ⏳ Not yet |
| 13 | [Distinct Colors](https://cses.fi/problemset/task/1139) | Count distinct colours in every subtree using small-to-large merging or offline techniques. | 🧠 **Advanced** | ⏳ Not yet |
| 14 | [Finding a Centroid](https://cses.fi/problemset/task/2079) | Compute subtree sizes and locate a vertex whose removal leaves no component larger than half the tree. | 🛠️ **Useful** | ⏳ Not yet |
| 15 | [Fixed-Length Paths I](https://cses.fi/problemset/task/2080) | Count vertex pairs at exactly distance k, classically using centroid decomposition. | 🧠 **Advanced** | ⏳ Not yet |
| 16 | [Fixed-Length Paths II](https://cses.fi/problemset/task/2081) | Count vertex pairs with distances in an interval using centroid decomposition and distance counting. | 🧠 **Advanced** | ⏳ Not yet |

## Alternative Implementations and Learning Progression

Two problems preserve multiple implementations. Subordinates compares memoisation with a single traversal. Tree Matching retains the direct sibling-summation recurrence alongside the version that removes repeated work.

A trailing `_` identifies an alternative implementation; it does not automatically mean a faster solution. The `_TLE` suffix explicitly identifies an **intentional slow teaching version**. There are no `_MLE` files in this archive.

In the tables below, `n` is the number of vertices and `q` is the number of queries. Space includes the stored tree, auxiliary arrays and any recursion stack. Buffered answers are included where used.

| File | Approach | Time | Space |
|---|---|---|---|
| [1_subordinates.cpp](1_subordinates.cpp) | Memoised DFS called for every employee; the first call computes all descendant counts and later calls reuse them. | O(n) | O(n) |
| [1_subordinates_.cpp](1_subordinates_.cpp) | One DFS from the root; add each child's completed descendant count plus the child itself. | O(n) | O(n) |
| [2_tree_matching_TLE.cpp](2_tree_matching_TLE.cpp) | For each possible selected child edge, explicitly sum all other child contributions. Intentional TLE teaching version. | O(n²) worst case | O(n) |
| [2_tree_matching.cpp](2_tree_matching.cpp) | Compute the common child total S once; replace only the chosen child's contribution. | O(n) | O(n) |

Both Subordinates versions are linear. Memoisation prevents repeated traversals; the single-DFS version avoids asking for already-completed answers again. Neither version counts the employee itself as a subordinate.

The Tree Matching teaching version repeats a sibling scan for each candidate child. A star with n − 1 children makes that work quadratic at the root. The improved version keeps exactly the same states and choices, but evaluates each candidate in constant time using:

```text
candidate = 1 + dp[v][1] + S - dp[v][0]
```

The other archived implementations are listed here so that every source file has a direct link:

| File | Approach | Time | Space |
|---|---|---|---|
| [3_tree_diameter.cpp](3_tree_diameter.cpp) | BFS from vertex 1, choose a farthest vertex, then BFS from that diameter endpoint. | O(n) | O(n) |
| [6_company_queries_i.cpp](6_company_queries_i.cpp) | BFS depths and parents; build binary-lifting columns; reject ancestors beyond the root and process set bits of k. | O(n log n + q log n) | O(n log n) |
| [7_company_queries_ii.cpp](7_company_queries_ii.cpp) | BFS preprocessing and binary lifting; equalise depths, then take simultaneous descending-power jumps. | O(n log n + q log n) | O(n log n) |
| [8_distance_queries.cpp](8_distance_queries.cpp) | Save endpoint depths, find the LCA with binary lifting and buffer distance answers. | O(n log n + q log n) | O(n log n + q) |
| [10_subtree_queries.cpp](10_subtree_queries.cpp) | Recursive DFS flattening, linear Fenwick construction, point assignments through differences and subtree range sums. | O(n + q log n) | O(n + q) |

The un-memoised DFS-per-employee approach to Subordinates and the direct interval-scan approach to Subtree Queries were useful learning steps, but are not included as separate files in this archive. Their repeated work explains the need for memoisation and a range-query structure respectively.

## Tree Algorithms Techniques Practised

The aim is to become comfortable with a compact set of reusable ideas:

- choosing a root and distinguishing an undirected neighbour from a child;
- excluding the parent edge when traversing an undirected tree;
- recognising that different child subtrees are disjoint;
- distinguishing subtree size, which includes its root, from descendant count, which excludes it;
- finishing child states before using them to compute a parent state;
- defining which edges a matching state counts and whether its root is already occupied;
- comparing complete matching alternatives while selecting at most one child edge;
- removing repeated sibling summation without changing the recurrence;
- counting path lengths and depths in edges rather than vertices;
- using a farthest vertex to obtain a diameter endpoint;
- composing two ancestor jumps to build a larger binary-lifting jump;
- treating zero as a missing-ancestor sentinel and preserving its table row;
- decomposing a jump length into powers of two using its set bits;
- keeping LCA candidates at equal depth and below their common ancestor;
- preserving original endpoint information before mutating query vertices;
- flattening an entire subtree into one contiguous DFS interval;
- distinguishing a vertex label from its position in the flattened array;
- matching half-open DFS intervals to inclusive range-query interfaces;
- converting assignment into addition of the difference from the current value;
- checking indexing contracts when passing values into a data structure.

Rerooting, heavy-light decomposition, small-to-large merging and centroid decomposition appear in the roadmap table. They are not implemented in the current archive.

## Implementation Notes

Each `.cpp` file is a standalone program with its own `main`. Compile and run one solution at a time using **C++23**.

```sh
g++ -std=c++23 -O2 -Wall -Wextra 10_subtree_queries.cpp -o subtree_queries
./subtree_queries < input.txt
```

The code uses explicit standard headers, `int64_t` for values, counts and indices, `using namespace std`, and readable traversal and preprocessing stages. The recursive implementations use separate DFS functions; the BFS implementations use a queue named `q`. Each file retains its own implementation rather than depending on a shared tree library.

Both Subordinates implementations use **zero-based employees**, rooted at employee 0. Their directed adjacency lists contain only boss-to-child edges, so no parent exclusion is required. All other archived tree implementations use **one-based vertices**, with vertex 1 as the traversal root or initial BFS source.

For **Subordinates**, a leaf has answer zero. For every child v, add `1 + answer[v]`: the one counts the child, and the remaining term counts its descendants. Memoised answers are stored only after every child is processed. The `-1` sentinel distinguishes an unknown answer from a completed zero.

For **Tree Matching**, `dp[u][matched_to_parent]` counts selected edges entirely inside u's subtree; the edge to u's parent is excluded.

- State 0 permits matching u with no child or exactly one child.
- State 1 assumes u is matched to its parent, so no edge from u to a child may be selected.
- A leaf has zero in both states.
- The common total `S = sum(dp[v][0])` describes selecting no child edge.
- Selecting `(u, v)` adds one edge and replaces `dp[v][0]` with `dp[v][1]`; all other child contributions remain unchanged.
- The root has no parent, so the final answer is `dp[1][0]`.

For **Tree Diameter**, any farthest vertex from an arbitrary source is an endpoint of some diameter. A second BFS from that endpoint gives the diameter length as its greatest distance. Distances count edges, so a single-vertex tree has diameter zero. The first BFS empties `q`, allowing it to be reused.

For **binary lifting**, `up[u][j]` is the ancestor 2^j edges above u. BFS first computes depths and immediate parents. The table then joins two jumps of length 2^(j − 1):

```text
middle = up[u][j - 1]
up[u][j] = up[middle][j - 1]
```

The column loop comes before the vertex loop so the entire preceding column is available. Vertex 0 is a missing-ancestor sentinel; its row remains zero. Company Queries I checks `k > depth[u]` before processing bits, so jumps above the root are rejected even when k is much larger than n. A bit test checks whether the masked result is nonzero, rather than whether it equals one.

For **LCA**, first lift the deeper vertex to the shallower depth. If the vertices coincide, that vertex is the answer. Otherwise, examine jump sizes from largest to smallest and move both vertices only when their jumped-to ancestors differ. They remain distinct, at equal depth and strictly below the LCA. At the end, their immediate parents coincide.

For **Distance Queries**, save the original endpoint depths before lifting. The implementation moves `lca` and `b` together during the simultaneous-jump phase; `lca` is initially a candidate vertex and becomes the actual LCA afterwards. The formula

```text
depth_a + depth_b - 2 * depth[lca]
```

counts the upward segment from one endpoint and the downward segment to the other. It also gives zero when both endpoints are identical.

For **Subtree Queries**, the DFS timer starts at 1 and advances only on entry. Set `tin[u]` when entering u and `tout[u]` after all its children are complete. DFS cannot leave u's subtree and then return to discover more of its descendants, so the subtree occupies exactly **[tin[u], tout[u])**. Its size is `tout[u] - tin[u]`; a leaf occupies one position, and the root's exclusive endpoint is n + 1.

Flattening remains a separate stage:

```text
flat[tin[u]] = v[u]
```

The Fenwick constructor expects a **zero-based input vector containing only actual values**, while `flat` has an unused position zero. The `values` copy excludes that element, ensuring Fenwick position i represents `flat[i]`. Updates use `tin[s]`, not the vertex number s. The update difference is `x - flat[tin[s]]`, and `flat[tin[s]]` is then set to x for future assignments. The inclusive query interface receives `[tin[s], tout[s] - 1]`.

For the **Fenwick tree**, `fenwick[i]` stores the block ending at i with length `i & -i`. An update moves upwards through every containing block; a prefix query moves downwards through disjoint blocks. Linear construction accumulates the current input value with `+=`, preserving earlier contributions, then forwards the completed block to its parent.

Distance Queries and Subtree Queries buffer their answers in `ostringstream` and write to `cout` once. In Subtree Queries, `endl` acts on the string stream rather than flushing standard output per answer. The archived Subtree Queries file also disables stream synchronisation and unties `cin`; this is an input/output setting, separate from the algorithm and its complexity.

Recursive DFS depth can reach O(n) on a chain. The space bounds include these calls; an explicit DFS stack is an alternative when the execution environment's call-stack limit is restrictive.

## Focus

The recurring question throughout the set is:

> **What information does this vertex need, and when is that information ready to use?**

Descendant counting and matching require completed child answers. Binary lifting requires completed smaller-jump columns. Subtree flattening requires finishing every descendant before recording the exclusive endpoint. Dynamic queries require the maintained array position to represent the current value of its vertex.

For dynamic programming, the guiding principle remains:

> **Different histories can be represented by the same DP state if they have exactly the same effect on all future decisions.**

For matching, everything outside a child's subtree affects its internal choices through whether its root is matched to its parent. Once that condition is fixed, the child does not need the entire history of choices above it.

Understand the requested result and constraints, devise a plan using familiar structures, carry it out with explicit invariants, and look back at why it works. Before replacing an implementation, explain what repeated work the change removes and preserve a useful earlier version when it makes the reasoning easier to revisit.
