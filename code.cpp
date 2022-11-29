#include <bits/stdc++.h>

using namespace std;

#define LOCAL

class Edge
{
public:
    int out, in, cost;
};

class UnionFind
{
public:
    int num;
    int components;
    vector<int> roots;
    vector<int> depths;

    UnionFind(int num)
    {
        this->num = num;
        components = num;

        for (int i = 0; i < num; i++)
            roots.push_back(i);
        for (int i = 0; i < num; i++)
            depths.push_back(1);
    }

    void unify(int n1, int n2)
    {
        components--;
        int r1 = find_root(n1);
        int r2 = find_root(n2);

        if (depths[r1] == depths[r2])
        {
            depths[r2] += 1;
            roots[r1] = r2;
        }
        else if (depths[r1] < depths[r2])
            roots[r1] = r2;
        else
            roots[r2] = r1;
    }

    int find_root(int n)
    {
        int curr = n;
        while (roots[curr] != curr)
            curr = roots[curr];
        // route compression
        roots[n] = curr;
        return curr;
    }
};

void quicksort(vector<Edge> &edges, int left, int right)
{
    if (left >= right)
        return;

    int t = left, p = left + 1, q = right;
    while (p != q)
    {
        while (edges[q].cost >= edges[t].cost && p != q)
            q--;
        while (edges[p].cost <= edges[t].cost && p != q)
            p++;

        Edge tmp = edges[p];
        edges[p] = edges[q];
        edges[q] = tmp;
    }

    if (edges[t].cost >= edges[p].cost)
    {
        Edge tmp = edges[t];
        edges[t] = edges[p];
        edges[p] = tmp;
        t = p;
    }

    quicksort(edges, left, t - 1);
    quicksort(edges, t + 1, right);
}

int main()
{

#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif

    int N, M;
    cin >> N >> M;
    UnionFind uf(N);
    vector<Edge> edges(M);
    while (M--)
    {
        int x, y, t;
        cin >> x >> y >> t;
        edges[M].out = x;
        edges[M].in = y;
        edges[M].cost = t;
    }

    quicksort(edges, 0, edges.size() - 1);

    int earliest = -1;
    for (int i = 0; i < edges.size(); i++)
    {
        int n1 = edges[i].out - 1;
        int n2 = edges[i].in - 1;
        if (uf.find_root(n1) != uf.find_root(n2))
            uf.unify(n1, n2);
        if (uf.components == 1)
        {
            earliest = edges[i].cost;
            break;
        }
    }

    if (N < 2)
        cout << 0 << endl;
    else
        cout << earliest << endl;
}