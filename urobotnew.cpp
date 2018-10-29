#include<stdio.h>

int x=9,y=9;
int di=0; //0 front ,1 left ,2 right,3 back
int ultra = 0;
int bx=0,by=0;
int status = 0;

void front(){
    switch(di){
        case 0:x--;break;
        case 1:y--;break;
        case 2:y++;break;
        default:x++;break;
    }
}
void left(){
    switch(di){
        case 0:di=1;break;
        case 1:di=3;break;
        case 2:di=0;break;
        default:di=2;break;
    }
}
void right(){
    switch(di){
        case 0:di=2;break;
        case 1:di=0;break;
        case 2:di=3;break;
        default:di=1;break;
    }
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
    {1,9,1,1,1, 9,1,1,1,1},//1
    {1,1,9,1,1, 1,1,1,1,1},//2
    {1,1,6,1,1, 1,1,1,1,1},//3
    {1,1,6,1,1, 1,1,1,1,1},//4
    
    {1,1,1,1,1, 1,1,1,1,1},//5
    {1,1,1,1,1, 1,1,1,1,1},//6
    {1,1,1,1,1, 1,1,1,1,1},//7
    {1,1,1,6,9, 6,1,1,1,1},//8
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

void printmap(int map[][10]);
void printxy(int x,int y);

void findone();
void findwall(int bx,int by);

int checkoor(int x,int y);
int checkwall(int x,int y);
void changeone(int bx,int by);
int min2(int a, int b);
int min3(int a, int b, int c);
int min4(int a, int b, int c, int d);

void move();
void min2way(int a, int b,int checkw);
void min3way(int a, int b, int c);

void clearmap();
void movewbox1();
int checkleft(int x, int y);
//****block (1,7) (7,2) (5,6)(6,6)****//

int main(){

    //find boxmall 1 : Round 1
    findone();
    printxy(x,y);
    printxy(bx,by);
    for(int i=0;i<15;i++){
        changeone(bx,by);
    }     
    printmap(mapone);

    while(x!=bx || y!=by){
        if(mapone[x][y]==1){
            break; //keepblock
        }else{
            move();
            printxy(x,y);
        }        
        
    }
    printf("keep block\n");
    status = 1;
    left();left();
    //find goal
    bx=1;
    by=7;
    printxy(x,y);
    printxy(bx,by);
    for(int i=0;i<15;i++){
        changeone(bx,by);
    }  
    printmap(mapone);

    while(x!=bx || y!=by){
        // if(mapone[x][y]==1){
        //     break; //keepblock
        // }else{
            movewbox1();
            //move(); //move with block
        //}        
        printxy(x,y);
    }
 
    return 0;
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
    printf("%d : (%d,%d)\n",di,x,y);
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
    findwall(bx,by);
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

/*
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
*/

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
    if (mapone[x-1][y] == 99 || checkoor(x-1,y)) checkw += 1; //#front
    if (mapone[x][y-1] == 99 || checkoor(x,y-1)) checkw += 2; //#left
    if (mapone[x][y+1] == 99 || checkoor(x,y+1)) checkw += 4; //#right
    if (mapone[x+1][y] == 99 || checkoor(x+1,y)) checkw += 8; //#back
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
    if (mapone[checkxf(x)][checkyf(y)] == 99 || checkoor(checkxf(x),checkyf(y))) checkw += 1; //#front
    if (mapone[checkxl(x)][checkyl(y)] == 99 || checkoor(checkxl(x),checkyl(y))) checkw += 2; //#left
    if (mapone[checkxr(x)][checkyr(y)] == 99 || checkoor(checkxr(x),checkyr(y))) checkw += 4; //#right
    switch(checkw){
        case 0: min3way(mapone[checkxf(x)][checkyf(y)] , mapone[checkxl(x)][checkyl(y)] , mapone[checkxr(x)][checkyr(y)]);
            break;
        case 1: min2way(mapone[checkxl(x)][checkyl(y)] , mapone[checkxr(x)][checkyr(y)],1);
            break;
        case 2: min2way(mapone[checkxf(x)][checkyf(y)] , mapone[checkxr(x)][checkyr(y)],2);
            break;
        case 3:right();front();break;
        case 4: min2way(mapone[checkxf(x)][checkyf(y)] , mapone[checkxl(x)][checkyl(y)],4);
            break;
        case 5:left();front();break;
        case 6:front();break;
        default:left();left();front();break;
    }
}
void min2way(int a, int b,int checkw)
{
    int check1=0;
	if (a <= b)
	{
		switch (checkw)
		{
		case 1:
            // if(status = 0){
            //     left();
            // } 
            // else if(status = 1){
            //     check1 = checkleft(x,y);
            //     switch(check1){
            //         case 1:left();break;
            //         case 2:right();right();right();break;
            //         default:break;
            //     }    
            // }    
            left();       
            front();break; //left,right				
		case 2: front();break; //front,right
		default: front();break;//front,left
		}		
	}
	else
	{
		switch (checkw)
		{
		case 1:	right();front();break; //left,right
		case 2: right();front();break; //front,right
		default: 
            // if(status = 0){
            //     left();
            // } 
            // else if(status = 1){
            //     check1 = checkleft(x,y);
            //     switch(check1){
            //         case 1:left();break;
            //         case 2:right();right();right();break;
            //         default:break;
            //     }    
            // }
            left();
            front();break; //front,left			
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
			// if(status = 0){
            //     left();
            // } 
            // else if(status = 1){
            //     check1 = checkleft(x,y);
            //     switch(check1){
            //         case 1:left();break;
            //         case 2:right();right();right();break;
            //         default:break;
            //     }    
            // }
            left(); 
            front();
		}
		else
		{ //go right
			right();front();
		}
	}
	else
	{
		front();
	}
}

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

/*
void clearmap(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            map[i][j]=mapone[i][j];
        }
    }
}
*/

//////////////////////////////move to goal with box1
void movewbox1(){
    int checkw=0,check1=0;
    if (mapone[x-1][y] == 99 || checkoor(x-1,y)) checkw += 1; //#front
    if (mapone[x][y-1] == 99 || checkoor(x,y-1)) checkw += 2; //#left
    if (mapone[x][y+1] == 99 || checkoor(x,y+1)) checkw += 4; //#right
    switch(checkw){
        case 0:
            switch(di){
                case 0:min3way(mapone[x - 1][y], mapone[x][y - 1], mapone[x][y + 1]);break;
                case 1:min3way(mapone[x][y - 1], mapone[x + 1][y], mapone[x - 1][y]);break;
                case 2:min3way(mapone[x][y + 1], mapone[x - 1][y], mapone[x + 1][y]);break;
                default:min3way(mapone[x + 1][y], mapone[x][y + 1], mapone[x][y - 1]);break;                
            }break;
        case 1:switch(di){
                case 0:min2way(mapone[x][y - 1], mapone[x][y + 1],1);break;
                case 1:min2way(mapone[x + 1][y], mapone[x - 1][y],1);break;
                case 2:min2way(mapone[x - 1][y], mapone[x + 1][y],1);break;
                default:min2way(mapone[x][y + 1], mapone[x][y - 1],1);break;                
            }break;
        case 2:switch(di){
                case 0:min2way(mapone[x - 1][y], mapone[x][y + 1],2);break;
                case 1:min2way(mapone[x][y - 1], mapone[x - 1][y],2);break;
                case 2:min2way(mapone[x][y + 1], mapone[x + 1][y],2);break;
                default:min2way(mapone[x + 1][y], mapone[x][y - 1],2);break;                
            }break;
        case 3:        
            right();front();break;
        case 4:switch(di){
                case 0:min2way(mapone[x - 1][y], mapone[x][y - 1],4);break;
                case 1:min2way(mapone[x][y - 1], mapone[x + 1][y],4);break;
                case 2:min2way(mapone[x][y + 1], mapone[x - 1][y],4);break;
                default:min2way(mapone[x + 1][y], mapone[x][y + 1],4);break;                
            }break;
        case 5:
            check1 = checkleft(x,y);
            switch(check1){
                case 1:left();break;
                case 2:right();right();right();break;
                default:break;
            }            
            front();break;
        case 6:front();break;
        default: 
            left();left();front();break;
    }
}
int checkleft(int x, int y){
    switch(di){
        case 0:
            if(mapone[x][y+1] == 1 && mapone[x+1][y+1] == 1){
                return 1;
            }else if(mapone[x][y+1] == 1 && mapone[x-1][y+1] == 1 &&                     
                    mapone[x-1][y] == 1 && mapone[x-1][y-1] == 1 &&
                    mapone[x][y-1] == 1 && mapone[x+1][y-1] == 1){
                return 2;
            }else{
                return 3;
            }
            break;
        case 1:
            if(mapone[x-1][y] == 1 && mapone[x-1][y+1] == 1){
                return 1;
            }else if(mapone[x-1][y] == 1 && mapone[x-1][y-1] == 1 &&                     
                    mapone[x][y-1] == 1 && mapone[x+1][y-1] == 1 &&
                    mapone[x+1][y] == 1 && mapone[x+1][y+1] == 1){
                return 2;
            }else{
                return 3;
            }
            break;
        case 2:
            if(mapone[x+1][y] == 1 && mapone[x+1][y-1] == 1){
                return 1;
            }else if(mapone[x+1][y] == 1 && mapone[x+1][y+1] == 1 &&                     
                    mapone[x][y+1] == 1 && mapone[x-1][y+1] == 1 &&
                    mapone[x-1][y] == 1 && mapone[x-1][y-1] == 1){
                return 2;
            }else{
                return 3;
            }
            break;
        default:
            if(mapone[x-1][y-1] == 1 && mapone[x][y-1] == 1){
                return 1;
            }else if(mapone[x][y-1] == 1 && mapone[x+1][y-1] == 1 &&                     
                    mapone[x+1][y] == 1 && mapone[x+1][y+1] == 1 &&
                    mapone[x][y+1] == 1 && mapone[x-1][y+1] == 1){
                return 2;
            }else{
                return 3;
            }
            break;

    }
    

}
void checkmap(int x,int y,int a){

}
