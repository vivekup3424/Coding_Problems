
#include <bits/stdc++.h>
using namespace std;
class ParkingSystem1
{
public:
    int big, medium, small;
    ParkingSystem(int big, int medium, int small)
    {
        this->big = big;
        this->medium = medium;
        this->small = small;
    }
    bool addCar(int carType)
    {
        switch (carType)
        {
        case 1: // big
        {
            if (this->big > 0)
            {
                this->big--;
                return true;
            }
            else
                return false;
            break;
        }
        case 2: // medium
        {
            if (this->medium > 0)
            {
                this->medium--;
                return true;
            }
            else
                return false;
            break;
        }
        case 3: // small
        {
            if (this->small > 0)
            {
                this->small--;
                return true;
            }
            else
                return false;
            break;
        }
        default:
        {
            return false;
            break;
        }
        }
    }
};
class ParkingSystem
{
public:
    vector<int> spots;
    ParkingSystem(int big, int medium, int small)
    {
        spots = {0, big, medium, small};
    }
    bool addCar(int carType)
    {
        if (spots[carType] > 0)
        {
            spots[carType]--;
            return true;
        }
        return false;
    }
};
int main()
{
}