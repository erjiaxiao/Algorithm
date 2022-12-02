#include <bits/stdc++.h>

using namespace std;

#define LOCAL

class Pair
{

public:
    int value, index;

    Pair() {}

    Pair(int index, int value)
    {
        this->index = index;
        this->value = value;
    }
};

class Heap
{

public:
    vector<Pair> vec;

    void add(Pair x)
    {
        vec.push_back(x);

        int curr = vec.size() - 1, par;
        while (curr != 0)
        {
            par = (curr - 1) / 2;
            if (vec[par].value <= vec[curr].value)
                return;
            if (vec[par].value > vec[curr].value)
            {
                Pair tmp = vec[curr];
                vec[curr] = vec[par];
                vec[par] = tmp;
            }
            curr = par;
        }
    }

    Pair pop()
    {
        Pair popping = vec[0];
        vec[0] = vec[vec.size() - 1];
        vec.pop_back();

        int curr = 0, next;
        while (true)
        {
            int child1 = curr * 2 + 1;
            int child2 = curr * 2 + 2;

            if (child1 >= vec.size() && child2 >= vec.size())
                break;
            else if (child1 < vec.size() && child2 < vec.size())
            {
                if (vec[child1].value < vec[child2].value)
                    next = child1;
                else
                    next = child2;
            }
            else if (child1 < vec.size())
                next = child1;
            else
                next = child2;

            if (vec[curr].value <= vec[next].value)
                break;
            else
            {
                Pair tmp = vec[next];
                vec[next] = vec[curr];
                vec[curr] = tmp;
            }
            curr = next;
        }

        return popping;
    }
};

int main()
{

#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    vector<vector<int>> equations;
    while (n--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        vector<int> curr{a, b, c, 1};
        equations.push_back(curr);
    }

    Heap heap;
    for (int i = 0; i < equations.size(); i++)
    {

        int value = equations[i][0] * equations[i][3] * equations[i][3] +
                    equations[i][1] * equations[i][3] +
                    equations[i][2];
        Pair pair(i, value);
        heap.add(pair);
    }

    while (m--)
    {

        Pair curr = heap.pop();

        if (m == 0)
            cout << curr.value << endl;
        else
            cout << curr.value << " ";

        equations[curr.index][3] += 1;
        curr.value = equations[curr.index][0] * equations[curr.index][3] * equations[curr.index][3] +
                     equations[curr.index][1] * equations[curr.index][3] +
                     equations[curr.index][2];
        heap.add(curr);
    }
}