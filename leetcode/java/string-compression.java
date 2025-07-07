class Solution {
	public int compress(char[] chars) {
		StringBuilder temp = new StringBuilder();
		Integer i = 0;
		while (i < chars.length) {
			Integer current_length = 0;
			Character current_char = chars[i];
			while (i < chars.length && chars[i] == current_char) {
				current_length++;
				i++;
			}
			temp.append(current_char);
			if (current_length > 1) {
				String lengthString = current_length.toString();
				temp.append(lengthString);
			}
		}
		System.out.println(temp);
		for (int r = 0; r < temp.length(); r++) {
			chars[r] = temp.charAt(r);
		}
		return temp.length();
	}
}
