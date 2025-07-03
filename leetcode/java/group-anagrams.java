import java.util.*;

class Solution {
	// left and right are inclusive indices
	public void mergeSort(char[] arr, int left, int right) {
		//this approach is bad, since its doing change into the string itself
		// probably I can create a copy of the string and then sort it
		// using this approach
		if (left < right) {
			int mid = (left + right) / 2;
			mergeSort(arr, left, mid);
			mergeSort(arr, mid + 1, right);
			merge(arr, left, mid, right);
		}
		return;
	}

	public void merge(char[] arr, int left, int mid, int right) {
		int i = left, j = mid, k = 0;
		char[] temp = new char[right - left + 1];
		while (i <= mid && j <= right) {
			if (arr[i] < arr[j]) {
				temp[k++] = arr[i++];
			}else {
				temp[k++] = arr[j++];
			}
		}
		while (i <= mid) {
			temp[k++] = arr[i++];
		}
		while (j <= right) {
			temp[k++] = arr[j++];
		}
		for(int i = 0; i < temp.length; i++) {
			arr[left + i] = temp[i];
		}
	}

	public List<List<String>> groupAnagrams(String[] strs) {
		HashMap<String, List<String>> map = new HashMap<>();
		for(int i =0;i < strs.length; i++){
			char[] arr = strs[i].toCharArray();
			mergeSort(arr, i, arr.length - 1);
			String sortedStr = new String(arr);
			i
		}
		List<List<String>> result = new ArrayList<>();
		return result;
	}
}
