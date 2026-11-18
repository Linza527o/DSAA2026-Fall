#include <iostream>
#include <vector>
using namespace std;

void mergeSort(vector<int> &num, int l, int r) {
    if (l >= r) return;

    int mid = l + (r - l) / 2;

    mergeSort(num, l, mid);
    mergeSort(num, mid + 1, r);

    vector<int> tmp;
    int i = l;
    int j = mid + 1;

    while (i <= mid && j <= r) {
        if (num[i] < num[j]) {
            tmp.push_back(num[i]);
            i++;
        } else {
            tmp.push_back(num[j]);
            j++;
        }
    }

    while (i <= mid) {
        tmp.push_back(num[i]);
        i++;
    }

    while (j <= r) {
        tmp.push_back(num[j]);
        j++;
    }

    for (int i = 0; i < tmp.size(); i++) {
        num[l + i] = tmp[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int len;
    cin >> len;

    vector<int> num(len);

    for (int i = 0; i < len; i++) {
        cin >> num[i];
    }

    mergeSort(num, 0, len - 1);

    int nntbf;
    cin >> nntbf;

    for (int i = 0; i < nntbf; i++) {
        int ntbf;
        cin >> ntbf;

        int left = 0;
        int right = len - 1;

        bool isFound = false;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (num[mid] == ntbf) {
                isFound = true;
                break;
            }

            if (num[mid] < ntbf) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        if (isFound) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}