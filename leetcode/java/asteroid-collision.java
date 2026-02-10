import java.util.Stack;
class Solution{
    public int[] asteroidCollision(int[] asteroids){
        Stack<Integer> stack = new Stack<>();
        for(int asteroid: asteroids){
            boolean isAlive = true;
            while(isAlive && !stack.isEmpty() && (stack.peek()>0 && asteroid<0)){
                int top = stack.peek();
                if(Math.abs(asteroid) > Math.abs(top)){
                    stack.pop();
                }else if(Math.abs(asteroid)==Math.abs(top)){
                    stack.pop();
                    isAlive=false; //the asteroid itself gets destroyed
                }else{
                    isAlive=false;
                }
            }
            if(isAlive){
                stack.push(asteroid);
            }
        }
        int[] result = new int[stack.size()]; //i don't think this would have been possible in c++, no runtime array length
        for(int i = result.length-1; i>=0; i--){
            result[i] = stack.pop();
        }
        return result;
    }
}
