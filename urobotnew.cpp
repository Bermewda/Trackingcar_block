#include<stdio.h>

int x=9,y=9;
int di=0; //0 front ,1 left ,2 right,3 back
int ultra = 0;
int bx=0,by=0;
int bx1=0,by1=0,bx2=0,by2=0;
int status = 0;
int box2=0;

void front(){
    switch(di){
        case 0:x--;break;
        case 1:y--;break;
        case 2:y++;break;
        default:x++;break;
    }
    printf(" front");
}
void left(){
    switch(di){
        case 0:di=1;break;
        case 1:di=3;break;
        case 2:di=0;break;
        default:di=2;break;
    }
    printf(" left");
}
void right(){
    switch(di){
        case 0:di=2;break;
        case 1:di=0;break;
        case 2:di=3;break;
        default:di=1;break;
    }
    printf(" right");
}
void back(){
    switch(di){
        case 0:x++;break;
        case 1:y++;break;
        case 2:y--;break;
        default:x--;break;
    }
    printf(" back");
}
int mapone[10][10] =  //changemap at 
{   //0 1 2 3 4 5 6 7 8 9
    {81,81,81,81,81, 81,81,81,81,81},//0
    {81,81,81,81,81, 81,81,81,81,81},//1
    {81,81,81,81,81, 81,81,81,81,81},//2
    {81,81,81,81,81, 81,81,81,81,81},//3
    {81,81,81,81,81, 81,81,81,81,81},//4
    
    {81,81,81,81,81, 81,81,81,81,81},//5
    {81,81,81,81,81, 81,81,81,81,81},//6
    {81,81,81,81,81, 81,81,81,81,81},//7
    {81,81,81,81,81, 81,81,81,81,81},//8
    {81,81,81,81,81, 81,81,81,81,81} //9
};

int map[10][10] =
{   //0 1 2 3 4 5 6 7 8 9
	{1,1,1,1,1, 1,1,1,1,1},//0
	{1,1,1,1,1, 6,9,1,1,1},//1
	{1,1,6,9,1, 1,1,1,1,1},//2
	{1,1,1,1,1, 1,1,1,1,1},//3
	{1,1,1,1,1, 1,1,1,1,1},//4

	{1,1,1,1,1, 1,1,1,1,1},//5
	{1,1,9,1,1, 6,1,9,1,1},//6
	{1,1,1,1,1, 6,1,1,1,1},//7
	{1,1,1,1,1, 1,1,1,1,1},//8
	{1,1,1,1,1, 1,1,1,1,1} //9
};
/*
void checkblock(int x,int y);

void checkmap();
int ultrasonic(int x,int y);
*/
int checkxf(int x);
int checkyf(int y);
int checkxl(int x);
int checkyl(int y);
int checkxr(int x);
int checkyr(int y);
int checkxb(int x);
int checkyb(int y);

int checkxne(int x);
int checkyne(int y);
int checkxnw(int x);
int checkynw(int y);
int checkxse(int x);
int checkyse(int y);
int checkxsw(int x);
int checkysw(int y);

void printmap(int map[][10]);
void printxy(int x,int y);

void findone();
void findtwo();
void findwall(int bx,int by);
void findwall2(int bx1,int by1,int bx2,int by2);
void change2();
void checkprekeep();
int checkmap2box();

int checkoor(int x,int y);
int checkwall(int x,int y);
void changeone(int bx,int by);
void changetwo(int bx1,int by1,int bx2,int by2);
int min2(int a, int b);
int min3(int a, int b, int c);
int min4(int a, int b, int c, int d);

void move();
void min2way(int a, int b,int checkw);
void min3way(int a, int b, int c);
void prekeep(int bx ,int by);
void keep();

void checkleftbox1(int x, int y);
void checkrightbox1(int x, int y);
void checkbackbox1(int x,int y);

int checkwallgoal(int bx,int by); //check wall around place
int checkdiplace(int bx,int by); //check position between car and place
void preplace1(int bx,int by);

void findboxsmall();
void findgoalboxsmall();

void findboxbig();
void findgoalboxbig();
//****block (1,7) (7,2) (5,6)(6,6)****//

int main(){

    //find boxmall 1 : Round 1
    findboxsmall();

    bx=7;
    by=2;

    //find goal
    findgoalboxsmall();

    //printmap(map);
    printf("------------------------------ Small Box ------------------------------\n");
    //find boxmall 1 : Round 2
    findboxsmall();

    bx=1;
    by=7;

    //find goal
    findgoalboxsmall();

    //printmap(map);

    //find boxbig 
    printf("------------------------------ Big Box ------------------------------\n");

    findboxbig();

    bx1=5;
    by1=6;
    bx2=6;
    by2=6;
    
    findgoalboxbig();

    printmap(map); 

    return 0;
}

