import java.util.Scanner;

/**
 * Given a string 'S' (composed of digits) and an integer 'X", 
 * the task is to count all the substrings of 'S' that satisfy the following conditions:
 * 
 * The sub-string must not begin with the digit '0'.
 * And the numeric number it represents must be greater than 'X'.
 */

class Solution{
    public static int countSubstrings(String s, int x) {
        int count = 0;
        for(int i = 0; i < s.length(); i++){
            if(s.charAt(i) != '0'){
                StringBuilder temp = new StringBuilder();
                for(int j = i; j < s.length(); j++){
                    temp.append(s.charAt(j));
                    long value = Long.parseLong(temp.toString());
                    if(value > x){
                        count++;
                    }
                }
            }
        }
        return count;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the string(S) and integer X, \n\tS's substrings' value need to greater than X:-");
        String s = scanner.nextLine();
        int x = scanner.nextInt();
        System.out.println("Count: " + countSubstrings(s, x));
        scanner.close();
    }
}