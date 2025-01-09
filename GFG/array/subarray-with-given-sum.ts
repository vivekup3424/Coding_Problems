class Solution {
	subarraySum(arr: number[], target: number): number[] | null {
		let n = arr.length
		let i = 0, j = 0, currentSum = 0;
		while (j < n) {
			currentSum += arr[j];
			while (currentSum > target && i < j) {
				currentSum -= arr[i];
				i++;
			}
			if (currentSum == target) {
				return [i + 1, j + 1]
			}
			j++;
		}
	}
}
let A = new Solution()
console.log(A.subarraySum([1, 2, 3, 7, 5], 12))
