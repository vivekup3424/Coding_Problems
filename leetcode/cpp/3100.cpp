class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int drank = 0;
        int emptyBottle = 0;
        while (numBottles > 0)
        {
            drank += numBottles;
            emptyBottle += numBottles;
            numBottles = 0;
            while (emptyBottle >= numExchange)
            {
                emptyBottle -= numExchange;
                numBottles++;
                numExchange++;
            }
            
        }
        return drank;
    }
};

int main(int argc, char const *argv[])
{
    int numBottles = 13, numExchange = 6;
    Solution A = Solution();
    int ans= A.maxBottlesDrunk(numBottles, numExchange);
    return 0;
}
