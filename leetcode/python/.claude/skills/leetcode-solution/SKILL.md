---
name: leetcode-solution
description: Use when the user asks to add, scaffold, or write the header/boilerplate/Solution class for a LeetCode problem in this python directory (e.g. "scaffold two-sum", "add remove-covered-intervals", "write the class Solution for X"). Creates the .py file with an EMPTY Solution stub (method signature only, no logic) — the user writes the actual algorithm themselves. Do not use this to implement a working solution.
---

# Adding a LeetCode Python Solution

## File naming
- kebab-case matching the LeetCode URL slug, e.g.
  `https://leetcode.com/problems/remove-covered-intervals/` -> `remove-covered-intervals.py`
- Lives directly in this directory (`leetcode/python/`). Check whether the file already
  exists (possibly empty, created as a placeholder) before creating a new one.

## File format
No problem-statement header comment in this repo's python files — just the imports
needed for the signature (e.g. `from typing import List`, `from collections import defaultdict`)
followed directly by the class, e.g.:
```python
from typing import List
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:

```

## Solution class — STUB ONLY, never the algorithm
This skill scaffolds, it does not solve. Leave the method body empty (just a blank
line, or `pass` if a non-empty body is required to avoid an IndentationError):
```python
class Solution:
    def removeCoveredIntervals(self, intervals: List[List[int]]) -> int:
        pass
```
- Class must be named `Solution` (LeetCode judge convention).
- Method name and signature (including type hints) must match LeetCode's exact
  signature for that problem.
- Style used throughout this repo: 4-space indent, type hints on params and return.
- Body stays empty (`pass` only). Do not fill in any logic, do not add helper
  methods, do not add a real `return` — the user solves it themselves.
- Never write a solution here even if you know the answer — do this only if the
  user explicitly asks you to solve/implement it (that's a separate ask, not this
  skill's job).
- No `if __name__ == "__main__"` block or test harness in the committed file.

## Workflow
1. Given a problem name, number, or URL, recall the exact method signature LeetCode
   uses for it (parameter names, types, return type).
2. Determine the file name and check whether it already exists in this directory.
3. Write the empty Solution stub into that one file, matching the format above.
4. Do NOT run/test it — an empty body has nothing to verify.
5. Stop there. Don't explain an approach or complexity — that would be solving it.
