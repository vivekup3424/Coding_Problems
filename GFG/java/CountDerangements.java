public class CountDerangements {

    public int recurse(int n){
        if(n==1) return 0;
        else if(n==2) return 1;
        else return (n-1) * (recurse(n-1) + recurse(n-2));
    }
    public int derangeCount(int n){
        return recurse(n);
    }
}