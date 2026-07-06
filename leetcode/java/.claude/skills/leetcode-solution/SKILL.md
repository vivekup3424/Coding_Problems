---
name: leetcode-solution
description: Use when the user asks to solve, add, scaffold, or write the header/boilerplate/Solution class for a LeetCode problem in this java directory (e.g. "solve two-sum", "add remove-covered-intervals", "write the class Solution for X"). Creates or fills in the .java file with the standard problem-statement header and a working Solution class, following this repo's conventions.
---

# Adding a LeetCode Java Solution

## File naming
- kebab-case matching the LeetCode URL slug, e.g.
  `https://leetcode.com/problems/remove-covered-intervals/` -> `remove-covered-intervals.java`
- Lives directly in this directory (`leetcode/java/`). Check whether the file already
  exists (possibly empty, created as a placeholder) before creating a new one.

## Header format
Every solution file starts with a block comment, e.g.:
```java
/*
 * <number>. <Problem Title>
 * https://leetcode.com/problems/<slug>/
 *
 * <problem statement, wrapped at ~80 cols>
 *
 * Example 1:
 *   Input:  <input>
 *   Output: <output>
 *   Explanation: <optional>
 *
 * Constraints:
 *   - <constraint>
 */
```
Recall the actual LeetCode problem number, statement, examples, and constraints
accurately — don't invent or approximate them. If unsure of the exact wording,
say so and ask the user for the problem link/text rather than guessing.

## Solution class
- Class must be named `Solution` (LeetCode judge convention).
- Method name and signature must match LeetCode's exact signature for that problem.
- Style used throughout this repo: 4-space indent, opening brace on the same line,
  no space before `(` in control statements (`if(...)`, `for(...)`):
```java
class Solution {
    public int removeCoveredIntervals(int[][] intervals) {
        ...
    }
}
```
- Implement a real, working solution — not a stub — unless the user explicitly asks
  for just a skeleton/stub (in which case use the minimal `class Solution{\n\n}`
  form seen elsewhere in this repo).
- No `main` method or test harness in the committed file — this repo doesn't use
  them; solutions are graded on LeetCode directly. If verification is useful,
  compile/run a scratch copy with a temporary `Main` class outside this directory,
  then discard it.

## Workflow
1. Given a problem name, number, or URL, recall the exact statement/examples/constraints.
2. Determine the file name and check whether it already exists in this directory.
3. Write the header + Solution class into that one file, matching the format above.
4. Compile it (`javac`) to make sure it's syntactically valid.
5. State the approach and time/space complexity briefly — don't over-explain.
