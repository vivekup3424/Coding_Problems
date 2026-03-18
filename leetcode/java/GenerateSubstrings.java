import java.util.Scanner;

public class GenerateSubstrings {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a new string:-");
        String str = scanner.nextLine();
        for (int i = 0; i < str.length(); i++) {
            StringBuilder temp = new StringBuilder();
            for (int j = i; j < str.length(); j++) {
               temp.append(str.charAt(j));
               System.out.println(temp.toString());
            }
        }
        scanner.close();
    }
}