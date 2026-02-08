public class ArrayDemo {
    private static void renderBlob(int value){
        for (int j = 0; j < value; j++) {
           System.out.print("█");
        }
    }
    public static void main(String[] args) {
        int[] anArray = new int[10];
        for (int i = 0; i < anArray.length; i++) {
            anArray[i] = i+1;
        }
        for (int i = 0; i < anArray.length; i++) {
            System.out.printf("Element at index %d = %2d: ", i, anArray[i]);
            renderBlob(anArray[i]);
            System.out.println();
        }
    }
    
}
