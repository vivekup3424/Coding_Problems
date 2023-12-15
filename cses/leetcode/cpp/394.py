class Solution:
    def decodeString(self, s: str) -> str:
        stack = []
        for c in s:
            if c!= ']':
                stack.append(c)
            else:
                tmp = ""
                while stack[-1]!='[':
                    tmp = stack.pop() + tmp
                stack.pop() # pop '['
                num = ""
                while stack and stack[-1].isdigit():
                    num = stack.pop() + num
                stack.append(tmp*int(num))
        return "".join(stack)

Solution().decodeString("3[a]2[bc]")