////////////////////////////// box small
void findboxsmall(){
    findone();
    findwall(bx,by);
    map[bx][by]=1;
    for(int i=0;i<15;i++){
        changeone(bx,by);
    }     
    printmap(mapone);

    while(x!=bx || y!=by){
        if(mapone[x][y]==1){
            break; //keepblock
        }else{
            printxy(x,y);
            move();
            
        }        
        
    }
    prekeep(bx,by);
    keep();
    
    printf("\nkeep block\n\n");
    status = 1;
}
void findgoalboxsmall(){
    
    printxy(x,y);
    printxy(bx,by);
    for(int i=0;i<15;i++){
        changeone(bx,by);
    }  
    printmap(mapone);

    //int count =0;
    while(x!=bx || y!=by)
    //while(count != 20)
    {
        if(mapone[x][y]==1){
            break; //keepblock
        }else{
            move();
            printxy(x,y);
        }  
       // count++;
    } 
    preplace1(bx,by);
    printxy(x,y);
    printf("\nplace box\n\n");
    status = 0;
    map[bx][by]=9;
}

void findboxbig(){

    findtwo();
    printxy(x,y);
    printxy(bx1,by1);
    printxy(bx2,by2);
    findwall2(bx1,by1,bx2,by2);   
    map[bx1][by1]=1;
    map[bx2][by2]=1;
    if(bx1 == bx2){//hori  
        mapone[bx1-1][by1]=99;
        mapone[bx2-1][by2]=99;
        mapone[bx1+1][by1]=99;
        mapone[bx2+1][by2]=99;      
        box2=1;
    }else{//vert 
        mapone[bx1][by1-1]=99;
        mapone[bx2][by2-1]=99;
        mapone[bx1][by1+1]=99;
        mapone[bx2][by2+1]=99; 
        box2=2;        
    }
    for(int i=0;i<15;i++){
        changetwo(bx1,by1,bx2,by2);        
    }    
    
    printmap(mapone);
    while((x!=bx1 || y!=by1 ) || (x!=bx2 || y!=by2 )){
        if(mapone[x][y]==1){
            break; //keepblock
        }else{
            move();
            printxy(x,y);
        }        
        
    }    
    checkprekeep();
    keep();
    printxy(x,y);    
    printf("\nkeep block\n\n");
    status = 1;
    if(bx1 == bx2){//hori
        if (map[bx1-1][by1] !=9){
            mapone[bx1-1][by1]=1;
        }
        if(map[bx2-1][by2] !=9){
            mapone[bx2-1][by2]=1;
        }
        if(map[bx1+1][by1] !=9){
            mapone[bx1+1][by1]=1;
        }
        if(map[bx2+1][by2] !=9){
            mapone[bx2+1][by2]=1; 
        }
    }else{//vert 
        if (map[bx1][by1-1] !=9){
            mapone[bx1][by1-1]=1;
        }
        if(map[bx2][by2-1] !=9){
            mapone[bx2][by2-1]=1;
        }
        if(map[bx1][by1+1] !=9){
            mapone[bx1][by1+1]=1;
        }
        if(map[bx2][by2+1] !=9){
            mapone[bx2][by2+1]=1;
        }
    }

}
void findgoalboxbig(){

    int count =0;
    printxy(x,y);
    printxy(bx1,by1);
    printxy(bx2,by2);
    int two=0;
    two = checkmap2box(); 
    change2();
    if(mapone[5][5]!=99){
        mapone[5][5]=99;
    }
    if(mapone[6][5]!=99){
        mapone[6][5]=99;
    }
    if(mapone[5][7]!=99){
        mapone[5][7]=99;
    }
    if(mapone[6][7]!=99){
        mapone[6][7]=99;
    }
    if(two>1){
       for(int i=0;i<15;i++){
            changeone(bx,by);
        } 
        while(x!=bx || y!=by ){
        //while(count != 10){
            
                move();
                printxy(x,y);
            
            //count++;
        }

    }else{
        for(int i=0;i<15;i++){
            changetwo(bx1,by1,bx2,by2); 
        }
        while((x!=bx1 || y!=by1 ) || (x!=bx2 || y!=by2 )){
    //while(count != 10){
            if(mapone[x][y]==1){
                break; //keepblock
            }else{
                move();
                printxy(x,y);
            }  
            //count++;
        }
    }
    printmap(mapone); 
    if(map[5][5]!=9){
        mapone[5][5]=1;
    }
    if(map[6][5]!=9){
        mapone[6][5]=1;
    }
    if(map[5][7]!=9){
        mapone[5][7]=1;
    }
    if(map[6][7]!=9){
        mapone[6][7]=1;
    }
    printmap(mapone); 
    for(int i=0;i<15;i++){
            changetwo(bx1,by1,bx2,by2); 
    }
    printmap(mapone); 

    if(x==4){
        preplace1(bx1,by1);
    }
    if(x=7){
        preplace1(bx2,by2);
    }    
    printxy(x,y);
    printf("\nplace box\n\n");
    status = 0;
    map[bx1][by1]=9;
    map[bx2][by2]=9; 
}
////////////////////////////// print
void printmap(int map[][10]){
    printf("\n 0  1  2  3  4  5  6  7  8  9 \n\n");
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            printf("%2d ",map[i][j]);
        }
        printf("  %d   ",i);
        printf("\n");
    }
    printf("\n");
}

