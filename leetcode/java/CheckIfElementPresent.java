import java.util.stream.IntStream;

class CheckElement{
    public static void main(String[] args){
        int[] n = {1,2,3,4,5};
        int t = 4;
        boolean isPresent = IntStream.of(n).anyMatch(n1 -> n1 == t);
        System.out.println(isPresent);
    }
}