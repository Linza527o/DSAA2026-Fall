#include <iostream>
#include <vector>
using namespace std;

void printall(const vector<vector<char>> & chart, int a, int b, int h) {
    for (int row = 0;row<2*b+2*h+1;row++) {
        for (int i = 0;i<2*a+2*b+1;i++) {
            printf("%c",chart[row][i]);
        }
        printf("\n");
    }
};

int main() {
    int lines = 0;
    scanf("%d", &lines);
    for (int k = 0;k<lines;k++) {
        int a = 0;
        int b = 0;
        int h = 0;
        scanf("%d %d %d", &a, &b, &h);
        vector<vector<char>> chart(2*h+2*b+1, vector<char>(2*a+2*b+1,'.'));
        for (int row = 2*b;row<=2*h+2*b;row++) {
            if (row %2 ==0 ) {
                for (int i = 0;i<=2*a;i++) {
                    if (i %2 == 0){chart[row][i] = '+';}
                    else {chart[row][i] = '-';}
                }
            }
            else {
                for (int i = 0;i<=2*a;i++) {
                    if (i%2 == 0){chart[row][i] = '|';}
                }
            }
        }
        //printall(chart, a, b, h);

        int ini = 2*b;
        for (int row = 0;row<2*b;row++) {
            if (row %2 == 0) {
                for (int i = ini;i<=2*a + 2*b - row;i++) {
                    if (i %2 == 0){chart[row][i] = '+';}
                    else {chart[row][i] = '-';}
                }
            }
            else {
                for (int i = ini;i<=2*a + 2*b - row;i++) {
                    if (i %2 != 0){chart[row][i] = '/';}
                }
            }
            ini--;
        }
        //printall(chart, a, b, h);

        ini = 2*b;
        int col = 0;
        while (col <= 2* b) {
            for (int row = 2*b+2*h - ini; row >= col;row--) {
                if (col %2 == 0) {
                    if (row %2 == 0){chart[row][2*a+2*b-col] = '+';}
                    else {chart[row][2*a+2*b-col] = '|';}
                }
                else {
                    if (row % 2 != 0){chart[row][2*a+2*b-col] = '/';}
                }
            }
            ini--;
            col++;
        }
        printall(chart, a, b, h);
    }
}
