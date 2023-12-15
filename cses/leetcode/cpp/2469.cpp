
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    std::vector<double> convertTemperature(double celsius)
    {
        double kelvin = celsius + 273.15;
        double fahrenheit = celsius * 1.8 + 32.0;
        return {kelvin, fahrenheit};
    }
} int main()
{
}