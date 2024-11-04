class Solution {
	function largest(arr) {
	let maxi = arr[0];
	for (let i = 0; i < arr.length; i++) {
		if (arr[i] > maxi) {
			maxi = arr[i];
		}
	}
	return maxi
}
}
