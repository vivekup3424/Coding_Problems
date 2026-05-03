public class RotateString {
    public boolean rotateString(String s, String goal){
        int n = s.length();
        if(s.equals(goal)) return true;
        if(s.length() != goal.length())return false;
        for (int i = 0; i < n; i++) {
           String t = goal.substring(i,n)+goal.substring(0, i);
           System.out.printf("t = %s\n",t);
           if(t.equals(s)) return true;
        }
        return false;
    }
    public boolean approach2(String s, String goal){
        String temp = s + s;
        int n = s.length();
        for(int i = 0; i < n; i++){
            String subStr = temp.substring(i, i+n);
            if(goal.equals(subStr)) return true;
        }
        return false;
    }
}