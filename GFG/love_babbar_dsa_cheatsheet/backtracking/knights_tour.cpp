// Given a N*N board with the Knight placed on the first block of an empty board.
// Moving according to the rules of chess knight must visit each square exactly once.
// Print the order of each cell in which they are visited.

#include <bits/stdc++.h>
using namespace std;
#define MAX 1000
bool visited[MAX][MAX];
int possible_moves_y[] = {3, 3, -3, -3, 1, -1, 1, -1};
int possible_moves_x[] = {1, -1, 1, -1, 3, 3, -3, -3};
bool isValid(int x, int y)
{
    if (x >= 0 and y >= 0 and x < 8 and y < 8 and !visited[x][y])
        return true;
    else
        return false;
}
bool knights_tour(int chess[8][8], int)
{
}
int main()
{
    int chess[8][8];
    int counter = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            chess[i][j] = counter;
            counter++;
        }
    }
    vector<int> empty;
    knights_tour(chess, 0, 0, empty);
    for (int i = 0; i < empty.size(); i++)
    {
        cout << empty[i] << ", ";
    }
    return 0;
}