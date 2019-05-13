#include <stdlib.h>
#include "sah.h"

int main(void)
{
    //char piesa; scanf(" %c", &piesa);
    char a[8][9]= {"rhbkqbhr", "pppppppp", "________", "________", "________", "________", "PPPPPPPP", "RHBKQBHR"};
    //char a[8][9]= {"___k____", "________", "________", "________", "________", "________", "________", "R__K___R"};
    char b[8][9];

    egal(a,b);
    init();
    //char cols[64];
    //int rows[64];
    //int nr=find(a, piesa, cols, rows);

    /**<  printf("\nNumarul de piese '%c' este %d\n\n", piesa, nr);
    for(int i=0;i<nr;i++)
    {
    	printf("Randul %d, coloana %c\n", rows[i], cols[i]);
    } */

    //printf("\n\n");

    afiseaza(a);

    int player=1;
    int r1, r2;
    char c1, c2;
    char chr1, chr2;

    while(1)
    {
        here:

        scanf(" %c", &c1);
        scanf("%d-", &r1);
        scanf(" %c", &c2);
        scanf("%d", &r2);

        chr1=a[8-r1][c1-'a'];

        if((!player && ('a'<=chr1 && chr1<'z')) || (player && ('A'<=chr1 && chr1<'Z')))
        {
            if(isValidMove(a,c1,r1,c2,r2))
            {
                move(b, c1, r1, c2, r2);
                if(sah(b, player))
                {
                    if(mat(a, player)) break;
                    printf("Sah\n");
                    egal(a, b);
                    goto here;
                }
                updatePawns(a, c1, r1, c2, r2);
                move(a, c1, r1, c2, r2);
                afiseaza(a);
            }
            else
            {
                do
                {
                    printf("Miscare Imposibila\n");
                    scanf(" %c", &c1);
                    scanf("%d-", &r1);
                    scanf(" %c", &c2);
                    scanf("%d", &r2);
                }
                while(!isValidMove(a,c1,r1,c2,r2));

                chr1=a[8-r1][c1-'a'];

                if((!player && ('a'<=chr1 && chr1<'z')) || (player && ('A'<=chr1 && chr1<'Z')))
                {
                    move(b, c1, r1, c2,r2);
                    if(sah(b, player))
                    {
                        if(mat(a, player)) break;
                        printf("Sah\n");
                        egal(a, b);
                        goto here;
                    }
                    updatePawns(a, c1, r1, c2, r2);
                    move(a, c1, r1, c2, r2);
                    afiseaza(a);
                }
                else
                {
                    (chr1!='_')? printf("Piesa %c nu va apartine\n", chr1):printf("Alegeti o piesa\n");
                    goto here;
                }
            }
        }
        else
        {
            (chr1!='_')? printf("Piesa %c nu va apartine\n", chr1):printf("Alegeti o piesa\n");
            goto here;
        }

        if(player)
        {
            player=0;
        }
        else player=1;

        if(mat(a, player)) break;
    }

    printf("Gavemover\nPlayer %d wins", (player)?1:2);
}
