from collections import deque

MAX_HEIGHT = 100
dq = deque()
dq.append(100 - 0)
for i in range(1, MAX_HEIGHT):
    dq.append(100 - i)
    dq.appendleft(100 - i)
