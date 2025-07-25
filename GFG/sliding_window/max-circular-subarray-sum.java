import java.util.*;

class Solution {
	public int maxCircularSum(int arr[]) {
		int max_so_far = Integer.MIN_VALUE;
		int arrLength = arr.length;
		int temp[] = new int[2 * arrLength];
		for (int i = 0; i < arrLength; i++) {
			temp[i] = arr[i];
		}
		for (int i = 0; i < arrLength; i++) {
			temp[arrLength + i] = arr[i];
		}
		for (int i = 0; i < temp.length; i++) {
			int current_sum = 0;
			for (int j = i; j < temp.length; j++) {
				if (j - i + 1 > arrLength) {
					break;
				}
				current_sum += temp[j];
				max_so_far = Math.max(max_so_far, current_sum);
			}
		}
		return max_so_far;
	}

	public int slidingWindow(int arr[]) {
		int max_so_far = Integer.MIN_VALUE, current_sum = 0;
		int arrLength = arr.length;
		int temp[] = new int[2 * arrLength];
		for (int i = 0; i < arrLength; i++) {
			temp[i] = arr[i];
		}
		for (int i = 0; i < arrLength; i++) {
			temp[arrLength + i] = arr[i];
		}
		int l = 0, r = 0;
		while(l<r){
			current_sum += temp[r];
			while()
			max_so_far = Math.max(max_so_far, current_sum);
		}
		return max_so_far;
	}
}