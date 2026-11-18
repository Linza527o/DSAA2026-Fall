#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void mergesort(vector<long long> &a, long long l, long long r) {
    if (l >= r) return;

    long long mid = (l + r) / 2;
    mergesort(a, l, mid);
    mergesort(a, mid + 1, r);

    vector<long long> tmp;
    int i = l;
    int j = mid + 1;

    while (i <= mid && j <= r) {
        if (a[i] < a[j]) {
            tmp.push_back(a[i]);
            i++;
        }
        else {
            tmp.push_back(a[j]);
            j++;
        }
    }

    while (i <= mid) {
        tmp.push_back(a[i]);
        i++;
    }

    while (j <= r) {
        tmp.push_back(a[j]);
        j++;
    }

    for (int k = 0; k < tmp.size(); k++) {
        a[l + k] = tmp[k];
    }
}

int n, k;

int main() {
    cin.tie(nullptr);  // 这两句用于关闭流同步，但关流后不可以混用 cin / scanf
    ios::sync_with_stdio(false);
    cin>>n>>k;
    vector<long long> a(n);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    mergesort(a, 0, n - 1);

    cout << a[k];

    return 0;
}
