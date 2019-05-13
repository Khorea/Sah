#include <stdio.h>
#include <math.h>
#include "sah.h"

struct pion
{
    int i;
    char j;
    int vulnerabil;
} pionMare[8], pionMic[8];

void init()
{
    for(int i=0; i<8; i++)
    {
        pionMare[i].i=2;
        pionMare[i].j='a'+i;
        pionMare[i].vulnerabil=0;

        pionMic[i].i=7;
        pionMic[i].j='a'+i;
        pionMic[i].vulnerabil=0;
    }
}

int find(char a[][9], char piece, char *cols, int *rows)
{
    int k=0;

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(a[i][j]==piece)
            {
                *(cols+k)='a'+j;
                *(rows+k)=8-i;
                k++;
            }
        }
    }

    return k;
}

void move(char *a, char c1, int r1, char c2, int r2)
{
    char *chr1=(a+9*(8-r1)+c1-'a'), *chr2=(a+9*(8-r2)+c2-'a');

    *chr2=*chr1;
    *chr1='_';
}

void updatePawns(char *a, char c1, int r1, char c2, int r2)
{
    char *chr1=(a+9*(8-r1)+c1-'a'), *chr2=(a+9*(8-r2)+c2-'a');

    if(*chr1=='p')
    {
        if(r2==r1-2)
        {
            for(int i=0; i<8; i++)
            {
                if(pionMic[i].i==r1 && pionMic[i].j==c1)
                {
                    pionMic[i].i=r2;
                    pionMic[i].j=c2;
                    pionMic[i].vulnerabil=1;
                    break;
                }
            }
        }
        else
        {
            for(int i=0; i<8; i++)
            {
                if(pionMic[i].i==r1 && pionMic[i].j==c1)
                {
                    pionMic[i].i=r2;
                    pionMic[i].j=c2;
                    pionMic[i].vulnerabil=0;
                    break;
                }
            }
        }

        for(int i=0; i<8; i++)
        {
            if(((pionMare[i].i==r1 && pionMare[i].j==c2) && pionMare[i].vulnerabil) && *chr2=='_')
            {
                pionMare[i].i==0;
                pionMare[i].j==0;
                *(a+9*(8-r1)+c2-'a')='_';
            }
        }
    }
    else if (*chr1=='P')
    {
        if(r2==r1+2)
        {
            for(int i=0; i<8; i++)
            {
                if(pionMare[i].i==r1 && pionMare[i].j==c1)
                {
                    pionMare[i].i=r2;
                    pionMare[i].j=c2;
                    pionMare[i].vulnerabil=1;
                    break;
                }
            }
        }
        else
        {
            for(int i=0; i<8; i++)
            {
                if(pionMare[i].i==r1 && pionMare[i].j==c1)
                {
                    pionMare[i].i=r2;
                    pionMare[i].j=c2;
                    pionMare[i].vulnerabil=0;
                    break;
                }
            }
        }

        for(int i=0; i<8; i++)
        {
            if(((pionMic[i].i==r1 && pionMic[i].j==c2) && pionMic[i].vulnerabil) && *chr2=='_')
            {
                pionMic[i].i=0;
                pionMic[i].j=0;
                *(a+9*(8-r1)+c2-'a')='_';
            }
        }
    }

    if(*chr2=='p')
    {
        for(int i=0; i<8; i++)
        {
            if(pionMic[i].i==r2 && pionMic[i].j==c2)
            {
                pionMic[i].i=0;
                pionMic[i].j=0;
                break;
            }
        }
    }
    else if(*chr2=='P')
    {
        for(int i=0; i<8; i++)
        {
            if(pionMare[i].i==r2 && pionMare[i].j==c2)
            {
                pionMare[i].i=0;
                pionMare[i].j=0;
                break;
            }
        }
    }
}

