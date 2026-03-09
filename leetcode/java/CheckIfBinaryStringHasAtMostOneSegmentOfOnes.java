class CheckIfBinaryStringHasAtMostOneSegmentOfOnes {
    public boolean checkOnesSegment(String s){
        int count = 0;
        if(s.length()==0){
            return true;
        }
        if(s.charAt(0)=='1'){
            count+=1;
        }
        for(int i = 1; i < s.length(); i++){
            if(s.charAt(i)=='1' && s.charAt(i-1)!='1'){
                count++;
            }
        }
        System.out.println("final count = "+count);
        return count <= 1;
    }
}