void printxy(int x,int y){
    printf("\n%d : (%d,%d)",di,x,y);
}

////////////////////////////// find box one
void findone(){
    int count = 0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(map[i][j]==6 && count ==0){
                if(map[i+1][j] != 6 && map[i][j+1] != 6 && map[i-1][j] != 6 && map[i][j-1] != 6){
                    bx = i;
                    by = j;
                    mapone[i][j]=0;
                    count++;
                }                    
            }
            
        }
    }
    
}
void findwall(int bx,int by){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(map[i][j]>1){
                //wall[i][j]=1;
                mapone[i][j]=99;
            }
        }
    }
    //wall[bx][by]=0;
    mapone[bx][by]=0;
}
void findtwo(){
    int count =0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(map[i][j]==6){
                //if(map[i+1][j] != 6 && map[i][j+1] != 6 && map[i-1][j] != 6 && map[i][j-1] != 6){
                if(count==0){
                    bx1 = i;
                    by1 = j;
                    mapone[i][j]=0; 
                    count++;
                }
                else if(count==1){
                    bx2 = i;
                    by2 = j;
                    mapone[i][j]=0; 
                    count++;
                }else{
                    break;
                }
                    
                //}                    
            }
            
        }
    }
    
}
void findwall2(int bx1,int by1,int bx2,int by2){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(map[i][j]>1){
                //wall[i][j]=1;
                mapone[i][j]=99;
            }
        }
    }
    //wall[bx][by]=0;
    mapone[bx1][by1]=0;
    mapone[bx2][by2]=0;
    // if(bx1 == bx2){//hori  
    //     mapone[bx1-1][by1]=99;
    //     mapone[bx2-1][by2]=99;
    //     mapone[bx1+1][by1]=99;
    //     mapone[bx2+1][by2]=99;      
    //     box2=1;
    // }else{//vert 
    //     mapone[bx1][by1-1]=99;
    //     mapone[bx2][by2-1]=99;
    //     mapone[bx1][by1+1]=99;
    //     mapone[bx2][by2+1]=99; 
    //     box2=2;
    // }
    // printf("%d\n",box2);
}
void change2(){
    ///*
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(map[i][j] == 9){
                mapone[checkxf(i)][checkyf(j)]=99;
                mapone[checkxr(i)][checkyr(j)]=99;
                mapone[checkxl(i)][checkyl(j)]=99;
                mapone[checkxb(i)][checkyb(j)]=99;

                mapone[checkxse(i)][checkyse(j)]=99;
                mapone[checkxsw(i)][checkysw(j)]=99;
                mapone[checkxne(i)][checkyne(j)]=99;
                mapone[checkxnw(i)][checkynw(j)]=99;
            }
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(i==9 || j==9 || i==0 || j==0 ){
                mapone[i][j]=1;
            }
        }
    }
    if(map[4][6]!=9){
        mapone[4][6]=1;
    }
    if(map[7][6]!=9){
        mapone[7][6]=1;
    }

    
   
    mapone[bx1][by1]=0;
    mapone[bx2][by2]=0; 
    //*/ 

}
void checkprekeep(){
    if(box2==1){ //hori
        if(mapone[x][y+1] == mapone[bx1][by1]){
            prekeep(bx1,by1);
        }else{
            prekeep(bx2,by2);
        }
    }else{
        if(mapone[x+1][y] == mapone[bx1][by1]){
            
            prekeep(bx1,by1);
        }else{
            prekeep(bx2,by2);
        }
    }
    
}
//for 2 box
int checkmap2box(){
    int two=0;
    by=6;
    if(map[4][by]!=9 && map[7][by]!=9){
        if(map[8][by]!=9){
            bx=7;
            two=2;
        }else if(map[3][by]!=9 && map[2][by]!=9 && map[1][by]!=9){
            bx=4;
            two=2;
        }else{
            two=1;
        }  
        
    }else if(map[4][by]==9){
        bx=7;
        two=3;
    }else if(map[7][by]==9){
        bx=4;
        two=3;
    }
    return two;
}
////////////////////////////// change map
int checkoor(int x,int y){
    if(x < 0 || x > 9 || y < 0 || y > 9){
        return 1;
    }else{
        return 0;
    }
}
int checkwall(int x,int y){
    int checkw=0;

    if(checkoor(x-1,y)){
        checkw += 1;//front
    }else{
        if (mapone[x-1][y] == 99) {
            checkw += 1;//front
        }
    }

    if(checkoor(x,y-1)){
        checkw += 2;//left
    }else{
        if (mapone[x][y-1] == 99) {
            checkw += 2;//left
        }
    }

    if(checkoor(x,y+1)){
        checkw += 4;//front
    }else{
        if (mapone[x][y+1] == 99) {
            checkw += 4;//right
        }
    }

    if(checkoor(x+1,y)){
        checkw += 8;//front
    }else{
        if (mapone[x+1][y] == 99) {
            checkw += 8;//back
        }
    }
    return checkw;
}
void changeone(int bx,int by)
{
	int checkw = 0;    
	for (int i = 0; i < 10 ; i++){        
		for (int j = 0; j < 10; j++){
            
            if(mapone[i][j] != 99){
                checkw = checkwall(i,j);                
                switch (checkw)
                {
                case 0: //front,left,right,back
                    mapone[i][j] = min4(mapone[i - 1][j], mapone[i][j - 1],
                                        mapone[i][j + 1], mapone[i + 1][j]);
                    break;
                case 1: //left,right,back
                    mapone[i][j] = min3(mapone[i][j - 1], mapone[i][j + 1], mapone[i + 1][j]);
                    break;
                case 2: //front,right,back
                    mapone[i][j] = min3(mapone[i - 1][j], mapone[i][j + 1], mapone[i + 1][j]);
                    break;
                case 3: //back,right
                    mapone[i][j] = min2(mapone[i][j + 1], mapone[i + 1][j]);
                    break;
                case 4: //front,left,back
                    mapone[i][j] = min3(mapone[i - 1][j], mapone[i][j - 1], mapone[i + 1][j]);
                    break;
                case 5: //left,back
                    mapone[i][j] = min2(mapone[i][j - 1], mapone[i + 1][j]);
                    break;
                case 6: //front,back
                    mapone[i][j] = min2(mapone[i - 1][j], mapone[i + 1][j]);
                    break;
                case 7: //back
                    mapone[i][j] = mapone[i + 1][j] + 1;
                    break;
                case 8: //front,left,right
                    mapone[i][j] = min3(mapone[i - 1][j], mapone[i][j - 1], mapone[i][j + 1]);
                    break;
                case 9: //left,right
                    mapone[i][j] = min2(mapone[i][j - 1], mapone[i][j + 1]);
                    break;
                case 10: //front,right
                    mapone[i][j] = min2(mapone[i - 1][j], mapone[i][j + 1]);
                    break;
                case 11: //right
                    mapone[i][j] = mapone[i][j + 1] + 1;
                    break;
                case 12: //front,left
                    mapone[i][j] = min2(mapone[i - 1][j], mapone[i][j - 1]);
                    break;
                case 13: //left
                    mapone[i][j] = mapone[i][j - 1] + 1;
                    break;
                case 14: //front
                    mapone[i][j] = mapone[i - 1][j] + 1;
                    break;
                default: //no
                    mapone[i][j] = 99;
                    break;
                }
                if (i == bx && j == by)
                {
                    mapone[bx][by] = 0;
                }
            }
		}
	}
}
void changetwo(int bx1,int by1,int bx2,int by2)
{
	int checkw = 0;    
	for (int i = 0; i < 10 ; i++){        
		for (int j = 0; j < 10; j++){
            
            if(mapone[i][j] != 99){
                checkw = checkwall(i,j);                
                switch (checkw)
                {
                case 0: //front,left,right,back
                    mapone[i][j] = min4(mapone[i - 1][j], mapone[i][j - 1],
                                        mapone[i][j + 1], mapone[i + 1][j]);
                    break;
                case 1: //left,right,back
                    mapone[i][j] = min3(mapone[i][j - 1], mapone[i][j + 1], mapone[i + 1][j]);
                    break;
                case 2: //front,right,back
                    mapone[i][j] = min3(mapone[i - 1][j], mapone[i][j + 1], mapone[i + 1][j]);
                    break;
                case 3: //back,right
                    mapone[i][j] = min2(mapone[i][j + 1], mapone[i + 1][j]);
                    break;
                case 4: //front,left,back
                    mapone[i][j] = min3(mapone[i - 1][j], mapone[i][j - 1], mapone[i + 1][j]);
                    break;
                case 5: //left,back
                    mapone[i][j] = min2(mapone[i][j - 1], mapone[i + 1][j]);
                    break;
                case 6: //front,back
                    mapone[i][j] = min2(mapone[i - 1][j], mapone[i + 1][j]);
                    break;
                case 7: //back
                    mapone[i][j] = mapone[i + 1][j] + 1;
                    break;
                case 8: //front,left,right
                    mapone[i][j] = min3(mapone[i - 1][j], mapone[i][j - 1], mapone[i][j + 1]);
                    break;
                case 9: //left,right
                    mapone[i][j] = min2(mapone[i][j - 1], mapone[i][j + 1]);
                    break;
                case 10: //front,right
                    mapone[i][j] = min2(mapone[i - 1][j], mapone[i][j + 1]);
                    break;
                case 11: //right
                    mapone[i][j] = mapone[i][j + 1] + 1;
                    break;
                case 12: //front,left
                    mapone[i][j] = min2(mapone[i - 1][j], mapone[i][j - 1]);
                    break;
                case 13: //left
                    mapone[i][j] = mapone[i][j - 1] + 1;
                    break;
                case 14: //front
                    mapone[i][j] = mapone[i - 1][j] + 1;
                    break;
                default: //no
                    mapone[i][j] = 99;
                    break;
                }
                if ((i == bx1 && j == by1) || (i == bx2 && j == by2))
                {
                    mapone[bx1][by1] = 0;
                    mapone[bx2][by2] = 0;
                }
            }
		}
	}
}
int min2(int a, int b)
{
	if (a < b)
	{
		return a + 1;
	}
	else
	{
		return b + 1;
	}
}
int min3(int a, int b, int c)
{
	if (((a < b) && (a < c)) || ((a == c) && (a < b)) || ((a == b) && (a < c)))
	{
		return a + 1;
	}
	else if ((b < a) && (b < c) || ((b == c) && (b < a)))
	{
		return b + 1;
	}
	else if ((c < a) && (c < b))
	{
		return c + 1;
	}
	else
	{
		return a + 1;
	}
}
int min4(int a, int b, int c, int d)
{
	if (((a < b) && (a < c) && (a < d)) || ((a == b) && (a < c) && (a < d)) || ((a == c) && (a < b) && (a < d)) || ((a == d) && (a < b) && (a < c)))
	{
		return a + 1;
	}
	else if (((b < a) && (b < c) && (b < d)) || ((b == c) && (b < a) && (b < d)) || ((b == d) && (b < a) && (b < c)))
	{
		return b + 1;
	}
	else if ((c < a) && (c < b) && (c < d) || ((c == d) && (c < a) && (c < b)))
	{
		return c + 1;
	}
	else if ((d < a) && (d < b) && (d < c))
	{
		return d + 1;
	}
	else
	{
		return a + 1;
	}
}

