#include<cstring>
#include<iostream>
using namespace std;
constexpr int i1 = 173;
constexpr int SIZE = 100005;
constexpr int M = 1000003;
struct HashTable {
    struct Node {
        int next, value, key;
    } data[SIZE];

    int head[M], size;
    //head 数组是用来做什么的？
    // head 是用来存哈希桶的头的

    int f(int key) { return (key % M + M) % M; }

    int get(int key) {
        for (int p = head[f(key)]; p; p = data[p].next)
            if (data[p].key == key) return data[p].value;
        //如果 存数据的数组 的key位置 的数值
        return -1;
    }

    int modify(int key, int value) {
        for (int p = head[f(key)]; p; p = data[p].next)
            if (data[p].key == key) return data[p].value = value;
        // 如果密钥是匹配的 那么久更新这个位置的数值
        return -1;
        //否则返回-1
    }

    int add(int key, int value) {
        // if (get(key) != -1) return -1;
        // //如果不是空的 那就不允许添加
        data[++size] = Node{head[f(key)], value, key};
        //否则 继续执行
        //先用这个size的指针 在data的那一位添加一个下一个为Head中 f(key)位置的
        head[f(key)] = size;
        //把f(key)位置的这个head值改成size 
        return value;
        //返回添加的值
    }
    int hashValue(string str) {
        int hash = 0;
        for (char c : str) {
            hash = (hash * i1 + c + 1) % M;
        }
        return hash;
    }
    void clear() {
        memset(head, 0, sizeof(head));
        size = 0;
    }


};
HashTable table;
bool match(long long hash, long long posB, long long len,
           string &a, string &b) {

    for (long long p = table.head[table.f(hash)];
         p;
         p = table.data[p].next) {

        if (table.data[p].key == hash &&
            a.compare(table.data[p].value, len, b, posB, len) == 0) {
            return true;
            }
         }

    return false;
}
int checkLen(int len, string &a, string &b) {
    int ini = table.hashValue(a.substr(0,len));

    int power = 1;

    for (int i = 1; i < len; i++) {
        power = power * i1 % M;
    }
    table.add(ini,0);
    for (int i = len; i < a.length(); i++) {
        ini = (ini - (a[i-len] + 1) * power % M + M) % M;
        ini = (ini * i1 + a[i] + 1) % M;
        table.add(ini, i-len+1);
    }


    ini = table.hashValue(b.substr(0,len));
    if ((match(ini, 0, len, a, b))) return 1;
    for (int i = len; i < b.length(); i++) {
        ini = (ini - (b[i-len] + 1) * power % M + M) % M;
        ini = (ini * i1 + b[i] + 1) % M;
        if (table.get(ini) != -1) {
            if (match(ini,i-len+1,len,a,b)){return 1;}
        }
    }
    return -1;

}



int main() {
    string a,b;
    cin>>a>>b;
    int left = 0;
    int right = min(a.length(), b.length());


    while (left<right) {
        int mid = (left + right + 1) / 2;
        table.clear();
        if (checkLen(mid, a, b) == 1) {
            left = mid;
        }
        else {
            right = mid - 1;
        }

    }
    cout<<left<<endl;

}