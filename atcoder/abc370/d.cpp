#include <iostream>
#include <vector>
using namespace std;

int H, W, Q;
vector<int> parent, Rank, has_wall;

int find(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

void unite(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY)
    {
        if (Rank[rootX] > Rank[rootY])
        {
            parent[rootY] = rootX;
        }
        else if (Rank[rootX] < Rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else
        {
            parent[rootY] = rootX;
            Rank[rootX]++;
        }
    }
}

int toIndex(int r, int c)
{
    return (r - 1) * W + (c - 1);
}

int main()
{
    cin >> H >> W >> Q;
    parent.resize(H * W);
    Rank.resize(H * W, 0);
    has_wall.resize(H * W, 1);

    // Initialize union-find
    for (int i = 0; i < H * W; ++i)
    {
        parent[i] = i;
    }

    while (Q--)
    {
        int R, C;
        cin >> R >> C;
        int idx = toIndex(R, C);

        if (has_wall[idx])
        {
            has_wall[idx] = 0;

            if (R > 1 && !has_wall[toIndex(R - 1, C)])
            {
                unite(idx, toIndex(R - 1, C));
            }
            if (R < H && !has_wall[toIndex(R + 1, C)])
            {
                unite(idx, toIndex(R + 1, C));
            }
            if (C > 1 && !has_wall[toIndex(R, C - 1)])
            {
                unite(idx, toIndex(R, C - 1));
            }
            if (C < W && !has_wall[toIndex(R, C + 1)])
            {
                unite(idx, toIndex(R, C + 1));
            }
        }
        else
        {
            for (int dr = -1; dr <= 1; ++dr)
            {
                for (int dc = -1; dc <= 1; ++dc)
                {
                    if ((dr == 0 || dc == 0) && dr != dc)
                    {
                        int nr = R + dr, nc = C + dc;
                        while (nr >= 1 && nr <= H && nc >= 1 && nc <= W)
                        {
                            int nIdx = toIndex(nr, nc);
                            if (has_wall[nIdx])
                            {
                                has_wall[nIdx] = 0;
                                unite(idx, nIdx);
                                break;
                            }
                            nr += dr;
                            nc += dc;
                        }
                    }
                }
            }
        }
    }

    int remaining_walls = 0;
    for (int i = 0; i < H * W; ++i)
    {
        if (has_wall[i])
            remaining_walls++;
    }
    cout << remaining_walls << endl;

    return 0;
}
