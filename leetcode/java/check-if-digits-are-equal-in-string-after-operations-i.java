class Solution {
    public boolean hasSameDigits(String s) {
        while (s.length() > 2) {
            StringBuilder newbornString = new StringBuilder();
            for(int i = 0; i < s.length()-1; i++) {
                int firstDigit = s.charAt(i) - '0';
                int secondDigit = s.charAt(i+1) - '0';
                int newDigit = (firstDigit + secondDigit)%10;
                newbornString.append(newDigit);
            }
            s = newbornString.toString();
        }
        return s.charAt(0) == s.charAt(1);
    }
}