//////////////////////////////move to goal
void move(){
    int checkw=0;
    if(checkoor(checkxf(x),checkyf(y))){
        //printf("fwall ");
        checkw += 1; //front
    }else{
        if (mapone[checkxf(x)][checkyf(y)] == 99 ){
            //printf("fwall ");
           checkw += 1; //front 
        }
    }
    if(checkoor(checkxl(x),checkyl(y))){
        //printf("lwall ");
        checkw += 2; //left
    }else{
        if (mapone[checkxl(x)][checkyl(y)] == 99){
            //printf("lwall ");
            checkw += 2; //left
        }
    }
    if(checkoor(checkxr(x),checkyr(y))){
        //printf("rwall ");
        checkw += 4; //right
    }else{
        if (mapone[checkxr(x)][checkyr(y)] == 99){
            //printf("rwall ");
            checkw += 4; //right
        }
    }    
    switch(checkw){
        case 0: min3way(mapone[checkxf(x)][checkyf(y)] , mapone[checkxl(x)][checkyl(y)] , mapone[checkxr(x)][checkyr(y)]);
            break;
        case 1: min2way(mapone[checkxl(x)][checkyl(y)] , mapone[checkxr(x)][checkyr(y)],1);
            break;
        case 2: min2way(mapone[checkxf(x)][checkyf(y)] , mapone[checkxr(x)][checkyr(y)],2);
            break;
        case 3:
            if(status == 0){
                right();front();
            } 
            else if(status == 1){
                checkrightbox1(x,y);   
            }
            // right();
            break;
        case 4: min2way(mapone[checkxf(x)][checkyf(y)] , mapone[checkxl(x)][checkyl(y)],4);
            break;
        case 5:
            if(status == 0){
                left();front();
            } 
            else if(status == 1){
                checkleftbox1(x,y);   
            }
            // left();
            break;
        case 6:front();break;
        default:left();left();front();break;
    }
}
void min2way(int a, int b,int checkw)
{
	if (a <= b)
	{
		switch (checkw)
		{
		case 1:
            if(status == 0){
                left();front();
            } 
            else if(status == 1){
                checkleftbox1(x,y); 
            }    
            // left();       
            break; //left,right				
		case 2: front();break; //front,right
		default: front();break;//front,left
		}		
	}
	else
	{
		switch (checkw)
		{
		case 1:	
            if(status == 0){
                right();front();
            } 
            else if(status == 1){
                checkrightbox1(x,y);   
            }
            // right();
            break; //left,right
		case 2: 
            if(status == 0){
                right();front();
            } 
            else if(status == 1){
                checkrightbox1(x,y);   
            }
            // right();
            break; //front,right
		default: 
            if(status == 0){
                left();front();
            } 
            else if(status == 1){
                checkleftbox1(x,y);   
            }
            // left();
            break; //front,left			
		}		
	}
}
void min3way(int a, int b, int c)
{ //front,left,right
    int check1=0;
	if (a != b && a != c && b != c)
	{
		if (a < b && a < c)
		{ //go front
			front();
		}
		else if (b < a && b < c)
		{ //go left
			if(status == 0){
                left();front();
            } 
            else if(status == 1){
                checkleftbox1(x,y);  
            }
            // left(); 
            
		}
		else
		{ //go right
			if(status == 0){
                right();front();
            } 
            else if(status == 1){
                checkrightbox1(x,y);   
            }
            // right();
            
		}
	}
	else if(a == b)
	{
        if(a < c){
           front(); 
        }else{
            if(status == 0){
                right();front();
            } 
            else if(status == 1){
                checkrightbox1(x,y);   
            }
        }		
	}
    else if(a == c)
	{
        if(a < b){
           front(); 
        }else{
            if(status == 0){
                left();front();
            } 
            else if(status == 1){
                checkleftbox1(x,y);  
            }
        }		
	}else if(b == c){
        if(a < b){
           front(); 
        }else{
            if(status == 0){
                left();front();
            } 
            else if(status == 1){
                checkleftbox1(x,y);  
            }
        }
    }else{
        front();
    }
}

