#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;

int main(){
    int lines = 0;
    scanf("%d",&lines);
    for(int i = 0;i<lines;i++){
        int n;
        scanf("%d",&n);
        vector<int> a(n);
        vector<int> gap(n);
        int maxp = -199998;
        for(int j = 0;j<n;j++){
            scanf("%d",&a[j]);
        }
        int min = a[n-1];
        for(int j = n-2;j>=0;j--){

            gap[j] = a[j] - min;
            
            if(a[j] < min){
                min = a[j];
            }
            a[j] = min;
            if(gap[j]>maxp){
                maxp = gap[j];
            }
        }

        printf("%d\n",maxp);
        
    }

}