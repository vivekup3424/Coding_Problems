import java.util.ArrayDeque;
import java.util.Queue;

class Solution{
    //this code is wrong, will solve it again later
    public String predictPartyVictory(String senate){
        Queue<Character> queue = new ArrayDeque<>();
        Character lastPlayer = null;
        for(int i = 0; i < senate.length(); i++){
            char current = senate.charAt(i);
            if(!queue.isEmpty() && queue.peek()!=current){
                lastPlayer = queue.poll();
                //kick out the new senate and the present send who kicked has expired his move
            }else{
                queue.add(current);
            }
        }
        if(queue.isEmpty()){
            return lastPlayer == 'D' ? "Dire" : "Radiant";
        }
        return queue.peek() == 'D' ? "Dire" : "Radiant";
    }
}