////////////////////////////// north east west
//front
int checkxf(int x){
    switch(di){
        case 0: return x-1;
        case 1: return x;
        case 2: return x;
        default: return x+1;
    }
}
int checkyf(int y){
    switch(di){
        case 0: return y;
        case 1: return y-1;
        case 2: return y+1;
        default: return y;
    }
}
//left
int checkxl(int x){
    switch(di){
        case 0: return x;
        case 1: return x+1;
        case 2: return x-1;
        default: return x;
    }
}
int checkyl(int y){
    switch(di){
        case 0: return y-1;
        case 1: return y;
        case 2: return y;
        default: return y+1;
    }
}
//right
int checkxr(int x){
    switch(di){
        case 0: return x;
        case 1: return x-1;
        case 2: return x+1;
        default: return x;
    }
}
int checkyr(int y){
    switch(di){
        case 0: return y+1;
        case 1: return y;
        case 2: return y;
        default: return y-1;
    }
}
//back
int checkxb(int x){
    switch(di){
        case 0: return x+1;
        case 1: return x;
        case 2: return x;
        default: return x-1;
    }
}
int checkyb(int y){
    switch(di){
        case 0: return y;
        case 1: return y+1;
        case 2: return y-1;
        default: return y;
    }
}
////////////////////////////// ne nw be bw
//northeast
int checkxne(int x){
    switch(di){
        case 0: return x-1;
        case 1: return x+1;
        case 2: return x-1;
        default: return x+1;
    }
}
int checkyne(int y){
    switch(di){
        case 0: return y-1;
        case 1: return y-1;
        case 2: return y+1;
        default: return y+1;
    }
}
//northwest
int checkxnw(int x){
    switch(di){
        case 0: return x-1;
        case 1: return x-1;
        case 2: return x+1;
        default: return x+1;
    }
}
int checkynw(int y){
    switch(di){
        case 0: return y+1;
        case 1: return y-1;
        case 2: return y+1;
        default: return y-1;
    }
}

