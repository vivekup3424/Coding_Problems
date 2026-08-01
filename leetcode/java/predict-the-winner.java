/*
 * 486. Predict the Winner
 * https://leetcode.com/problems/predict-the-winner/
 *
 * You are given an integer array nums. Two players are playing a game with
 * this array: player 1 and player 2.
 *
 * Player 1 and player 2 take turns, with player 1 starting first. Both
 * players start the game with a score of 0. At each turn, the player takes
 * one of the numbers from either end of the array (i.e., nums[0] or
 * nums[nums.length - 1]) which reduces the size of the array by 1. The
 * player adds the chosen number to their score. The game ends when there
 * are no more elements in the array.
 *
 * Return true if Player 1 can win the game. If the scores of both players
 * are equal, then player 1 is still the winner, and the answer is true.
 * You may assume that both players are playing optimally.
 *
 * Example 1:
 *   Input:  nums = [1,5,2]
 *   Output: false
 *   Explanation: Initially, player 1 can choose between 1 and 2. If he
 *     chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If
 *     player 2 chooses 5, then player 1 will be left with 1 (or 2). So,
 *     final score of player 1 is 1 + 2 = 3, and player 2 is 5. Hence,
 *     player 1 will never be the winner and you need to return False.
 *
 * Example 2:
 *   Input:  nums = [1,5,233,7]
 *   Output: true
 *   Explanation: Player 1 first chooses 1. Then player 2 has to choose
 *     between 5 and 7. No matter which number player 2 chooses, player 1
 *     can choose 233. Finally, player 1 has more score (234) than player 2
 *     (12), so you need to return True.
 *
 * Constraints:
 *   - 1 <= nums.length <= 20
 *   - 0 <= nums[i] <= 10^7
 */

class Solution {
    private int recurse(int[] nums, int l, int r, int turn){
        if(l > r) return 0;
        if(turn==1){
            return Math.max(
                recurse(nums, l+1, r, 2) + nums[l],
                recurse(nums,l,r-1,2) + nums[r]
            );
        }
        else{
            return Math.min(
                recurse(nums,l+1,r,1),
                recurse(nums,l,r-1,1)
            );
        }
    }
    public boolean predictTheWinner(int[] nums) {
        int answer = recurse(nums,0,nums.length-1,1);
        int total_sum = 0;
        for(int num : nums) total_sum += num;
        return answer * 2 >= total_sum;
    }
}
