class Solution:
    def canChange(self, start: str, target: str) -> bool:
        start_positions = [(char, idx) for idx, char in enumerate(start) if char != "_"]
        target_positions = [
            (char, idx) for idx, char in enumerate(target) if char != "_"
        ]
        if len(start_positions) != len(target_positions):
            return False
        for (s_char, s_idx), (t_char, t_idx) in zip(start_positions, target_positions):
            if s_char != t_char:  # The characters must match
                return False
            if s_char == "L" and t_idx > s_idx:  # 'L' can only move left
                return False
            if s_char == "R" and t_idx < s_idx:  # 'R' can only move right
                return False
        return True


import unittest


class TestCanChange(unittest.TestCase):
    def test_cases(self):
        sol = Solution()
        # Test cases provided in the problem
        self.assertTrue(sol.canChange("_L__R__R_", "L______RR"))
        self.assertFalse(sol.canChange("R_L_", "__LR"))
        self.assertFalse(sol.canChange("_R", "R_"))
        self.assertFalse(sol.canChange("R_L_", "_R_L"))
        self.assertTrue(sol.canChange("_L_R_", "L__R_"))
        self.assertFalse(sol.canChange("R_L_", "__RL_"))
        self.assertTrue(sol.canChange("L___R", "L___R"))
        self.assertTrue(sol.canChange("_L", "L_"))


if __name__ == "__main__":
    unittest.main()
