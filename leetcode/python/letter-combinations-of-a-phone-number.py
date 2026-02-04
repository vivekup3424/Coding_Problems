class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        characters_map = {
            "2": ["a", "b", "c"],
            "3": []
        }