void afiseaza(char *a)
{
    printf("\n\n    a b c d e f g h\n\n");

    for(int i=0; i<8; i++)
    {
        printf("%d   ", 8-i);
        for(int j=0; j<8; j++)
        {
            printf("%c ", *(a+i*9+j));
        }
        printf("   %d\n", 8-i);
    }

    printf("\n    a b c d e f g h\n\n");
}


void egal(char *a, char *b)
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<9; j++)
        {
            *(b+9*i+j)=*(a+9*i+j);
        }
    }
}

void createControlMatrix(char *a, char *c, int player)
{
    if(player)
    {
        for(int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                char chr = *(a+9*i+j);

                if('A'<=chr && chr<='Z')
                {
                    for(int k=0; k<8; k++)
                    {
                        for(int p=0; p<8; p++)
                        {
                            if(isValidMove(a, j+'a', 8-i, p+'a', 8-k)) *(c+9*k+p)='1';
                        }
                    }
                }
            }
        }
    }
    else
    {
        for(int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                char chr = *(a+9*i+j);

                if('a'<=chr && chr<='z')
                {
                    for(int k=0; k<8; k++)
                    {
                        for(int p=0; p<8; p++)
                        {
                            if(isValidMove(a, j+'a', 8-i, p+'a', 8-k)) *(c+9*k+p)='1';
                        }
                    }
                }
            }
        }
    }
}

int sah(char *a, int player)
{
    char c[8][9] = {"00000000", "00000000", "00000000", "00000000", "00000000", "00000000", "00000000", "00000000"};
    createControlMatrix(a, c, (player)?0:1);

    if(player)
    {
        for(int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                if(*(a+9*i+j)=='K')
                {
                    if(c[i][j]=='1') return 1;
                    else return 0;
                }
            }
        }
    }
    else
    {
        for(int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                if(*(a+9*i+j)=='k')
                {
                    if(c[i][j]=='1') return 1;
                    else return 0;
                }
            }
        }
    }

    return 0;
}

