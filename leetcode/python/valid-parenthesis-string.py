from collections import deque


class Solution:
    def checkValidString(self, s: str) -> bool:
        stackParenthesis = deque()
        specialStack = deque()
        for i, c in enumerate(s):
            if c == "(":
                stackParenthesis.append(i)  # Store index of '('
            elif c == "*":
                specialStack.append(i)  # Store index of '*'
            elif c == ")":
                if stackParenthesis:  # Prioritize matching '('
                    stackParenthesis.pop()
                elif (
                    specialStack
                ):  # Use '*' if no '(' available, here we are using * as (
                    specialStack.pop()
                else:
                    return False  # Unmatched ')'

        # Second pass: Match remaining '(' with '*'
        while stackParenthesis and specialStack:
            if stackParenthesis.pop() > specialStack.pop():
                return False  # '(' cannot appear after '*' for balancing, here we are using * as )

        # Return True if no unmatched '(' remains
        return not stackParenthesis
