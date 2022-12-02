#include <bits/stdc++.h>

using namespace std;

#define LOCAL

class MinHeap
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

    int pop()
    {
        int popping = vec[0];
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

        return popping;
    }
};

class MaxHeap
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
            if (vec[par] >= vec[curr])
                return;
            if (vec[par] < vec[curr])
            {
                int tmp = vec[curr];
                vec[curr] = vec[par];
                vec[par] = tmp;
            }
            curr = par;
        }
    }

    int pop()
    {
        int popping = vec[0];
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
                if (vec[child1] > vec[child2])
                    next = child1;
                else
                    next = child2;
            }
            else if (child1 < vec.size())
                next = child1;
            else
                next = child2;

            if (vec[curr] >= vec[next])
                break;
            else
            {
                int tmp = vec[next];
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

    int m, n, tmp;
    vector<int> numbers, thresholds;

    cin >> m >> n;
    while (m--)
    {
        cin >> tmp;
        numbers.push_back(tmp);
    }
    while (n--)
    {
        cin >> tmp;
        thresholds.push_back(tmp);
    }

    MaxHeap maxheap;
    MinHeap minheap;

    int volumn = 1;
    int i = 0;
    for (int t : thresholds)
    {
        while (i < t)
        {

            if (maxheap.vec.size() < volumn)
                maxheap.add(numbers[i]);
            else
            {
                minheap.add(numbers[i]);
                while (minheap.vec[0] < maxheap.vec[0])
                {
                    int n1 = minheap.pop();
                    int n2 = maxheap.pop();
                    minheap.add(n2);
                    maxheap.add(n1);
                }
            }
            i++;
        }

        cout << maxheap.vec[0] << endl;

        volumn++;
        if(minheap.vec.size()!=0)
            maxheap.add(minheap.pop());
    }
}