int mat(char *a, int player)
{
    if(player)
    {
        for(int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                char chr = *(a+9*i+j);

                if('A'<=chr && chr<='Z')
                {
                    for(int k=0; k<8; k++)
                    {
                        for(int p=0; p<8; p++)
                        {
                            if(isValidMove(a, j+'a', 8-i, p+'a', 8-k))
                            {
                                char vmatrix[8][9];

                                egal(a, vmatrix);
                                move(vmatrix, j+'a', 8-i, p+'a', 8-k);
                                if(!sah(vmatrix, player)) return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        for(int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                char chr = *(a+9*i+j);

                if('a'<=chr && chr<='z')
                {
                    for(int k=0; k<8; k++)
                    {
                        for(int p=0; p<8; p++)
                        {
                            if(isValidMove(a, j+'a', 8-i, p+'a', 8-k))
                            {
                                char vmatrix[8][9];
                                char c[8][9] = {"00000000", "00000000", "00000000", "00000000", "00000000", "00000000", "00000000", "00000000"};

                                egal(a, vmatrix);
                                move(vmatrix, j+'a', 8-i, p+'a', 8-k);
                                if(!sah(vmatrix, player)) return 0;
                            }
                        }
                    }
                }
            }
        }
    }

    return 1;
}

int isValidMove(char *a, char c1, int r1, char c2, int r2)
{
    // 1 --> Valid, 0 --> Invalid

    if(r2>8 || r2<1 || c2>'h' || c2<'a' || (r1==r2 && c1==c2)) return 0;
    char chr1=*(a+9*(8-r1)+c1-'a'), chr2=*(a+9*(8-r2)+c2-'a');

    int i=r1, j=c1;

    switch(chr1)
    {
    case '_':
        return 0;
        break;
    case 'R':
        if('A'<=chr2 && chr2<='Z') return 0;
        if(r1!=r2 && c1!=c2) return 0;
        if(r2<r1)
        {
            while(i>r2+1)
            {
                i--;
                if(*(a+9*(8-i)+c1-'a')!='_') return 0;
            }
        }
        else if(r2>r1)
        {
            while(i<r2-1)
            {
                i++;
                if(*(a+9*(8-i)+c1-'a')!='_') return 0;
            }
        }
        else if(c2<c1)
        {
            while(j>c2+1)
            {
                j--;
                if(*(a+9*(8-r1)+j-'a')!='_') return 0;
            }
        }
        else
        {
            while(j<c2-1)
            {
                j++;
                if(*(a+9*(8-r1)+j-'a')!='_') return 0;
            }
        }
        return 1;
        break;
    case 'H':
        if('A'<=chr2 && chr2<='Z') return 0;
        if((r1-r2)*(r1-r2)+(c1-c2)*(c1-c2)!=5) return 0;
        return 1;
        break;
    case 'B':
        if('A'<=chr2 && chr2<='Z') return 0;
        if(abs(r2-r1)!=abs(c2-c1)) return 0;
        if(r2>r1 && c2>c1)
        {
            while(i<r2-1)
            {
                i++;
                j++;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        else if(r2>r1 && c2<c1)
        {
            while(i<r2-1)
            {
                i++;
                j--;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        else if(r2<r1 && c2>c1)
        {
            while(i>r2+1)
            {
                i--;
                j++;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        else
        {
            while(i>r2+1)
            {
                i--;
                j--;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        return 1;
        break;
    case 'K':
        if('A'<=chr2 && chr2<='Z') return 0;
        if((r1-r2)*(r1-r2)+(c1-c2)*(c1-c2)>2.001) return 0;
        return 1;
        break;
    case 'Q':
        if('A'<=chr2 && chr2<='Z') return 0;
        if(abs(r2-r1)!=abs(c2-c1) && (r1!=r2 && c1!=c2)) return 0;
        if(r2>r1 && c2>c1)
        {
            while(i<r2-1)
            {
                i++;
                j++;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        else if(r2>r1 && c2<c1)
        {
            while(i<r2-1)
            {
                i++;
                j--;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        else if(r2<r1 && c2>c1)
        {
            while(i>r2+1)
            {
                i--;
                j++;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        else if(r2<r1 && c2<c1)
        {
            while(i>r2+1)
            {
                i--;
                j--;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        else if(r2<r1)
        {
            while(i>r2+1)
            {
                i--;
                if(*(a+9*(8-i)+c1-'a')!='_') return 0;
            }
        }
        else if(r2>r1)
        {
            while(i<r2-1)
            {
                i++;
                if(*(a+9*(8-i)+c1-'a')!='_') return 0;
            }
        }
        else if(c2<c1)
        {
            while(j>c2+1)
            {
                j--;
                if(*(a+9*(8-r1)+j-'a')!='_') return 0;
            }
        }
        else
        {
            while(j<c2-1)
            {
                j++;
                if(*(a+9*(8-r1)+j-'a')!='_') return 0;
            }
        }
        return 1;
        break;
    case 'P':
        if('A'<=chr2 && chr2<='Z') return 0;
        if((c2==c1+1 || c2==c1-1) && r2==r1+1)
        {
            if('a'<=chr2 && chr2<='z')
            {
                return 1;
            }

            if(*(a+9*(8-r1)+c2-'a')=='p')
            {
                for(int i=0; i<8; i++)
                {
                    if((pionMic[i].i==r1 && pionMic[i].j==c2) && pionMic[i].vulnerabil)
                    {
                        return 1;
                    }
                }
            }
        }
        if(r1==2)
        {
            if((r2!=r1+1 && r2!=r1+2)||(c2!=c1)) return 0;
            if(r2==r1+2)
            {
                if(*(a+9*(8-(r1+1))+c1-'a')!='_') return 0;
            }
        }
        else
        {
            if((r2!=r1+1) || (c2!=c1)) return 0;
        }
        return 1;
        break;
    case 'r':
        if('a'<=chr2 && chr2<='z') return 0;
        if(r1!=r2 && c1!=c2) return 0;
        if(r2<r1)
        {
            while(i>r2+1)
            {
                i--;
                if(*(a+9*(8-i)+c1-'a')!='_') return 0;
            }
        }
        else if(r2>r1)
        {
            while(i<r2-1)
            {
                i++;
                if(*(a+9*(8-i)+c1-'a')!='_') return 0;
            }
        }
        else if(c2<c1)
        {
            while(j>c2+1)
            {
                j--;
                if(*(a+9*(8-r1)+j-'a')!='_') return 0;
            }
        }
        else
        {
            while(j<c2-1)
            {
                j++;
                if(*(a+9*(8-r1)+j-'a')!='_') return 0;
            }
        }
        return 1;
        break;
    case 'h':
        if('a'<=chr2 && chr2<='z') return 0;
        if((r1-r2)*(r1-r2)+(c1-c2)*(c1-c2)!=5) return 0;
        return 1;
        break;
    case 'b':
        if('a'<=chr2 && chr2<='z') return 0;
        if(abs(r2-r1)!=abs(c2-c1)) return 0;
        if(r2>r1 && c2>c1)
        {
            while(i<r2-1)
            {
                i++;
                j++;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        else if(r2>r1 && c2<c1)
        {
            while(i<r2-1)
            {
                i++;
                j--;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        else if(r2<r1 && c2>c1)
        {
            while(i>r2+1)
            {
                i--;
                j++;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        else
        {
            while(i>r2+1)
            {
                i--;
                j--;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        return 1;
        break;
    case 'k':
        if('a'<=chr2 && chr2<='z') return 0;
        if((r1-r2)*(r1-r2)+(c1-c2)*(c1-c2)>2.001) return 0;
        return 1;
        break;
    case 'q':
        if('a'<=chr2 && chr2<='z') return 0;
        if(abs(r2-r1)!=abs(c2-c1) && (r1!=r2 && c1!=c2)) return 0;
        if(r2>r1 && c2>c1)
        {
            while(i<r2-1)
            {
                i++;
                j++;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        else if(r2>r1 && c2<c1)
        {
            while(i<r2-1)
            {
                i++;
                j--;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        else if(r2<r1 && c2>c1)
        {
            while(i>r2+1)
            {
                i--;
                j++;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        else if(r2<r1 && c2<c1)
        {
            while(i>r2+1)
            {
                i--;
                j--;
                if(*(a+9*(8-i)+j-'a')!='_') return 0;
            }
        }
        else if(r2<r1)
        {
            while(i>r2+1)
            {
                i--;
                if(*(a+9*(8-i)+c1-'a')!='_') return 0;
            }
        }
        else if(r2>r1)
        {
            while(i<r2-1)
            {
                i++;
                if(*(a+9*(8-i)+c1-'a')!='_') return 0;
            }
        }
        else if(c2<c1)
        {
            while(j>c2+1)
            {
                j--;
                if(*(a+9*(8-r1)+j-'a')!='_') return 0;
            }
        }
        else
        {
            while(j<c2-1)
            {
                j++;
                if(*(a+9*(8-r1)+j-'a')!='_') return 0;
            }
        }
        return 1;
        break;
    case 'p':
        if('a'<=chr2 && chr2<='z') return 0;
        if((c2==c1+1 || c2==c1-1) && r2==r1-1)
        {
            if('A'<=chr2 && chr2<='Z')
            {
                return 1;
            }
            if(*(a+9*(8-r1)+c2-'a')=='P')
            {
                for(int i=0; i<8; i++)
                {
                    if((pionMare[i].i==r1 && pionMare[i].j==c2) && pionMare[i].vulnerabil)
                    {
                        return 1;
                    }
                }
            }
        }
        if(r1==7)
        {
            if((r2!=r1-1 && r2!=r1-2) || (c2!=c1)) return 0;
            if(r2==r1-2)
            {
                if(*(a+9*(8-(r1-1))+c1-'a')!='_') return 0;
            }
        }
        else
        {
            if((r2!=r1-1) || (c2!=c1)) return 0;
        }
        return 1;
    }

    return 0;
}

