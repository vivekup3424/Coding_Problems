from collections import deque


class Solution:
    def canBeValid(self, s: str, locked: str) -> bool:
        parenthesisStack = deque()
        lockedStack = deque()
        for i, c in enumerate(s):
            if locked[i] == "0":
                lockedStack.append(i)
            else:
                if s[i] == "(":
                    parenthesisStack.append(i)
                elif s[i] == ")":
                    if len(parenthesisStack) > 0:
                        parenthesisStack.pop()
                    elif len(lockedStack) > 0:
                        lockedStack.pop()
                while len(parenthesisStack) > 0 and len(lockedStack) > 0:
                    if parenthesisStack.pop() > lockedStack.pop():
                        return False
        return len(parenthesisStack) == 0