//southeast
int checkxse(int x){
    switch(di){
        case 0: return x+1;
        case 1: return x+1;
        case 2: return x-1;
        default: return x-1;
    }
}
int checkyse(int y){
    switch(di){
        case 0: return y-1;
        case 1: return y+1;
        case 2: return y-1;
        default: return y+1;
    }
}
//southwest
int checkxsw(int x){
    switch(di){
        case 0: return x+1;
        case 1: return x-1;
        case 2: return x+1;
        default: return x-1;
    }
}
int checkysw(int y){
    switch(di){
        case 0: return y+1;
        case 1: return y+1;
        case 2: return y-1;
        default: return y-1;
    }
}
//turn car to box
void prekeep(int bx ,int by){
    if(checkxf(x) == bx && checkyf(y) == by){
    }else if(checkxl(x) == bx && checkyl(y) == by){
        left();
    }else if(checkxr(x) == bx && checkyr(y) == by){
        right();
    }
    else{
        left();
        left();
    }
}
void keep(){
    left();left();
}
//turn with box1
void checkleftbox1(int x, int y){
    ///*
    if( checkoor(checkxr(x),checkyr(y)) ){
        left();
    }
    else{
        if(mapone[checkxr(x)][checkyr(y)] != 99){
            if(mapone[checkxsw(x)][checkysw(y)] != 99){
                left();
            }else{
                if( checkoor(checkxf(x),checkyf(y)) ){
                    if(mapone[checkxf(x)][checkyf(y)] != 99){
                        if(mapone[checkxl(x)][checkyl(y)] != 99 && mapone[checkxse(x)][checkyse(y)] != 99){
                            right();right();right();
                        }else{
                            mapone[x][y] = 98;
                            back();
                        }
                    }else{
                        mapone[x][y] = 98;
                        back();
                    }
                   
                }else{
                    if( checkoor(checkxb(x),checkyb(y)) ){
                        if(mapone[checkxf(x)][checkyf(y)] != 99){
                            if(mapone[checkxl(x)][checkyl(y)] != 99 && mapone[checkxne(x)][checkyne(y)] != 99 && mapone[checkxnw(x)][checkynw(y)] != 99){
                                right();right();right();
                            }else{
                                if(mapone[checkxf(x)][checkyf(y)] != 98){
                                    front();
                                }else{
                                    mapone[x][y] = 98;
                                    back();
                                }                                
                            }
                        }else{
                            mapone[x][y] = 98;
                            back();
                        }
                    }else{
                        if(mapone[checkxf(x)][checkyf(y)] != 99){
                            if(mapone[checkxl(x)][checkyl(y)] != 99 && mapone[checkxne(x)][checkyne(y)] != 99 && mapone[checkxnw(x)][checkynw(y)] != 99 && mapone[checkxse(x)][checkyse(y)] != 99){
                                right();right();right();
                            }else{
                                if(mapone[checkxf(x)][checkyf(y)] != 98){
                                    front();
                                }else{
                                    mapone[x][y] = 98;
                                    back();
                                } 
                            }
                        }else{
                            mapone[x][y] = 98;
                            back();
                        }

                    }
                }
            }
        }else{
            if( checkoor(checkxf(x),checkyf(y)) ){
                mapone[x][y] =98;
                back();
            }else{               
                if( checkoor(checkxb(x),checkyb(y)) ){ 
                    if(mapone[checkxf(x)][checkyf(y)] != 98){
                            front();
                        }else{
                            mapone[x][y] =98;
                            back();
                        } 
                }else{
                    if(mapone[checkxf(x)][checkyf(y)] != 99){
                       if(mapone[checkxf(x)][checkyf(y)] != 98){
                            front();
                            printf("WTFF1");
                        }else{
                            mapone[x][y] =98;
                            back();
                        } 
                    }else{
                        mapone[x][y] = 98;
                        back();
                    }
                }
           }
        }
    }
}

