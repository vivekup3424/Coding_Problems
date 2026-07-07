---
name: leetcode-solution
description: Use when the user asks to add, scaffold, or write the header/boilerplate/Solution class for a LeetCode problem in this java directory (e.g. "scaffold two-sum", "add remove-covered-intervals", "write the class Solution for X"). Creates the .java file with the standard problem-statement header and an EMPTY Solution stub (method signature only, no logic) — the user writes the actual algorithm themselves. Do not use this to implement a working solution.
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

## Solution class — STUB ONLY, never the algorithm
This skill scaffolds, it does not solve. Leave the method body empty, exactly like
LeetCode's own "Java" starter code for a problem:
```java
class Solution {
    public int removeCoveredIntervals(int[][] intervals) {

    }
}
```
- Class must be named `Solution` (LeetCode judge convention).
- Method name and signature must match LeetCode's exact signature for that problem.
- Style used throughout this repo: 4-space indent, opening brace on the same line,
  no space before `(` in control statements (`if(...)`, `for(...)`).
- Body stays empty. Do not fill in any logic, do not add a `return` statement,
  do not add helper methods — it not compiling is expected and fine, same as a
  fresh LeetCode problem page. The user solves it themselves.
- Never write a solution here even if you know the answer — do this only if the
  user explicitly asks you to solve/implement it (that's a separate ask, not this
  skill's job).
- No `main` method or test harness in the committed file.

## Workflow
1. Given a problem name, number, or URL, recall the exact statement/examples/constraints.
2. Determine the file name and check whether it already exists in this directory.
3. Write the header + empty Solution stub into that one file, matching the format above.
4. Do NOT compile/test it — an empty body has nothing to verify.
5. Stop there. Don't explain an approach or complexity — that would be solving it.
