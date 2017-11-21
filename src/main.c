#include <stdio.h>
#include <stdlib.h>
#define MAXNUMBER 1000
#define MAXSIZE 15
#include<math.h>
#include<ctype.h>
#include<stdbool.h>
char symbol(int saf1,int mod1);
int convertchar(char character);
int chechmove(char x,int saf1,int saf2,int mod1,int mod2);
char startboard[8][8]={'R','N','B','Q','K','B','N','R','P','P','P','P','P','P','P','P','_','.','_','.','_','.','_','.','.','_','.','_','.','_','.','_','_','.','_','.','_','.','_','.','.','_','.','_','.','_','.','_','p','p','p','p','p','p','p','p','r','n','b','q','k','b','n','r'};
char board[8][8];
char letters[8]={'A','B','C','D','E','F','G','H'};
int saf1,saf2,mod1,mod2,found;
char deadpeices[9][4]={'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'};
int index1=0,index2=0,game=0;
char array[500][4];
int sizeOfArray=0;
bool simulation = false;

void collectMove(int x)
{
    simulation = true;
   char backupBoard[8][8];
   copyBoard(board,backupBoard);
   char counter1,counter2,counter3,counter4;sizeOfArray=0;
    for(counter1 = 'A'; counter1 <= 'H'; counter1++)
    {
        for( counter2 = '1'; counter2<='8'; counter2++)
        {
            for(counter3 = 'A'; counter3 <= 'H'; counter3++)
            {
                for(counter4 = '1'; counter4 <= '8'; counter4++)
                {
                    int moveDone = 0;
                    int notCheck = 0;
                    int col1=convertchar(counter1);
                    int col2=convertchar(counter3);
                    int row1=convertnumber(counter2-'0');
                    int row2=convertnumber(counter4-'0');
                    if((board[row1][col1]=='.'||board[row1][col1]=='_')|| ( isupper(board[row1][col1]) && x == 0) || ( islower(board[row1][col1]) && x == 1) )
                        continue;

                    char desiredpiece=board[row1][col1];
                    found=chechmove(desiredpiece,row1,row2,col1,col2);
                    if(found==1)
                    {
                        moveDone=1;
                    }
                    else
                    {
                        moveDone=0;
                    }
                    board[row2][col2]=desiredpiece;
                    char sign=symbol(row1,col1);
                    board[row1][col1]=sign;
                    if(x==0)
                    {
                        int danger=checksmall();
                        if(danger==0)
                        {
                            notCheck=0;
                        }
                        else
                        {
                            notCheck=1;
                        }
                    }

                    if(x==1)
                    {
                        int danger=checkcapital();
                        if(danger==0)
                        {
                            notCheck=0;
                        }
                        else
                        {
                            notCheck=1;
                        }
                    }

                    if( moveDone == 1 && notCheck == 0)
                    {
                        array[sizeOfArray][0] = counter1;
                        array[sizeOfArray][1] = counter2;
                        array[sizeOfArray][2] = counter3;
                        array[sizeOfArray][3] = counter4;
                        sizeOfArray++;


                    }
                    copyBoard(backupBoard,board);
                }
            }
        }
    }
    simulation = false;
}

void copyBoard( char board[8][8], char board2[8][8])
{
    int counter,counter2;
    for(counter =0; counter<8; counter++)
    {
        for(counter2 = 0; counter2<8; counter2++)
        {
            board2[counter][counter2]= board[counter][counter2];
        }
    }
}
int checkIfAvailable(a,b,c,d)
{int counter;
    for(counter = 0; counter< sizeOfArray; counter++)
    {
        if( a == array[counter][0] && b == array[counter][1] && c == array[counter][2] && d == array[counter][3])
            return 1;
    }
    return 0;                           //collect move &&
}

char symbol(int saf1,int mod1)
{
    int a,b;
    char sign2,sign1;
    sign1='_';
    sign2='.';
    a=saf1%2;       /* lw zero yb2a zwgy wlw 1 yb2a frdy*/
    b=mod1%2;       /* lw zero yb2a zwgy wlw 1 yb2a frdy*/
    if(((a==0)&&(b==1))){return sign2;}
    else if(((a==0)&&(b==0))){return sign1;}
    else if(((a==1)&&(b==1))){return sign1;}
    else if(((a==1)&&(b==0))){return sign2;}
}



char undoredo[1000][8][8];

 char undo_Redo(char char1){

 int i=0,j=0,counter=0;

if (char1=='U'||char1=='R'){


 if (char1=='U'){

   if (game==0){
    printf("move");
 }

 else

 {
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
                    {
                        board[i][j]=undoredo[game-1][i][j];
                    }
                }
game--;
printf("Undo\n");
counter++;
 }

 printboard();

 printf("\n");


 }
 else if(char1=='R')


 if (counter==0)
{
printboard();
printf("\n");
printf("error");
}
else
{

for(i=0; i<8; i++)
{
   for(j=0; j<8; j++)
    {
       board[i][j]=undoredo[game+1][i][j];
    }
}
game++;
printf("REDO\n");
counter--;
printboard();
printf("\n");
}


 }

 return char1;

 }