void checkrightbox1(int x, int y){
    if( checkoor(checkxl(x),checkyl(y)) ){
        right();
    }else{
        if(mapone[checkxl(x)][checkyl(y)] != 99){
            if(mapone[checkxse(x)][checkyse(y)] != 99){
                right();
            }else{
                if( checkoor(checkxf(x),checkyf(y)) ){
                    if(mapone[checkxf(x)][checkyf(y)] != 99){
                        if(mapone[checkxl(x)][checkyl(y)] != 99 && mapone[checkxse(x)][checkyse(y)] != 99){
                            left();left();left();
                        }else{
                            mapone[x][y] = 98;
                            back();
                        }
                    }else{
                        mapone[x][y] = 98;
                        back();
                    }
                   
                }else{
                    if( checkoor(checkxb(x),checkyb(y)) ){
                        if(mapone[checkxf(x)][checkyf(y)] != 99){
                            if(mapone[checkxr(x)][checkyr(y)] != 99 && mapone[checkxne(x)][checkyne(y)] != 99 && mapone[checkxnw(x)][checkynw(y)] != 99){
                                left();left();left();
                            }else{
                                if(mapone[checkxf(x)][checkyf(y)] != 98){
                                    front();
                                }else{
                                    mapone[x][y] = 98;
                                    back();
                                } 
                            }
                        }else{
                            mapone[x][y] = 98;
                            back();
                        }
                    }else{
                        if(mapone[checkxf(x)][checkyf(y)] != 99){
                            if(mapone[checkxr(x)][checkyr(y)] != 99 && mapone[checkxne(x)][checkyne(y)] != 99 && mapone[checkxnw(x)][checkynw(y)] != 99 && mapone[checkxsw(x)][checkysw(y)] != 99){
                                left();left();left();
                            }else{
                                if(mapone[checkxf(x)][checkyf(y)] != 98){
                                    front();
                                }else{
                                    mapone[x][y] = 98;
                                    back();
                                } 
                            }
                        }else{
                            mapone[x][y] = 98;
                            back();
                        }

                    }
                }
            }
        }else{
            if( checkoor(checkxf(x),checkyf(y)) ){ 
                mapone[x][y] = 98;
                back();
            }else{               
                if( checkoor(checkxb(x),checkyb(y)) ){ 
                   if(mapone[checkxf(x)][checkyf(y)] != 99){
                       if(mapone[checkxf(x)][checkyf(y)] != 98){
                            front();
                        }else{
                            mapone[x][y] = 98;
                            back();
                        } 
                   }else{
                       mapone[x][y] = 98;
                       back();
                   }
                }else{
                    if(mapone[checkxf(x)][checkyf(y)] != 99){
                       if(mapone[checkxf(x)][checkyf(y)] != 98){
                            front();
                        }else{
                            mapone[x][y] = 98;
                            back();
                        } 
                    }else{
                        mapone[x][y] = 98;
                        back();
                    }
                }
           }
        }
    }
}

