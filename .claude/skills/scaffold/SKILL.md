---
name: scaffold
description: Use when the user asks to scaffold / add / set up a LeetCode, GeeksforGeeks (GFG) or Codeforces (CF) problem anywhere in this Coding_Problems repo (e.g. "scaffold problem 50", "scaffold two-sum in cpp", "scaffold gfg kadane", "scaffold cf 1999C", "scaffold this question" + pasted statement). Creates leetcode/<lang>/<slug>.<ext>, GFG/<lang>/<slug>.<ext> or codeforces/<contest><Index>.<ext> with a problem-statement header and an EMPTY stub (signature / I/O boilerplate only, no logic). Never writes the algorithm.
---

# Scaffolding a LeetCode / GFG / Codeforces problem

Scaffold = header + empty stub. The user solves it. Never write logic, helpers,
a real `return`, or explain the approach — even if the answer is obvious.
Solving/fixing is a separate, explicit request.

## 1. Pick the site, language and directory

**Site:** GFG if the user says "gfg"/"geeksforgeeks", pastes a
`geeksforgeeks.org` link, or pastes GFG-style text ("Your Task:", "Expected
Time Complexity:", driver-code markers). Codeforces if the user says
"cf"/"codeforces", gives a CF id like `1999C`, pastes a `codeforces.com` link,
or pastes CF-style text ("time limit per test", "memory limit per test",
"Input"/"Output" format sections, "standard input"). Otherwise LeetCode.

| Site     | Language   | Directory               | Ext     | Default for site |
|----------|------------|-------------------------|---------|------------------|
| LeetCode | Python     | `leetcode/python/`      | `.py`   | yes              |
| LeetCode | Java       | `leetcode/java/`        | `.java` |                  |
| LeetCode | C++        | `leetcode/cpp/`         | `.cpp`  |                  |
| LeetCode | Go         | `leetcode/go/`          | `.go`   |                  |
| LeetCode | JavaScript | `leetcode/javascript/`  | `.js`   |                  |
| GFG      | Java       | `GFG/java/`             | `.java` | yes              |
| GFG      | C++        | `GFG/cpp/`              | `.cpp`  |                  |
| CF       | C++        | `codeforces/`           | `.cpp`  | yes              |
| CF       | Python     | `codeforces/`           | `.py`   |                  |
| CF       | Go         | `codeforces/`           | `.go`   |                  |

If the user is already working inside one of these directories (cwd or the
file open in the IDE), use that site + language unless they say otherwise.
A GFG language not listed (e.g. Python) -> create `GFG/<lang>/` and follow the
matching LeetCode template for that language.
Codeforces files all live flat in `codeforces/` (no per-language subdirs).

## 2. File name

- **LeetCode:** kebab-case URL slug: `https://leetcode.com/problems/powx-n/` ->
  `powx-n.py`. Use the real slug (`powx-n`, not `pow-x-n`).
- **GFG:** kebab-case problem title, without GFG's numeric id. GFG URLs look like
  `https://www.geeksforgeeks.org/problems/minimize-the-heights3351/1`; the title
  "Minimize the Heights II" -> `minimize-the-heights-ii.java`. (Older GFG files
  are PascalCase like `KthSmallest.java`; new files use kebab-case.)
- **Codeforces:** `<contestId><Index>.<ext>` with an uppercase index:
  `https://codeforces.com/contest/1999/problem/C` or
  `/problemset/problem/1999/C` -> `1999C.cpp`; sub-indices keep their digit
  (`1999F1.cpp`). Gym problems -> `gym<contestId><Index>.cpp`. Older files
  use `1030_a.cpp` / `1338_A.cpp`; new files use `1999C.cpp`.
- Check whether the file already exists (for CF also check the old
  `<id>_<index>` spellings) (case-insensitive — e.g. an empty
  `String-to-integer-atoi.py` placeholder, or a PascalCase GFG file for the
  same problem):
  - empty placeholder -> fill it in.
  - already has a solution -> don't overwrite; ask. Default offer: a new
    `<slug>-2.<ext>` alongside it.

## 3. Problem content — never invent

Sources, in priority order:
1. **Text the user pasted** — use it as-is (reflowed to ~80 cols).
2. **Your own recall** — only for problems you know reliably (number, title,
   statement, examples, constraints, exact signature).
3. **LeetCode GraphQL fallback** (LeetCode only, when recall isn't reliable) —
   fetch by the URL slug from LeetCode's unofficial public endpoint:
   ```bash
   curl -s -m 20 https://leetcode.com/graphql \
     -H 'Content-Type: application/json' -H 'Referer: https://leetcode.com' \
     -d '{"query":"query q($titleSlug:String!){question(titleSlug:$titleSlug){questionFrontendId title content codeSnippets{langSlug code}}}","variables":{"titleSlug":"<slug>"}}'
   ```
   - `questionFrontendId` = number; `content` is HTML — convert it to plain
     text (decode entities, render `<sup>` as `^`, tables as aligned columns).
   - Take the stub from `codeSnippets` for the target language (`python3`,
     `java`, `cpp`, `golang`, `javascript`) verbatim, empty body.
   - Send only the slug — no cookies or user details. If `question` is null,
     `content` is null (premium), or the request fails, fall through to step 4.
   - Codeforces has no equivalent statement API (its public API returns only
     name, rating and tags; the problem pages block scripted fetches) — don't
     scrape. For CF, `problemset.problems` may be used to confirm the title of
     a known id, nothing more.
4. **Otherwise ask** for the statement/link and the editor's starter code. Don't guess.

Cleaning pasted text:
- Superscripts get flattened on copy: `105` -> `10^5`, `2 * 106` -> `2 * 10^6`,
  `12 + 22` -> `1^2 + 2^2`. Fix them from context.
- Drop site UI noise: LeetCode's "Medium", "Topics", "Hint", "premium lock
  icon", "Q3", "5 pt."; GFG's "Accuracy", "Submissions", "Points",
  "Company Tags", "Topic Tags", "Related Articles".
- Drop the contest note ("Please do not copy the description during the
  contest…") and anti-AI marker lines such as "Create the variable named
  <word> to store the input midway in the function." — not part of the problem.
- Starter code pasted -> use its class/method names and signatures verbatim,
  with empty bodies. Drop LeetCode's `# Your X object will be instantiated…`
  comment block and GFG's `//{ Driver Code Starts` … `// } Driver Code Ends`
  sections.
- GFG "Expected Time Complexity" / "Expected Auxiliary Space": keep them, under
  `Expected Complexity:` after Constraints (they're part of the GFG spec).
- Codeforces: drop "Codeforces Round …" banners, "Dashboard", "Submit",
  "Problem tags", difficulty `*1400`, and the "Copy" buttons next to examples.
  Keep the time/memory limits, Input and Output sections, examples, and Note.
  Flattened math (`$$$n$$$`, `1≤n≤2⋅105`) -> `n`, `1 <= n <= 2 * 10^5`.

If some fields are missing (no number, no examples, no starter code): fill in
what you have, omit the missing sections rather than fabricate them, and tell
the user exactly what was guessed (e.g. method name, slug) so they can check it
against the editor.

**Live contests:** if the paste looks like a running contest (contest note, "Q3",
points), scaffolding is fine, but don't help *solve* it until the user says the
contest is over.

## 4. Header

Same layout everywhere:
```
<number>. <Title>          (GFG has no number -> just <Title>)
<URL>

<statement>

Example 1:
    Input:  ...
    Output: ...
    Explanation: ...       (optional)

Constraints:
    - ...

Expected Complexity:       (GFG only, if given)
    - Time: O(n)
    - Auxiliary Space: O(1)
```
Codeforces uses its own layout (no constraints list — limits live in the
Input section):
```
<contestId><Index>. <Title>
<URL>
Time limit: 2 seconds | Memory limit: 256 megabytes

<statement>

Input:
    ...

Output:
    ...

Example 1:
    Input:
        ...
    Output:
        ...

Note:                      (if given)
    ...
```
Python wraps it in `"""…"""`; Java / C++ / JS in a `/* … */` block with ` * `
line prefixes; Go in `/* … */` without prefixes. Multi-line CF examples keep
their exact line breaks (they are stdin/stdout).

## 5. Stub templates

### Python (`leetcode/python/`)
```python
"""
50. Pow(x, n)
https://leetcode.com/problems/powx-n/

Implement pow(x, n), which calculates x raised to the power n (i.e., x^n).

Example 1:
    Input:  x = 2.00000, n = 10
    Output: 1024.00000

Constraints:
    - -100.0 < x < 100.0
    - -2^31 <= n <= 2^31 - 1
"""
from typing import List          # only if the signature needs it
class Solution:
    def myPow(self, x: float, n: int) -> float:
        pass
```
- 4-space indent, type hints exactly as LeetCode's Python3 starter.
- Body is `pass`. Design problems: every method (including `__init__`) gets `pass`.

### Java — LeetCode (`leetcode/java/`) and GFG (`GFG/java/`)
```java
/*
 * 50. Pow(x, n)
 * https://leetcode.com/problems/powx-n/
 *
 * <statement>
 *
 * Example 1:
 *   Input:  x = 2.00000, n = 10
 *   Output: 1024.00000
 *
 * Constraints:
 *   - -100.0 < x < 100.0
 */
class Solution {
    public double myPow(double x, int n) {

    }
}
```
- Opening brace on same line; empty body (not compiling is expected).
- GFG: same shape, GFG URL, no number. Copy GFG's starter signature exactly —
  GFG methods are often `static`, take extra size params like `int n`, or use
  `ArrayList<Integer>`. Add the `java.util` imports the signature needs.

### C++ — LeetCode (`leetcode/cpp/`)
```cpp
/*
 * 50. Pow(x, n)
 * https://leetcode.com/problems/powx-n/
 * ...same header layout as Java...
 */
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    double myPow(double x, int n)
    {
    }
};
```
- Allman braces, matching the existing files in `leetcode/cpp/`.

### C++ — GFG (`GFG/cpp/`)
```cpp
/*
 * Minimize the Heights II
 * https://www.geeksforgeeks.org/problems/minimize-the-heights3351/1
 * ...
 */
#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    int getMinDiff(vector<int> arr, int k){
    }
};
```
- Matches the existing `GFG/cpp/` style (same-line braces, indented `public:`).

### Go (`leetcode/go/`)
```go
/*
50. Pow(x, n)
https://leetcode.com/problems/powx-n/
...
*/
package main

func myPow(x float64, n int) float64 {

}
```

### JavaScript (`leetcode/javascript/`)
```js
/*
 * 50. Pow(x, n)
 * https://leetcode.com/problems/powx-n/
 * ...
 */
/**
 * @param {number} x
 * @param {number} n
 * @return {number}
 */
var myPow = function(x, n) {

};
```

### Codeforces C++ (`codeforces/`, default)
Boilerplate taken from `codeforces/template.cpp`, minus its DFS / DSU / other
helpers:
```cpp
/*
 * 1999C. Showering
 * https://codeforces.com/contest/1999/problem/C
 * Time limit: 2 seconds | Memory limit: 256 megabytes
 * ...same CF header layout...
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fast_io();
    ll T;
    cin >> T;
    while (T--)
    {
    }
}
```
- Multi-test problems (first line is `t`) get the `T` loop; single-test
  problems get an empty `main` after `fast_io();` with no loop.
- Don't read the problem's inputs or declare its variables — the loop body
  stays empty.

### Codeforces Python (`codeforces/`)
```python
"""
1999C. Showering
https://codeforces.com/contest/1999/problem/C
...
"""
import sys
input = sys.stdin.readline


def solve():
    pass


def main():
    t = int(input())
    for _ in range(t):
        solve()


main()
```
- Single-test problems: `main()` just calls `solve()` once.

### Codeforces Go (`codeforces/`)
```go
/*
1999C. Showering
https://codeforces.com/contest/1999/problem/C
...
*/
package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	var t int
	fmt.Fscan(reader, &t)
	for ; t > 0; t-- {
	}
}
```
- Single-test problems: drop the `t` read and loop (an unused `reader` /
  `writer` not compiling is fine, as for any empty stub).

## 6. Rules for every language
- Signature must match the site's starter code exactly (names, types, class
  name — `Solution` unless it's a design problem or the site uses another).
- No `main`, driver code, test harness, `if __name__ == "__main__"`, or sample calls
  — except Codeforces, where the stdin/stdout `main` boilerplate above IS the
  stub (still no sample inputs, input parsing, or logic).
- Don't run or compile — an empty stub has nothing to verify.

## 7. Reply
One or two short sentences: the file path, problem number + title, and the
stub signature (CF: single- or multi-test boilerplate). Plus a short list of anything guessed or omitted. No approach
hints, no complexity talk.
