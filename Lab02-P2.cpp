#include <iostream>
using namespace std;
int main() {
    int lines;
    scanf("%lld",&lines);
    for (int i=0;i<lines;i++) {
        long long n;
        scanf("%lld",&n);
        long long m1;
        m1 = n;
        long long mod = 1000000007;
        long long tmpn;
        long long tmpnpo;
        if (n%2 == 0) {
            tmpn = n/2;
            tmpnpo = n + 1;
        }
        else {
            tmpnpo = (n + 1) / 2;
            tmpn = n;
        }


        m1 = (((((((((tmpn % mod)*(tmpnpo))%mod)*tmpn)%mod)*(tmpnpo))%mod))%mod);
        printf("%d\n",m1);

    }


}
