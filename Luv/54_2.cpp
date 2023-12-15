// Binary Exponentiation: Iterative Method | CP Course | EP 54.2

// implementing it using iterative method
#define MAX 1000

int binExpIter(int a, int b)
{
    int ans = 1;
    while (b > 0)
    {
        if (b & 1 == 1) // its odd
        {
            ans = a * ans;
        }
        a = a * a;
        b >> 1;
    }
    return ans;
}

// excercise questionson this topic