void dead_capital(int saf1,int mod1,int saf2,int mod2){

if (((board[saf1][mod1] >= 'a') &&( board[saf1][mod1] <= 'z'))&&((board[saf2][mod2] >= 'A') &&( board[saf2][mod2] <= 'Z'))){
        deadpeices[index2][index1]=board[saf2][mod2];
        index1++;

    if(index1>=4){
        index1=0;
        index2++;
}
    }
}
void dead_smal(int saf1,int mod1,int saf2,int mod2){

if (((board[saf1][mod1] >= 'A') &&( board[saf1][mod1] <= 'Z'))&&((board[saf2][mod2] >= 'a') &&( board[saf2][mod2] <= 'z'))){
        deadpeices[index2][index1]=board[saf2][mod2];
        index1++;

    if(index1>=4){
        index1=0;
        index2++;
}
    }
}








    void save()
    {
         FILE* saveload;
    saveload = fopen("saveload.txt","w");
    fwrite(&board,sizeof(board),1,saveload);
    fwrite(&deadpeices,sizeof(deadpeices),1,saveload);
    fclose(saveload);
    }
void load()
{
     FILE* saveload;

    saveload = fopen("saveload.txt","r");
    if(saveload == NULL)
    {
        return 1;
    }
    fread(&board,sizeof(board),1,saveload);

    fread(&deadpeices,sizeof(deadpeices),1,saveload);

    fclose(saveload);
}

