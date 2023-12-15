// intersection of graph
vector<tuple<string, int, int>> G1;
vector<tuple<string, int, int>> G2;
map<"edge", v1, v2>
    vector<tuple<string, int, int>> G;

// how to find the union of the graphs

for (auto item : map)
{
    map[item] = 1;
}

// or i can check if that map has already the item present, if
//  not present insert item

map.find(item) == map.end()
                      map.insert(item);

// T(n) is the number of factors of n.
//  sum of all factors of n

// SieveOfEratosthenes
// sieve[x] = 0, if x is prime
//            1, otherwise
// algo
for (int x = 2; x <= n; x++)
{
    if (sieve[x])
        continue;
    for (int u = 2x; u <= n; u += x)
    {
        sieve[u] = 1;
    }
}

// extended euclid's algo
// Euclid's Algo : gcd(a,b) = {a , (b=0),
//                         gcd(b,amodb)}
// Extended Euclid's algo:  ax+by = gcd(a,b)
//
// tuple<int,int,int> gcd(int a,int b)
if (b == 0)
    return (1, 0, a);
else
{
    int x, y, g;
    tie(x, y, g) = gcd(b, a % b);
    return (y, x - (a / b) * y, g);
}

// Euler's Theorem:
//   let a and b are two coprime numbers, then gcd(a,b) = 1

// Euler's totient function phi(n):
// gives the number of integer between 1,2,3,...,n that are coprime to n.
//formula for phi(n)


