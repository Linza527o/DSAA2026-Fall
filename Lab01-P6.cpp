#include <iostream>

using namespace std;

bool check(int b[4][10]) {

    // b1：当前这一轮的所有可能状态
    // b2：下一轮的所有可能状态
    int b1[20][4][10] = {0};
    int b2[20][4][10] = {0};

    int cnt = 1;

    // 把最开始的 b 放进 b1[0]
    for(int j = 0; j < 4; j++){
        for(int i = 0; i <= 9; i++){
            b1[0][j][i] = b[j][i];
        }
    }


    // 已经去掉雀头，所以剩下12张
    // 一共要组成4组
    for(int k = 0; k < 4; k++){

        int cnt2 = 0;

        // 检查当前所有可能状态
        for(int a = 0; a < cnt; a++){

            int m = -1;
            int n = -1;

            // 找第一张还存在的牌
            for(int j = 0; j < 4; j++){
                for(int i = 1; i <= 9; i++){

                    if(b1[a][j][i] > 0){
                        m = j;
                        n = i;
                        break;
                    }
                }

                if(m != -1){
                    break;
                }
            }


            // -------------------
            // 尝试刻子
            // -------------------
            if(b1[a][m][n] >= 3){

                // 复制当前状态
                for(int j = 0; j < 4; j++){
                    for(int i = 0; i <= 9; i++){
                        b2[cnt2][j][i] = b1[a][j][i];
                    }
                }

                // 去掉刻子
                b2[cnt2][m][n] -= 3;

                cnt2++;
            }


            // -------------------
            // 尝试顺子
            // -------------------

            // m == 3 表示 z，不能组成顺子
            // n <= 7，因为需要 n,n+1,n+2
            if(m != 3 &&
               n <= 7 &&
               b1[a][m][n + 1] > 0 &&
               b1[a][m][n + 2] > 0){

                // 复制当前状态
                for(int j = 0; j < 4; j++){
                    for(int i = 0; i <= 9; i++){
                        b2[cnt2][j][i] = b1[a][j][i];
                    }
                }

                // 去掉顺子
                b2[cnt2][m][n]--;
                b2[cnt2][m][n + 1]--;
                b2[cnt2][m][n + 2]--;

                cnt2++;
            }
        }


        // 一个可能状态都没有
        if(cnt2 == 0){
            return false;
        }


        // 把 b2 复制回 b1，进入下一轮
        cnt = cnt2;

        for(int a = 0; a < cnt; a++){
            for(int j = 0; j < 4; j++){
                for(int i = 0; i <= 9; i++){
                    b1[a][j][i] = b2[a][j][i];
                }
            }
        }
    }


    // 四轮结束
    // 检查有没有某个状态已经把牌全部用完
    for(int a = 0; a < cnt; a++){

        bool empty = true;

        for(int j = 0; j < 4; j++){
            for(int i = 1; i <= 9; i++){

                if(b1[a][j][i] != 0){
                    empty = false;
                    break;
                }
            }

            if(!empty){
                break;
            }
        }

        if(empty){
            return true;
        }
    }

    return false;
}


int main(){

    int lines = 0;

    scanf("%d",&lines);

    for(int k = 0; k < lines; k++){

        int b[4][10] = {0};
        int copy[4][10] = {0};

        bool boh = false;


        // -------------------
        // 输入
        // -------------------
        for(int i = 0; i < 14; i++){

            char category;
            int num = 0;

            scanf("%d",&num);
            scanf("%c",&category);

            switch(category){

            case 'b':
                b[0][num]++;
                break;

            case 's':
                b[1][num]++;
                break;

            case 'w':
                b[2][num]++;
                break;

            case 'z':
                b[3][num]++;
                break;
            }
        }


        // 保存原始牌
        for(int j = 0; j < 4; j++){
            for(int i = 0; i <= 9; i++){
                copy[j][i] = b[j][i];
            }
        }


        // -------------------
        // 找所有可能的雀头
        // -------------------

        int indexm[40] = {0};
        int indexn[40] = {0};

        int cnt = 0;

        for(int j = 0; j < 4; j++){
            for(int i = 1; i <= 9; i++){

                if(b[j][i] >= 2){

                    indexm[cnt] = j;
                    indexn[cnt] = i;

                    cnt++;
                }
            }
        }


        // -------------------
        // 一个一个尝试雀头
        // -------------------

        for(int cnt2 = 0; cnt2 < cnt; cnt2++){

            if(boh){
                break;
            }

            int m = indexm[cnt2];
            int n = indexn[cnt2];


            // 每次先恢复到完整14张牌
            for(int j = 0; j < 4; j++){
                for(int i = 0; i <= 9; i++){
                    b[j][i] = copy[j][i];
                }
            }


            // 去掉当前尝试的雀头
            b[m][n] -= 2;


            // 检查剩下12张
            if(check(b)){
                boh = true;
            }
        }


        if(boh){
            printf("Blessing of Heaven\n");
        }
        else{
            printf("Bad luck\n");
        }
    }

    return 0;
}