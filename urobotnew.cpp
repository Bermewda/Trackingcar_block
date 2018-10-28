#include<stdio.h>
int mapcheck[10][10] = 
{   //0 1 2 3 4 5 6 7 8 9
    {1,1,1,1,1, 1,1,1,1,1},//0
    {1,0,0,0,0, 0,0,0,0,1},//1
    {1,0,0,0,0, 0,0,0,0,1},//2
    {1,0,0,0,0, 0,0,0,0,1},//3
    {1,0,0,0,0, 0,0,0,0,1},//4
    
    {1,0,0,0,0, 0,0,0,0,1},//5
    {1,0,0,0,0, 0,0,0,0,1},//6
    {1,0,0,0,0, 0,0,0,0,1},//7
    {1,0,0,0,0, 0,0,0,0,1},//8
    {1,1,1,1,1, 1,1,1,1,1} //9
};
//block (2,8) (8,3) (6,7)(7,7)

int map[8][8] = 
{   //0 1 2 3 4 5 6 7 8 9
    {1,1,1,1,1, 1,1,1,1,1},//0
    {1,0,0,0,0, 0,0,0,0,1},//1
    {1,0,0,0,0, 0,0,0,0,1},//2
    {1,0,0,0,0, 0,0,0,0,1},//3
    {1,0,0,0,0, 0,0,0,0,1},//4
    
    {1,0,0,0,0, 0,0,0,0,1},//5
    {1,0,0,0,0, 0,0,0,0,1},//6
    {1,0,0,0,0, 0,0,0,0,1},//7
    {1,0,0,0,0, 0,0,0,0,1},//8
    {1,1,1,1,1, 1,1,1,1,1} //9
};


int x=9,y=9;
int di=0; //0 front ,1 left ,2 right,3 back
int ultra = 0;
void checkmap(int x,int y);
void checkblock(int x,int y);
int checkx(int x,int i);
int checky(int y,int i);
void check();
int ultrasonic(int x,int y);

void printmap();
void printxy(int x,int y);
int main(){
    
    check();
    printmap();
    
    return 0;
}

void check(){
    ultra = ultrasonic(x,y);
    printf("%d : (%d,%d), checkfront\n",di,x,y);
    checkblock(x,y);  
}
void checkblock(int x,int y){    
    if(ultra >= 6 && ultra <= 18){
        map[checkx(x,0)][checky(y,0)]=1;
        map[checkx(x,1)][checky(y,1)]=4;        
    }
    else if(ultra >= 36 && ultra <= 47){
        map[checkx(x,0)][checky(y,0)]=1;
        map[checkx(x,1)][checky(y,1)]=1;
        map[checkx(x,2)][checky(y,2)]=4;        
    }
    else if(ultra >= 65 && ultra <= 78){
        map[checkx(x,0)][checky(y,0)]=1;
        map[checkx(x,1)][checky(y,1)]=1;
        map[checkx(x,2)][checky(y,2)]=1;
        map[checkx(x,3)][checky(y,3)]=4;        
    }
    else if(ultra >= 87 && ultra <= 107){
        map[checkx(x,0)][checky(y,0)]=1;
        map[checkx(x,1)][checky(y,1)]=1;
        map[checkx(x,2)][checky(y,2)]=1;
        map[checkx(x,3)][checky(y,3)]=1;
        map[checkx(x,4)][checky(y,4)]=4;        
    }
    else{
        for(int i=0;i<=4;i++){ 
            if( checkx(x,i)>=0 && checkx(x,i)<=7 && checky(y,i)>=0 && checky(y,i)<=7 )      
            {
                map[checkx(x,i)][checky(y,i)]=1;
            }
        }
    }
}
int checkx(int x,int i){
    switch(di){
        case 0: return x-i;
        case 1: return x;
        case 2: return x;
        default: return x+i;
    }
}
int checky(int y,int i){
    switch(di){
        case 0: return y;
        case 1: return y-i;
        case 2: return y+i;
        default: return y;
    }
}
void printmap(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void printxy(int x,int y){
    printf("(%d,%d)\n",x,y);
}
int ultrasonic(int x,int y){
    if(mapcheck[checkx(x,1)][checky(y,1)] > 1){
        return 15;
    }else if(mapcheck[checkx(x,2)][checky(y,2)] > 1){
        return 40;
    }else if(mapcheck[checkx(x,3)][checky(y,3)] > 1){
        return 70;    
    }else if(mapcheck[checkx(x,4)][checky(y,4)] > 1){
        return 90; 
    }else{
        return 255;
    }
}
