#include <iostream>
#include <vector>

using namespace std;

unsigned int f (unsigned int pos)
{
    return pos & (pos + 1);
}

unsigned int g (unsigned int pos)
{
    return pos | (pos + 1);
}

class BITree {
public:
    BITree (const vector<long long>& arr);

    long long getSum (unsigned int left, unsigned int right);
    void update (unsigned int pos, long long val);

private:
    vector<long long> tree;
    long long prefixSum (unsigned int pos) const;
};

BITree::BITree (const vector<long long>& arr):
    tree (arr)
    {
    for (unsigned int i = 1; i < tree.size(); ++i)
        tree[i] += tree[i - 1];

    for (unsigned int i = tree.size() - 1; i > 0; --i)
        tree[i] -= (f(i) == 0 ? 0 : tree[f(i) - 1]);
    }

long long BITree::getSum (unsigned int left, unsigned int right)
{
    return left == 0 ? prefixSum(right) : (prefixSum(right) - prefixSum(left - 1));
}

void BITree::update (unsigned int pos, long long val)
{
    for (unsigned int i = pos; i < tree.size(); i = g(i))
        tree[i] += val;
}

long long BITree::prefixSum (unsigned int pos) const
{
    long long result = 0;
    for (unsigned int i = pos; ; i = f(i) - 1) {
        result += tree[i];
        if (f(i) == 0) {
            break;
        }
//        i = f(i) - 1;
    }
  return result;
}


int main()
{
    int n;
    cin >> n;
    vector <long long> a(n + 2);
    for (int i = 0; i < n; i++) 
    {
        cin >> a[i];
        if(i % 2 == 1) a[i] *= -1;
    }
    BITree tree(a);
    int m;
    cin >> m;
    while(m--) {
        int q;
        cin >> q;
        if(q == 0) {
            int i;
            long long j;
            cin >> i >> j;
            if(i % 2 == 0) j *= -1;
            int inc = j - a[i - 1];
            tree.update(i - 1, inc);
            a[i - 1] = j;
        } else {
            int l, r;
            cin >> l >> r;
            int sum = tree.getSum(l - 1, r - 1);
            if(l % 2 == 0) sum *= -1;
            cout << sum << endl;
        }
    }
    return 0;
}
