#include<iostream>

int main(){
    int numOfLines;
    scanf("%d",&numOfLines);
    for(int j = 0;j<numOfLines;j++){
        int T[10] = {0};
        int Y[10] = {0};
        int WA[10] = {0};
        int E = 0,S = 0,W = 0,N = 0,B = 0,F = 0,Z = 0;
        
    for(int i = 0;i<13;i++){
        char readNext; 
        char readNextForward;

        scanf(" %c",&readNext);
        if(readNext == 'T'){
            int num = 0;
            scanf("%d",&num);
            T[num]++;
            continue;
        }
        if(readNext == 'Y'){
            int num = 0;
            scanf("%d",&num);
            Y[num]++;
            continue;
        }
        if(readNext == 'E') E++; 
        if(readNext == 'S') S++; 
        if(readNext == 'W') {
            scanf("%1c",&readNextForward);
            if(readNextForward == ' '){W++;}
            else if(readNextForward == '\n'){W++;}
            else{
                WA[readNextForward-48]++;
            }
            
            
        } 
        if(readNext == 'N') N++; 
        if(readNext == 'B') B++; 
        if(readNext == 'F') F++; 
        if(readNext == 'Z') Z++; 
    };
    for(int i = 1;i<=9;i++){
        for(int j = 0; j<WA[i];j++){
            printf("W%d ",i);
        }
    }
    for(int i = 1;i<=9;i++){
        for(int j = 0; j<T[i];j++){
            printf("T%d ",i);
        }
    }
    for(int i = 1;i<=9;i++){
        for(int j = 0; j<Y[i];j++){
            printf("Y%d ",i);
        }
    }
    for(int i = 0;i<E;i++){printf("E ");}
    for(int i = 0;i<S;i++){printf("S ");}
    for(int i = 0;i<W;i++){printf("W ");}
    for(int i = 0;i<N;i++){printf("N ");}
    for(int i = 0;i<B;i++){printf("B ");}
    for(int i = 0;i<F;i++){printf("F ");}
    for(int i = 0;i<Z;i++){printf("Z ");}
    printf("\n");
}
    
}