#include <bits/stdc++.h>

using namespace std;

#define LOCAL

class Heap
{

public:
    vector<int> vec;

    void add(int x)
    {
        vec.push_back(x);

        int curr = vec.size() - 1, par;
        while (curr != 0)
        {
            par = (curr - 1) / 2;
            if (vec[par] <= vec[curr])
                return;
            if (vec[par] > vec[curr])
            {
                int tmp = vec[curr];
                vec[curr] = vec[par];
                vec[par] = tmp;
            }
            curr = par;
        }
    }

    void pop()
    {
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
                if (vec[child1] < vec[child2])
                    next = child1;
                else
                    next = child2;
            }
            else if (child1 < vec.size())
                next = child1;
            else
                next = child2;

            if (vec[curr] <= vec[next])
                break;
            else
            {
                int tmp = vec[next];
                vec[next] = vec[curr];
                vec[curr] = tmp;
            }
            curr = next;
        }
    }
};

int main()
{

#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif

    Heap heap;
    int n, op, x;

    cin >> n;

    while (n--)
    {
        cin >> op;

        if (op == 1)
        {
            cin >> x;
            heap.add(x);
        }
        else if (op == 2)
            cout << heap.vec[0] << endl;
        else
            heap.pop();
    }
}