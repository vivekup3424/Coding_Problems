from typing import List
class StockSpanner:
    def __init__(self):
        self.stack: List[tuple[int,int]]= [] #stores the indices of elements
        self.index = 0
    
    def next(self, price: int) -> int:
        while len(self.stack) > 0 and self.stack[-1][1] <= price:
            self.stack.pop()

        value = self.index + 1 if len(self.stack) == 0 else self.index - self.stack[-1][0]
        self.stack.append((self.index,price))
        self.index+=1
        return value