int checkcapital()
{
    int flag=0,i,j;

    int danger=0;

    for(i=0;(i<8&&flag==0);i++)
    {
        for(j=0;(j<8&&flag==0);j++){

                        if (board[i][j]=='K'){flag=1;}
                        else{flag=0;}
                                    }
                                  }
i=i-1;
j=j-1;
    int a=i+1;
    int b=i-1;
    int c=j+1;
    int d=j-1;
    int e=i-2;
    int f=j-2;
    int g=i+2;
    int h=j+2;
    int k=i-1;
    if(board[a][c]=='p'||board[a][d]=='p'){danger=1;}
    else if(board[e][c]=='n'||board[e][d]=='n'){danger=1;}
    else if(board[g][c]=='n'||board[g][d]=='n'){danger=1;}
    else if(board[b][h]=='n'||board[b][f]=='n'){danger=1;}
    else if(board[a][h]=='n'||board[a][f]=='n'){danger=1;}


    int found=0;

    if(danger==0)
    {
        for(h=j+1;((h<8)&&(found==0)&&(danger==0));h++){
        if(board[i][h]=='P'||board[i][h]=='R'||board[i][h]=='N'||board[i][h]=='B'||board[i][h]=='Q'){found=1;}
        else if(board[i][h]=='r'||board[i][h]=='q'){danger=1;}
                                                       }
    }
    found=0;
     if(danger==0)
    {
        for(h=j-1;((h>=0)&&(found==0)&&(danger==0));h--){
        if(board[i][h]=='P'||board[i][h]=='R'||board[i][h]=='N'||board[i][h]=='B'||board[i][h]=='Q'){found=1;}
        else if(board[i][h]=='r'||board[i][h]=='q'){danger=1;}
    }
    }
    found=0;
     if(danger==0)
    {
        for(h=i-1;((h>=0)&&(found==0)&&(danger==0));h--){
        if(board[h][j]=='P'||board[h][j]=='R'||board[h][j]=='N'||board[h][j]=='B'||board[h][j]=='Q'){found=1;}
        else if(board[h][j]=='r'||board[h][j]=='q'){danger=1;}

    }
    }
    found=0;
     if(danger==0)
    {
        for(h=i+1;((h<8)&&(found==0)&&(danger==0));h++){
        if(board[h][j]=='P'||board[h][j]=='R'||board[h][j]=='N'||board[h][j]=='B'||board[h][j]=='Q'){found=1;}

        else if(board[h][j]=='r'||board[h][j]=='q'){danger=1;}


    }
    }
    found=0;
    if(danger==0)
    { k=j+1;
        for(h=i+1;((h<8)&&(found==0)&&(danger==0)&&(k<8));h++){
        if(board[h][k]=='P'||board[h][k]=='R'||board[h][k]=='N'||board[h][k]=='B'||board[h][k]=='Q'){found=1;}

        else if(board[h][k]=='b'||board[h][k]=='q'){danger=1;}

        k++;
                                                        }
    }
    found=0;
    if(danger==0)
    { k=j+1;
        for(h=i-1;((h>=0)&&(found==0)&&(danger==0)&&(k<8));h--){
        if(board[h][k]=='P'||board[h][k]=='R'||board[h][k]=='N'||board[h][k]=='B'||board[h][k]=='Q'){found=1;}

        else if(board[h][k]=='b'||board[h][k]=='q'){danger=1;}

        k++;
                                                        }
    }
    found=0;
    if(danger==0)
    { k=j-1;
        for(h=i-1;((h>=0)&&(found==0)&&(danger==0)&&(k>=0));h--){
        if(board[h][k]=='P'||board[h][k]=='R'||board[h][k]=='N'||board[h][k]=='B'||board[h][k]=='Q'){found=1;}

        else if(board[h][k]=='b'||board[h][k]=='q'){danger=1;}

        k--;
                                                        }
    }
    found=0;
    if(danger==0)
    { k=j-1;
        for(h=i+1;((h<8)&&(found==0)&&(danger==0)&&(k>=0));h++){
        if(board[h][k]=='P'||board[h][k]=='R'||board[h][k]=='N'||board[h][k]=='B'||board[h][k]=='Q'){found=1;}

        else if(board[h][k]=='b'||board[h][k]=='q'){danger=1;}

        k--;
                                                        }
    }

return danger;
}
int checksmall()
{
    int flag=0,i,j;

    int danger=0;

    for(i=0;(i<8&&flag==0);i++)
    {
        for(j=0;(j<8&&flag==0);j++){

                        if (board[i][j]=='k'){flag=1;}
                        else{flag=0;}
                                    }
                                  }
i=i-1;
j=j-1;
    int a=i-1;
    int b=i+1;
    int c=j+1;
    int d=j-1;
    int e=i-2;
    int f=j-2;
    int g=i+2;
    int h=j+2;
    int k=i-1;
    if(board[a][c]=='P'||board[a][d]=='P'){danger=1;}
    else if(board[e][c]=='N'||board[e][d]=='N'){danger=1;}
    else if(board[g][c]=='N'||board[g][d]=='N'){danger=1;}
    else if(board[b][h]=='N'||board[b][f]=='N'){danger=1;}
    else if(board[k][h]=='N'||board[k][f]=='N'){danger=1;}


    int found=0;

    if(danger==0)
    {
        for(h=j+1;(h<8&&found==0&&danger==0);h++){
        if(board[i][h]=='p'||board[i][h]=='r'||board[i][h]=='n'||board[i][h]=='b'||board[i][h]=='q'){found=1;}
        else if(board[i][h]=='R'||board[i][h]=='Q'){danger=1;}
                                                 }
    }
    found=0;
     if(danger==0)
    {
        for(h=j-1;((h>=0)&&(found==0)&&(danger==0));h--){
        if(board[i][h]=='p'||board[i][h]=='r'||board[i][h]=='n'||board[i][h]=='b'||board[i][h]=='q'){found=1;}
        else if(board[i][h]=='R'||board[i][h]=='Q'){danger=1;}
    }
    }
    found=0;
     if(danger==0)
    {
        for(h=i-1;((h>=0)&&(found==0)&&(danger==0));h--){
        if(board[h][j]=='p'||board[h][j]=='r'||board[h][j]=='n'||board[h][j]=='b'||board[h][j]=='q'){found=1;}
        else if(board[h][j]=='R'||board[h][j]=='Q'){danger=1;}

    }
    }
    found=0;
     if(danger==0)
    {
        for(h=i+1;((h<8)&&(found==0)&&(danger==0));h++){
        if(board[h][j]=='p'||board[h][j]=='r'||board[h][j]=='n'||board[h][j]=='b'||board[h][j]=='q'){found=1;}

        else if(board[h][j]=='R'||board[h][j]=='Q'){danger=1;}


    }
    }
    found=0;
    if(danger==0)
    { k=j+1;
        for(h=i+1;((h<8)&&(found==0)&&(danger==0)&&(k<8));h++){
        if(board[h][k]=='p'||board[h][k]=='r'||board[h][k]=='n'||board[h][k]=='b'||board[h][k]=='q'){found=1;}

        else if(board[h][k]=='B'||board[h][k]=='Q'){danger=1;}

        k++;
                                                        }
    }
    found=0;
    if(danger==0)
    { k=j+1;
        for(h=i-1;((h>=0)&&(found==0)&&(danger==0)&&(k<8));h--){
        if(board[h][k]=='p'||board[h][k]=='r'||board[h][k]=='n'||board[h][k]=='b'||board[h][k]=='q'){found=1;}

        else if(board[h][k]=='B'||board[h][k]=='Q'){danger=1;}

        k++;
                                                        }
    }
    found=0;
    if(danger==0)
    { k=j-1;
        for(h=i-1;((h>=0)&&(found==0)&&(danger==0)&&(k>=0));h--){
        if(board[h][k]=='p'||board[h][k]=='r'||board[h][k]=='n'||board[h][k]=='b'||board[h][k]=='q'){found=1;}

        else if(board[h][k]=='B'||board[h][k]=='Q'){danger=1;}

        k--;
                                                        }
    }
    found=0;
    if(danger==0)
    { k=j-1;
        for(h=i+1;((h<8)&&(found==0)&&(danger==0)&&(k>=0));h++){
        if(board[h][k]=='p'||board[h][k]=='r'||board[h][k]=='n'||board[h][k]=='b'||board[h][k]=='q'){found=1;}

        else if(board[h][k]=='B'||board[h][k]=='Q'){danger=1;}

        k--;
                                                        }
    }

return danger;
}
int convertchar(char character){
int x;
switch(character){

case'A':
    x=0;
break;
case'B':
    x=1;
break;
case'C':
     x=2;
break;
case'D':
     x=3;
break;
case'E':
     x=4;
break;
case'F':
     x=5;
break;
case'G':
     x=6;
break;
case'H':
     x=7;
break;
}
return x;
 }

void printletters(char letters[],int x)
{
    int i=0;
    printf("%c",' ');
    for(i=0;i<x;i++)

        printf("    %c",letters[i]);
        printf("%c",'\n');
}



void printboard()
{ int i,j,m;
for(i=0;i<8;i++){
        printf("%d",(8-i));
    for(j=0;j<8;j++)
    {
        printf("    %c",board[i][j]);

    }
    printf("    %d\t",(8-i));
    for(m=0; m<4 && i<=8; m++)

    {

         if(m==0 || m==1 )
            printf("| %c |",deadpeices[i][m]);
        else if(m==2 )
            printf("| %c |",deadpeices[i][m]);
        else if(m==3 )
            printf("| %c |",deadpeices[i][m]);
        if(i==0 && m==3);
            //printf("\n");
    }
    printf("\n\n");
    if(i==8)
        printf("\n");
}

}

