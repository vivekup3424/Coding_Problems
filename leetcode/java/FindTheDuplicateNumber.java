class FindTheDuplicateNumber {
    public int findDuplicate(int[] nums){
        int hare = 0, tortoise = 0;
        while(tortoise<nums.length){
            if(nums[hare]==nums[tortoise] && tortoise!=hare){
                return nums[hare];
            }
            hare+=2;
            hare = hare % nums.length;
            tortoise+=1;
        }
        return -1;
    }
}
