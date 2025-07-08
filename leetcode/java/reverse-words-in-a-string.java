class Solution {
	public String reverseWords(String s) {
		// since strings are immutable in java,
		// hence I go on swapping characters inside the string

		String[] splits = s.split("\\s+");
		int i = 0, j = splits.length-1;
		while (i < j) {
			String temp = splits[i];
			splits[i] = splits[j];
			splits[j] = temp;
			i++;
			j--;
		}
		String answer = splits[0];
		for(int i = 1; i < splits.length; i++){
			answer.concat(" ");
			answer.concat(splits[i]);
		}
		return answer;
	}
}
