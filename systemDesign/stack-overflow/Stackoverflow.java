import java.util.*;
//Question asked = +1
//Question answer = +1
//Answer accepeted = +2
//Answer upvoted = +1
//reputation calculation number

public class Stackoverflow {
    private Map<String, Set<String>> questions; //userId to list of questions
    private Map<String, Set<String>> answers;  //question to list of answers
    
    Stackoverflow(){
        questions = new HashMap<>();
        answers = new HashMap<>();
    }

    void askQuestion(String userId, String Question){

    }
}
