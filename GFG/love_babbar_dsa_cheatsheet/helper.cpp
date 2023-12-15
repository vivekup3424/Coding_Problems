#include <bits/stdc++.h>
using namespace std;
int main()
{
    int N;
    cin >> N;
    vector<int> V(N);
    for (int i = 0; i < N; i++)
    {
        cin >> V[i];
    }
}
bool isNegative(int a) { return a < 0; }
bool isPositive(int a) { return a >= 0; }
static long gcd(long a, long b)
{
    long r, i;
    while (b != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}
int max(int A, int B)
{
    if (A >= B)
        return A;
    else
        return B;
}
int min(int A, int B)
{
    if (A <= B)
        return A;
    else
        return B;
}
void printVector(vector<int> V)
{
    for (int i = 0; i < V.size(); i++)
    {
        cout << V[i] << " ";
    }
    cout << "\n";
}

void swap(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}
void printArray(int *a, int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << *(a + i) << " ";
    }
    cout << "\n";
}
int binary_search(vector<int> a, int low, int high, int value)
{
    int mid = low + (high - low) / 2;
    while (low < high)
    {
        if (value = a[mid])
            return mid;
        else if (value > a[mid])
        {
            low = mid + 1;
            mid = low + (high - low) / 2;
        }
        else if (value < a[mid])
        {
            high--;
            mid = low + (high - low) / 2;
        }
    }
    return mid;
}