void checkbackbox1(int x,int y){
    if( checkoor(checkxf(x),checkyf(y)) ){
        if( checkoor(checkxr(x),checkyr(y)) ){
            left();left();
        }else if( checkoor(checkxl(x),checkyl(y)) ){
            right();right();
        }else{
            if(mapone[checkxr(x)][checkyr(y)] != 99 && mapone[checkxsw(x)][checkysw(y)] != 99){
                left();left();
            }
            else if(mapone[checkxl(x)][checkyl(y)] != 99 && mapone[checkxse(x)][checkyse(y)] != 99){
                right();right();
            }else{
                mapone[x][y] = 98;
                back();
            }
        }
    }
    else if( checkoor(checkxb(x),checkyb(y)) ){
        if(mapone[checkxf(x)][checkyf(y)] != 99){
           if( checkoor(checkxr(x),checkyr(y)) ){
                left();left();
            }else if( checkoor(checkxl(x),checkyl(y)) ){
                right();right();
            }else{
                if(mapone[checkxr(x)][checkyr(y)] != 99 && mapone[checkxnw(x)][checkynw(y)] != 99){
                    left();left();
                }
                else if(mapone[checkxl(x)][checkyl(y)] != 99 && mapone[checkxne(x)][checkyne(y)] != 99){
                    right();right();
                }else{
                    mapone[x][y] = 98;
                    back();
                }
            }
        }else{
            mapone[x][y] = 98;
            back();
        }       

    }else{
        if(mapone[checkxf(x)][checkyf(y)] != 99){
           if( checkoor(checkxr(x),checkyr(y)) ){
                left();left();
            }else if( checkoor(checkxl(x),checkyl(y)) ){
                right();right();
            }else{
                if(mapone[checkxr(x)][checkyr(y)] != 99 && mapone[checkxnw(x)][checkynw(y)] != 99 && mapone[checkxsw(x)][checkysw(y)] != 99){
                    left();left();
                }
                else if(mapone[checkxl(x)][checkyl(y)] != 99 && mapone[checkxne(x)][checkyne(y)] != 99 && mapone[checkxse(x)][checkyse(y)] != 99){
                    right();right();
                }else{
                    mapone[x][y] = 98;
                    back();
                }
            }
        }else{
            mapone[x][y] = 98;
            back();
        }

    }
}
////////////////////////////// place
int checkwallgoal(int bx,int by){
    int checkw=0;
    if(mapone[checkxf(bx)][checkyf(by)] == 99){
        checkw+=1;
    }else if(mapone[checkxl(bx)][checkyl(by)] == 99){
        checkw+=2;
    }
    else if(mapone[checkxr(bx)][checkyr(by)] == 99){
        checkw+=4;
    }
    else if(mapone[checkxb(bx)][checkyb(by)] == 99){
        checkw+=8;
    }
    return checkw;
}

int checkdiplace(int bx,int by){
    if(!checkoor(checkxf(x),checkyf(y))){
        if(mapone[checkxf(x)][checkyf(y)] == mapone[bx][by]){
            //printf("\nfront*");
            return 0;
        }
    }
    if(!checkoor(checkxl(x),checkyl(y))){
        if(mapone[checkxl(x)][checkyl(y)] == mapone[bx][by]){
           // printf("\nleft*");
            return 1;
        }
    }
    if(!checkoor(checkxr(x),checkyr(y))){
        if(mapone[checkxr(x)][checkyr(y)] == mapone[bx][by]){
            //printf("\nright*");
            return 2;
        }
    }
    if(!checkoor(checkxb(x),checkyb(y))){
        if(mapone[checkxb(x)][checkyb(y)] == mapone[bx][by]){
            //printf("\nback*");
            return 3;
        }
    }
}
///*
void preplace1(int bx,int by){
    int checkw=0,checkp=0;
    checkw = checkwallgoal(bx,by);
    checkp = checkdiplace(bx,by);
    switch(checkp){
        case 0:
            printf(" goal in the front \n");
            if(checkw == 6 || checkw == 9){
                front();
                front();
            }else{
               checkbackbox1(x,y);   
            }                       
            break;
        case 1:
            printf(" goal in the left \n");
            checkrightbox1(x,y);            
            break;
        case 2:
            printf(" goal in the right \n");
            checkleftbox1(x,y);
            break;
        default:
            printf(" goal in the back \n");
            break;
    }
  
}
//*/