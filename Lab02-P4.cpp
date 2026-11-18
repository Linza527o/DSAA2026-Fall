//
// Created by Linza on 2026/9/16.
//

#include<iostream>
using namespace std;
int main() {
    long long  n,m;
    scanf("%lld %lld",&n,&m);
    long long product = 1;
    long long producttmp = 1;
    if (n<=3) {


        for (int i = 1; i <= n; i++) {
            producttmp *= i;
        }

        long long producttmp2 = 1;

        for (int i = 1; i <= producttmp; i++) {
            producttmp2 *= i;
        }

        long long product = 1;

        for (int i = 1; i <= producttmp2; i++) {
            product *= i;
            product %= m;
        }
        cout << product << endl;
    }
    else {
        cout << 0 << endl;
    }
}