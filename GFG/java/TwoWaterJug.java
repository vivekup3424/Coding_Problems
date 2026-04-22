public class TwoWaterJug {
    public int recurse(int volumeOne, int volumeTwo, int capacityOne, int capacityTwo, int target, int steps){
        if (volumeOne > capacityOne || volumeTwo > capacityTwo || volumeOne < 0 || volumeTwo < 0){
            return Integer.MAX_VALUE;
        }
        else if(volumeOne == target || volumeTwo == target){
            return steps;
        }


        
    }
    public int minSteps(int m, int n, int d){

    }
}