int chechmove(char x,int saf1,int saf2,int mod1,int mod2)/*found=chechmove(desiredpiece,row1,row2,col1,col2);*/
{
    int found,i,j;

if((x=='r')||(x=='R'))
 {  if(saf1!=saf2&&mod2!=mod1){found=0;}
    else if(saf2==saf1||mod2==mod1){
if(x=='r'){found=1;
         if(saf1 == saf2){
                if (mod1>mod2){
               for( i=mod1-1;i>mod2;i--){
                  if(((board[saf1][i] >= 'a') &&( board[saf1][i] <= 'z'))||(board[saf1][i]>='A'&&board[saf1][i]<='Z')){
                    found = 0;

                    break;
                  }



               }
 if((board[saf2][mod2] >= 'a') &&( board[saf2][mod2] <= 'z'))
                  {
                      found=0;


                  }

                             }
                else if(mod2>mod1)
                {
                  for(i=mod1+1;i<mod2;i++){
                  if(((board[saf1][i]>='a')&&(board[saf1][i]<='z'))||((board[saf1][i]>='A')&&(board[saf1][i]<='Z')))
                    {
                    found = 0;

                  break;
                    }


                  }
 if((board[saf2][mod2] >= 'a') &&( board[saf2][mod2] <= 'z'))
                   {found = 0;



                   }
                }

         }

if(mod2 == mod1){
                if (saf1>saf2){
               for( i=saf1-1;i>saf2;i--){
                  if(((board[i][mod1] >= 'a') &&( board[i][mod1] <= 'z'))||(board[i][mod1]>='A'&&board[i][mod1]<='Z')){
                    found = 0;

                    break;
                  }

               }
                 if((board[saf2][mod2] >= 'a') &&( board[saf2][mod2] <= 'z'))
                  {
                      found=0;


                  }

                 }
                else if(saf2>saf1)
                {
                  for(i=saf1+1;i<saf2;i++){
                  if(((board[i][mod1]>='a')&&(board[i][mod1]<='z'))||((board[i][mod1]>='A')&&(board[i][mod1]<='Z')))
                    {
                    found = 0;

                  break;
                    }

                  }
    if((board[saf2][mod2] >= 'a') &&( board[saf2][mod2] <= 'z'))
            {found = 0;


            }


       }
       if (saf1==saf2&&mod1==mod2){found=0;}

}
}

 if (x=='R'){found=1;
         if(saf1 == saf2){
                if (mod1>mod2){
               for( i=mod1-1;i>mod2;i--){
                  if(((board[saf1][i] >= 'a') &&( board[saf1][i] <= 'z'))||(board[saf1][i]>='A'&&board[saf1][i]<='Z')){
                    found = 0;

                    break;
                  }
                                        }
 if((board[saf2][mod2] >= 'A') &&( board[saf2][mod2] <= 'Z'))
                  {
                      found=0;


                  }

                             }
                else if(mod2>mod1)
                {
                  for(i=mod1+1;i<mod2;i++){
                  if(((board[saf1][i]>='a')&&(board[saf1][i]<='z'))||((board[saf1][i]>='A')&&(board[saf1][i]<='Z')))
                    {
                    found = 0;

                  break;
                    }


                  }
 if((board[saf2][mod2] >= 'A') &&( board[saf2][mod2] <= 'Z'))
                   {found = 0;



                   }
                }

         }

if(mod2 == mod1){
                if (saf1>saf2){
               for( i=saf1-1;i>saf2;i--){
                  if(((board[i][mod1] >= 'a') &&( board[i][mod1] <= 'z'))||(board[i][mod1]>='A'&&board[i][mod1]<='Z')){
                    found = 0;

                    break;
                  }

               }
                 if((board[saf2][mod2] >= 'A') &&( board[saf2][mod2] <= 'Z'))
                  {
                      found=0;


                  }

                 }
                else if(saf2>saf1)
                {
                  for(i=saf1+1;i<saf2;i++){
                  if(((board[i][mod1]>='a')&&(board[i][mod1]<='z'))||((board[i][mod1]>='A')&&(board[i][mod1]<='Z')))
                    {
                    found = 0;

                  break;
                    }

                  }
    if((board[saf2][mod2] >= 'A') &&( board[saf2][mod2] <= 'Z'))
            {found = 0;


            }


       }
       if (saf1==saf2&&mod1==mod2){found=0;}

}
 }

 }
 }
 else if(x=='n'||x=='N')
  {


    if (((abs(saf2-saf1)==2)&&(abs(mod2-mod1)==1))||((abs(mod2-mod1)==2)&&(abs(saf2-saf1)==1)))
    {
    found=1;
    }
    else{
    found=0;}


if(x == 'n'){
    if((board[saf2][mod2] >= 'a') && (board[saf2][mod2] <= 'z')){
        found = 0;
                 }
            }

 else if(x == 'N'){
    if((board[saf2][mod2] >= 'A') && (board[saf2][mod2] <= 'Z')){
            found = 0;
                      }
                  }


  }

else if(x=='b'||x=='B'){
if((abs(saf1-saf2))==(abs(mod1-mod2)))
{

if(x =='b'){found=1;
    if(saf1>saf2&&mod1<mod2){j=mod1+1;
            for (i=saf1-1;i>saf2;i--){

                        if(((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;

                                            break;}
                                     j++;}
    if((board[saf2][mod2] >= 'a')&&( board[saf2][mod2] <= 'z'))
        {
        found = 0;

        }
                            }
else if (saf1>saf2&&mod1>mod2){j=mod1-1;
            for (i=saf1-1;i>saf2;i--){

                        if (((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;break;}
                                     j--;}
    if((board[saf2][mod2] >= 'a' )&&( board[saf2][mod2] <= 'z'))
        {
        found = 0;

        }
}
else if (saf1<saf2&&mod1<mod2){j=mod1+1;
            for (i=saf1+1;i<saf2;i++){

                        if (((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;break;printf("bb");}
                                     j++;}
    if((board[saf2][mod2] >= 'a' )&&( board[saf2][mod2] <= 'z'))
        {
        found = 0;

        }
}
else if (saf1<saf2&&mod1>mod2){j=mod1-1;
                    for (i=saf1+1;i<saf2;i++){


                        if (((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;
                                            break;
                                            }
                                     j--;}
    if((board[saf2][mod2] >= 'a' )&&( board[saf2][mod2] <= 'z'))
        {
        found = 0;

        }

}
        if (saf1==saf2&&mod1==mod2){found=0;}

}
 else if(x =='B'){found=1;
    if(saf1>saf2&&mod1<mod2){j=mod1+1;
            for (i=saf1-1;i>saf2;i--){

               if(((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;

                                            break;}
                                     j++;}
    if((board[saf2][mod2] >= 'A')&&( board[saf2][mod2] <= 'Z'))
        {
        found = 0;

        }
                            }
else if (saf1>saf2&&mod1>mod2){j=mod1-1;
            for (i=saf1-1;i>saf2;i--){

                        if (((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;break;}
                                     j--;}
    if((board[saf2][mod2] >= 'A' )&&( board[saf2][mod2] <= 'Z'))
        {
        found = 0;

        }
}
else if (saf1<saf2&&mod1<mod2){j=mod1+1;
            for (i=saf1+1;i<saf2;i++){

                        if (((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;break;}
                                     j++;}
    if((board[saf2][mod2] >= 'A' )&&( board[saf2][mod2] <= 'Z'))
        {
        found = 0;

        }
}
else if (saf1<saf2&&mod1>mod2){j=mod1-1;
                    for (i=saf1+1;i<saf2;i++){


                        if (((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;
                                            break;
                                            }
                                     j--;}
    if((board[saf2][mod2] >= 'A' )&&( board[saf2][mod2] <= 'Z'))
        {
        found = 0;

        }

}
if (saf1==saf2&&mod1==mod2){found=0;}


}
}
else {found=0;}
}

else if(x=='K'){
    if((abs(saf2-saf1)==1)&&((mod2-mod1==0))||(abs(mod2-mod1)==1)&&((saf2-saf1)==0)||((abs(saf2-saf1))==1)&&((abs(mod1-mod2))==1))
    {
    found=1;
    if((board[saf2][mod2] >= 'A') && (board[saf2][mod2] <= 'Z'))
        {
        found = 0;
        }
    }

else{if(!simulation)
        printf("invalid move\n");
    found=0;}
    }

else if(x=='k'){
    if((abs(saf2-saf1)==1)&&((mod2-mod1==0))||(abs(mod2-mod1)==1)&&((saf2-saf1)==0)||((abs(saf2-saf1))==1)&&((abs(mod1-mod2))==1))
    {
    found=1;
    if((board[saf2][mod2] >= 'a') && (board[saf2][mod2] <= 'z'))
        {
        found = 0;
        }
    }

else{
    found=0;}
    }




if(x=='q'){
    if(saf2==saf1||mod2==mod1)
    {found=1;
         if(saf1 == saf2){
                if (mod1>mod2){
               for( i=mod1-1;i>mod2;i--){
                  if(((board[saf1][i] >= 'a') &&( board[saf1][i] <= 'z'))||(board[saf1][i]>='A'&&board[saf1][i]<='Z')){
                    found = 0;

                    break;
                  }
                                        }
 if((board[saf2][mod2] >= 'a') &&( board[saf2][mod2] <= 'z'))
                  {
                      found=0;


                  }

                             }
                else if(mod2>mod1)
                {
                  for(i=mod1+1;i<mod2;i++){
                  if(((board[saf1][i]>='a')&&(board[saf1][i]<='z'))||((board[saf1][i]>='A')&&(board[saf1][i]<='Z')))
                    {
                    found = 0;

                  break;
                    }


                  }
 if((board[saf2][mod2] >= 'a') &&( board[saf2][mod2] <= 'z'))
                   {found = 0;



                   }
                }

         }

if(mod2 == mod1){
                if (saf1>saf2){
               for( i=saf1-1;i>saf2;i--){
                  if(((board[i][mod1] >= 'a') &&( board[i][mod1] <= 'z'))||(board[i][mod1]>='A'&&board[i][mod1]<='Z')){
                    found = 0;

                    break;
                  }

               }
                 if((board[saf2][mod2] >= 'a') &&( board[saf2][mod2] <= 'z'))
                  {
                      found=0;


                  }

                 }
                else if(saf2>saf1)
                {
                  for(i=saf1+1;i<saf2;i++){
                  if(((board[i][mod1]>='a')&&(board[i][mod1]<='z'))||((board[i][mod1]>='A')&&(board[i][mod1]<='Z')))
                    {
                    found = 0;

                  break;
                    }

                  }
    if((board[saf2][mod2] >= 'a') &&( board[saf2][mod2] <= 'z'))
            {found = 0;


            }


       }
}
 }
 else if((abs(saf1-saf2))==(abs(mod1-mod2))){found=1;
    if(saf1>saf2&&mod1<mod2){j=mod1+1;
            for (i=saf1-1;i>saf2;i--){

                        if(((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;

                                            break;}
                                     j++;}
    if((board[saf2][mod2] >= 'a')&&( board[saf2][mod2] <= 'z'))
        {
        found = 0;

        }
                            }
else if (saf1>saf2&&mod1>mod2){
        j=mod1-1;
            for (i=saf1-1;i>saf2;i--){

                        if (((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;break;}
                                     j--;}
    if((board[saf2][mod2] >= 'a' )&&( board[saf2][mod2] <= 'z'))
        {
        found = 0;

        }
}
else if (saf1<saf2&&mod1<mod2){
    j=mod1+1;
            for (i=saf1+1;i<saf2;i++){

                        if (((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;break;}
                                     j++;}
    if((board[saf2][mod2] >= 'a' )&&( board[saf2][mod2] <= 'z'))
        {
        found = 0;

        }
}
else if (saf1<saf2&&mod1>mod2){j=mod1-1;


                    for (i=saf1+1;i<saf2;i++){
                       if (((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;
                                            break;
                                            }
                                     j--;}
    if((board[saf2][mod2] >= 'a' )&&( board[saf2][mod2] <= 'z'))
        {
        found = 0;

        }
}

}
else {if(!simulation)
    printf("invalid move\n ");
found=0;
     }
             if (saf1==saf2&&mod1==mod2){found=0;}

}
if(x=='Q'){
    if(saf2==saf1||mod2==mod1)
    {found  =1;
         if(saf1 == saf2){
                if (mod1>mod2){
               for( i=mod1-1;i>mod2;i--){
                  if(((board[saf1][i] >= 'a') &&( board[saf1][i] <= 'z'))||(board[saf1][i]>='A'&&board[saf1][i]<='Z')){
                    found = 0;

                    break;
                  }
                                        }
 if((board[saf2][mod2] >= 'A') &&( board[saf2][mod2] <= 'Z'))
                  {
                      found=0;


                  }

                             }
                else if(mod2>mod1)
                {
                  for(i=mod1+1;i<mod2;i++){
                  if(((board[saf1][i]>='a')&&(board[saf1][i]<='z'))||((board[saf1][i]>='A')&&(board[saf1][i]<='Z')))
                    {
                    found = 0;

                  break;
                    }


                  }
 if((board[saf2][mod2] >= 'A') &&( board[saf2][mod2] <= 'Z'))
                   {found = 0;



                   }
                }

         }

if(mod2 == mod1){
                if (saf1>saf2){
               for( i=saf1-1;i>saf2;i--){
                  if(((board[i][mod1] >= 'a') &&( board[i][mod1] <= 'z'))||(board[i][mod1]>='A'&&board[i][mod1]<='Z')){
                    found = 0;

                    break;
                  }

               }
                 if((board[saf2][mod2] >= 'A') &&( board[saf2][mod2] <= 'Z'))
                  {
                      found=0;


                  }

                 }
                else if(saf2>saf1)
                {
                  for(i=saf1+1;i<saf2;i++){
                  if(((board[i][mod1]>='a')&&(board[i][mod1]<='z'))||((board[i][mod1]>='A')&&(board[i][mod1]<='Z')))
                    {
                    found = 0;

                  break;
                    }

                  }
    if((board[saf2][mod2] >= 'A') &&( board[saf2][mod2] <= 'Z'))
            {found = 0;


            }


       }
}
 }
 else if((abs(saf1-saf2))==(abs(mod1-mod2))){found=1;
    if(saf1>saf2&&mod1<mod2){j=mod1+1;
            for (i=saf1-1;i>saf2;i--){

                        if(((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;

                                            break;}
                                     j++;}
    if((board[saf2][mod2] >= 'A')&&( board[saf2][mod2] <= 'Z'))
        {
        found = 0;

        }
                            }
else if (saf1>saf2&&mod1>mod2){j=mod1-1;
            for (i=saf1-1;i>saf2;i--){

                        if (((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;break;}
                                     j--;}
    if((board[saf2][mod2] >= 'A' )&&( board[saf2][mod2] <= 'Z'))
        {
        found = 0;

        }
}
else if (saf1<saf2&&mod1<mod2){j=mod1+1;
            for (i=saf1+1;i<saf2;i++){

                        if (((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;break;printf("bb");}
                                     j++;}
    if((board[saf2][mod2] >= 'A' )&&( board[saf2][mod2] <= 'Z'))
        {
        found = 0;

        }
}
else if (saf1<saf2&&mod1>mod2){j=mod1-1;
                    for (i=saf1+1;i<saf2;i++){


                        if (((board[i][j]>='a')&&(board[i][j]<='z'))||((board[i][j]>='A')&&(board[i][j]<='Z')))
                                            {found=0;
                                            break;
                                            }
                                     j--;}
    if((board[saf2][mod2] >= 'A' )&&( board[saf2][mod2] <= 'Z'))
        {
        found = 0;

        }
}

}


else {
found=0;
     }


}



if (x=='p')

{ found=0;
j=saf1-1;
int k=mod1+1;
int l=mod1-1;
      if(saf2-saf1==-1&&mod2==mod1)
        { found=1;
            if((board[saf2][mod2]>='a')&&(board[saf2][mod2]<='z')||(board[saf2][mod2]>='A')&&(board[saf2][mod2]<='Z')){found=0;}
        }
      else if(saf1==6&&saf2==4&&mod2==mod1)
    {found=1;
            if((board[j][mod1]>='a')&&(board[j][mod1]<='z')||(board[j][mod1]>='A')&&(board[j][mod1]<='Z')){found=0;}
            else if((board[saf2][mod2]>='a')&&(board[saf2][mod2]<='z')||(board[saf2][mod2]>='A')&&(board[saf2][mod2]<='Z')){found=0;}
    }

      else if((board[j][k]>='A'&&board[j][k]<='Z')&&(saf2-saf1==-1&&mod2==mod1+1)){found=1;}
      else if((board[j][l]>='A'&&board[j][l]<='Z')&&(saf2-saf1==-1&&mod2==mod1-1)){found=1;}
}

 if (x=='P')

{ found=0;
j=saf1+1;
int k=mod1+1;
int l=mod1-1;
      if(saf2-saf1==1&&mod2==mod1)
        { found=1;
            if((board[saf2][mod2]>='a')&&(board[saf2][mod2]<='z')||(board[saf2][mod2]>='A')&&(board[saf2][mod2]<='Z')){found=0;}
        }
      else if(saf1==1&&saf2==3&&mod2==mod1)
    {found=1;
            if((board[j][mod1]>='a')&&(board[j][mod1]<='z')||(board[j][mod1]>='A')&&(board[j][mod1]<='Z')){found=0;}
            else if((board[saf2][mod2]>='a')&&(board[saf2][mod2]<='z')||(board[saf2][mod2]>='A')&&(board[saf2][mod2]<='Z')){found=0;}
    }

      else if((board[j][k]>='a'&&board[j][k]<='z')&&(saf2-saf1==1&&mod2==mod1+1)){found=1;}
      else if((board[j][l]>='a'&&board[j][l]<='z')&&(saf2-saf1==1&&mod2==mod1-1))
        {found=1;}
}


    return found;
}

int convertnumber(int x)
{int row;
row=8-x;
return row;

}


int main()
{
char save_piece,char3,sign,char1,char2,deadsmall[MAXSIZE],deadbig[MAXSIZE];
int col1,col2,stalematesmall,stalematecapital,num1,f,dangersmall=0,dangercapital=0,num2,row1,row2,counter=0,player=1;

    int i,j,k=0;
for(i=0;i<8;i++){
    for(j=0;j<8;j++)
    {
        board[i][j]=startboard[i][j];
    }
}
for (i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            undoredo[game][i][j]=board[i][j];
        }
    }


for(i=1;i<1000;i++){

printletters(letters,8);
printf("\n");
printboard();
printletters(letters,8);
int y=player%2;
if(y==1){
 collectMove(0);
dangersmall=checksmall();
if(sizeOfArray==0&&checksmall()==1){printf("\t\t\t CHECKMATE(Player2 Wins)");}
if(sizeOfArray==0&&checksmall()==0){printf("\t\tSTALEMATE");}

printf("PLAYER(1) Enter your move:\n");
int state=scanf("%c%d%c%d%c",&char1,&num1,&char2,&num2,&char3);

if(char1=='L')
    {load();
    continue;}
else if(char1=='S')
    {save();
        continue;}

/*else if (char1=='U')
   {undo_Redo(char1);continue;}
else if (char1=='R')
   {undo_Redo(char1);continue;}
*/
if(state<4)
{
   while( getchar()!='\n');
    continue;
}

if((char1>'I')&&(char1<='Z')||((char2>'I')&&(char2<='Z')))
{
printf("INVALID PLACE \n ");
char c=getchar();
while(c!='\n')
    {
    c=getchar();
    }
continue;
}

else if(!(num1>=1&&num1<=8)||!(num2>=1&&num2<=8))
{
printf("INVALID PLACE \n ");
char c=getchar();
while(c!='\n')
    {
    c=getchar();
    }
continue;
}
else if((char1>'Z')&&(char1<='z')||((char2>'Z')&&(char2<='z')))

{
printf("INVALID PLACE \n ");
char c=getchar();
while(c!='\n')
    {
    c=getchar();
    }
continue;
}
else if((char3!='\n')&&(char3!='r')&&(char3!='n')&&(char3!='b')&&(char3!='q'))
{
    /*printf("invalid character for promotion\n");*/

    char c=getchar();
    while(c!='\n')
    {
    c=getchar();
    }
continue;
}
    char c = getchar();
    while (c != '\n')
        c = getchar();

col1=convertchar(char1);
col2=convertchar(char2);
row1=convertnumber(num1);
row2=convertnumber(num2);
/*l7d hna zy alfol*/
char desiredpiece=board[row1][col1];
if(row1==1&&row2==0&&desiredpiece=='p')
{
    if(char3=='\n'){printf("ITS A PROMOTION>>invalid for promotion");
                     char c = getchar();
                     while (c != '\n')
                     c = getchar();
                        continue;
           }

}

int x=player%2;
if(x==1){
  if(desiredpiece=='p'||desiredpiece=='r'||desiredpiece=='b'||desiredpiece=='n'||desiredpiece=='q'||desiredpiece=='k'){f=1;}
        else{f=0;}
        }
if(f==0){
    printf("CANNOT MOVE OTHER PLAYER PIECES\n");
        continue;}


found=chechmove(desiredpiece,row1,row2,col1,col2);
if(found==0){
        if(!simulation)
            printf("INVALID MOVE\n");
        continue;}

else if(found==1){
        dead_capital(row1,col1,row2,col2);
        save_piece=board[row2][col2];
        board[row2][col2]=desiredpiece;


                }
sign=symbol(row1,col1);
board[row1][col1]=sign;
dangersmall=checksmall();
if(dangersmall==1)
{
    printf("YOUR KING IS STILL CHECKED\nCANNOT THS PLACE IS CHECKED\n");
    board[row1][col1]=board[row2][col2];
    if(save_piece>='A'&&save_piece<='Z'){board[row2][col2]=save_piece;}
    else{sign=symbol(row2,col2);
    board[row2][col2]=sign;}

    continue;
}
if(dangersmall==0&&board[row2][col2]=='p'&&row2==0)
{
    if(char3=='r'||char3=='b'||char3=='q'||char3=='n'||char3=='p')
    {board[row2][col2]=char3;}
}


player++;
game++;
}
else if(y==0){
collectMove(1);
dangercapital=checkcapital();
if(sizeOfArray==0&&dangercapital==1){printf("\t\t\t CHECKMATE(Player1 Wins)");
                                       break; }
if(sizeOfArray==0&&dangercapital==0){printf("\t\tSTALEMATE");
                                      break;          }



if(dangercapital==1){printf("YOUR KING IS CHECKED WATCH YOUR KING\n\n");}
printf("PLAYER(2) Enter your move :\n  ");
int state=scanf("%c%d%c%d%c",&char1,&num1,&char2,&num2,&char3);
if(char1=='\n')
{
    char c=getchar();
    while(c!='\n')
    {
        c=getchar();
    }
  continue;
}

if(char1=='L')
    {load();continue;}
else if(char1=='S')
    {save();continue;}
/*else if (char1=='U')
   {undo_Redo(char1);continue;}
else if (char1=='R')
   {undo_Redo(char1);continue;}*/
if(state<4)
{
   while( getchar()!='\n');
    continue;
}


if((char1>'I')&&(char1<='Z')||((char2>'I')&&(char2<='Z')))
{
printf("INVALID PLACE \n ");
char c=getchar();
while(c!='\n')
    {
    c=getchar();
    }
continue;
}
else if(!(num1>=1&&num1<=8)||!(num2>=1&&num2<=8))
{
printf("INVALID PLACE \n ");
char c=getchar();
while(c!='\n')
    {
    c=getchar();
    }
continue;
}
else if((char1>'Z')&&(char1<='z')||((char2>'Z')&&(char2<='z')))

{
printf("INVALID PLACE \n ");
char c=getchar();
while(c!='\n')
    {
    c=getchar();
    }
continue;
}
else if((char3!='\n')&&(char3!='R')&&(char3!='N')&&(char3!='B')&&(char3!='Q'))
{
    printf("invalid character for promotion\n");
char c=getchar();
while(c!='\n')
    {
    c=getchar();
    }
continue;
}

    char c = getchar();
    while (c != '\n')
        c = getchar();

col1=convertchar(char1);
col2=convertchar(char2);
row1=convertnumber(num1);
row2=convertnumber(num2);

char desiredpiece=board[row1][col1];
if(row1==6&&row2==7&&desiredpiece=='P')
{
    if(char3=='\n'){printf("ITS A PROMOTION>>invalid for promotion");
                     char c = getchar();
                     while (c != '\n')
                     c = getchar();
                        continue;
           }

}

int x=player%2;
if(x==0){
        if(desiredpiece=='P'||desiredpiece=='R'||desiredpiece=='B'||desiredpiece=='N'||desiredpiece=='Q'||desiredpiece=='K'){f=1;}
        else{f=0;}
        }
if(f==0){
    printf("CANNOT MOVE OTHER PLAYER PIECES\n");
        continue;}

found=chechmove(desiredpiece,row1,row2,col1,col2);
if(found==0){

        if(!simulation)
    printf("INVALID MOVE\n");
        continue;}
else if(found==1){
        dead_smal(row1,col1,row2,col2);
        save_piece=board[row2][col2];
        board[row2][col2]=desiredpiece; }
sign=symbol(row1,col1);
board[row1][col1]=sign;
dangercapital=checkcapital();
if(dangercapital==1)
{
    printf("YOUR KING IS STILL CHECKED\nCANNOT THS PLACE IS CHECKED\n");
    board[row1][col1]=board[row2][col2];
    if(save_piece>='a'&&save_piece<='z'){board[row2][col2]=save_piece;}
    else{sign=symbol(row2,col2);
    board[row2][col2]=sign;
        }
    continue;
}

if(dangercapital==0&&board[row2][col2]=='P'&&row2==7)
{
    if(char3=='R'||char3=='B'||char3=='Q'||char3=='N'||char3=='P')
    {board[row2][col2]=char3;}
}

player++;
game++;
}

}
return 0;

}

