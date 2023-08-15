// Tower of Hanoi

// The Tower of Hanoi game consists of three stacks (left,
// middle and right) and n round disks of different sizes.
// Initially, the left stack has all the disks, in increasing
// order of size from top to bottom.

// The goal is to move all the disks to the right stack
// using the middle stack.On each move you can move the
// uppermost disk from a stack to another stack.In addition,
// it is not allowed to place a larger disk on a smaller disk.

// Your task is to find a solution that minimizes the
// number of moves.

// left rod = 1, aux. rod = 2, right rod = 3
// right rod is the final rod

#include <bits/stdc++.h>
using namespace std;

// Time-complexity = O(2^n)
int toh(char left_rod, char aux_rod, char right_rod, int n)
{
    int num = pow(2, n);
    if (n == 0)
        return 0;
    toh(left_rod, right_rod, aux_rod, n - 1); // left->aux
    cout << left_rod << " " << right_rod << "\n";
    toh(aux_rod, left_rod, right_rod, n - 1); // aux->right
    return num;
}
void print_toh(int n)
{
    cout << pow(2, n) - 1 << "\n";
    return;
}
int main()
{
    int n; // number of disks
    cin >> n;
    print_toh(n);
    toh('1', '2', '3', n);
}