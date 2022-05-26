#include <stdio.h>
#include <stdlib.h>
# include <time.h>
# include "sodium.h"

typedef struct  s_rodent
{
    int         dex;
    int         force;
    int         stam;
    int         pdv;
    int         att;
    int         deg;
}               t_rodent;

int     d_100(void)
{
    uint32_t p;

    if (sodium_init() < 0)
        return -1; 

    p = randombytes_uniform(100);
    return (p + 1);
}

int 	d_3(void)
{
	uint32_t p;

    if (sodium_init() < 0)
        return -1; 

    p = randombytes_uniform(2);
    return (p - 1);
}

int attack(int adex, int aforce)
{
    float r;

    r = 50 + 3*adex/4.0 + aforce/4.0;
    if (r != (int)r)
        r += 1;
    return ((int)r);
}

float prob(t_rodent r, int ddex)
{
    float att;

    att = (r.att - ddex)/100.0;
    if (att < 0.1)
        return (2 * 0.1 - 0.01);
    if (att > 0.95)
        return (2 * 0.95 - 0.95 * 0.95);
    att = 2 * att - att * att;
    return (att);
}

int  attack_lauch(t_rodent r, int ddex)
{
    int att;
    int p1;
    int p2;

    att = r.att - ddex;
    if (att < 10)
        att = 10;
    else if (att > 95)
        att = 95;
    p1 = d_100();
    p2 = d_100();
    if (att >= 50 && (p1 < att / 10 || p2 < att / 10))
        return (2);
    if (p1 < att || p2 < att)
        return (1);
    return (0);
}

void battle(t_rodent *r1, t_rodent *r2)
{
    int a;

    a = attack_lauch(*r1, r2->dex);
    if (a == 1)
        r2->pdv -= r1->deg + d_3();
    if (a == 2)
        r2->pdv -= (int)((r1->deg + d_3()) * 1.5);
    if (r2->pdv <= 0)
        return ;
    a = attack_lauch(*r2, r1->dex);
    if (a == 1)
        r1->pdv -= r2->deg + d_3();
    if (a == 2)
        r1->pdv -= (int)((r2->deg + d_3()) * 1.5);
}

int degats(int force)
{
    float forc;

    forc = force/5.0;
    if (forc != (int)forc)
        forc = forc + 1;
    return (((int)forc));
}

float degats_moy(t_rodent r, int ddex)
{
    return (r.deg*prob(r, ddex));
}

int     pdv(int stam)
{
    float pdv;

    pdv = 7 + stam/2;
    if (pdv != (int)pdv)
        pdv += 1;
    return ((int)pdv);
}

int     combat_print(t_rodent r1, t_rodent r2)
{
    t_rodent tmp;
    int round;
    int f_swap;

    f_swap = 0;
    if (r1.dex < r2.dex)
    {
        tmp = r1;
        r1 = r2;
        r2 = tmp;
        f_swap = 1;
    }
    round = 0;
    printf("\nexemple de combat : \n");
    while(r1.pdv > 0 && r2.pdv > 0)
    {
        if (!f_swap)
            printf("round %2d : pdv r1 : %3d, pdv r2 : %3d\n", round, r1.pdv, r2.pdv);
        else
            printf("round %2d : pdv r1 : %3d, pdv r2 : %3d\n", round, r2.pdv, r1.pdv);
        round++;
        battle(&r1, &r2);
    }
    if (!f_swap)
        printf("round %2d : pdv r1 : %3d, pdv r2 : %3d\n\n", round, r1.pdv, r2.pdv);
    else
        printf("round %2d : pdv r1 : %3d, pdv r2 : %3d\n\n", round, r2.pdv, r1.pdv);
    if ((r1.pdv <= 0 && !f_swap) || (r2.pdv <= 0 && f_swap))
    {
        printf("r2 gagne en %d tours\n", round);
        return (2);
    }
    else
    {
        printf("r1 gagne en %d tours\n", round);
        return (1);
    }
}
int     combat(t_rodent r1, t_rodent r2)
{
    t_rodent tmp;
    int f_swap;

    f_swap = 0;
    if (r1.dex < r2.dex)
    {
        tmp = r1;
        r1 = r2;
        r2 = tmp;
        f_swap = 1;
    }
    while(r1.pdv > 0 && r2.pdv > 0)
        battle(&r1, &r2);
    if ((r1.pdv <= 0 && !f_swap) || (r2.pdv <= 0 && f_swap))
        return (0);
    else
        return (1);
}

void    combat_stats(t_rodent r1, t_rodent r2, int n)
{
    float count;
    int i;

    i = 0;
    count = 0;
    while (i++ < n)
        count += combat(r1, r2);
    printf("\nr1 gagne %.3f%% des combats\n", 100.0 * count/n);
}

int     combat_moy(t_rodent r1, t_rodent r2)
{
    float deg1;
    float deg2;
    float tours1;
    float tours2;

    deg1 = degats_moy(r1, r2.dex);
    deg2 = degats_moy(r2, r1.dex);
    if (deg1 == 0 || deg2 == 0)
        return (0);
    tours1 = r1.pdv/deg2;
    tours2 = r2.pdv/deg1;
    printf("Stats :\n");
    printf("deg moyen 1 : %.3f\n", deg1);
    printf("deg moyen 2 : %.3f\n\n", deg2);
    if (tours1 > tours2)
    {
        printf("en moyenne 1 gagne en %.2f tours\n2 aurait pris %.2f tours\n", tours2, tours1);
        return (1);
    }
    else if (tours2 > tours1)
    {
        printf("en moyenne 2 gagne en %.2f tours\n1 aurait pris %.2f tours\n", tours1, tours2);
        return (2);
    }
    else
    {
        printf("en moyenne ex equo en %.2f tours\n\n", tours1);
        return (0);
    }
}

t_rodent init_rodent(int dex, int force, int stam)
{
    t_rodent r;

    r.dex = dex;
    r.force = force;
    r.stam = stam;
    r.pdv = pdv(stam);
    r.att = attack(r.dex, r.force);
    r.deg = degats(r.force);
    return (r);
}

void    print_rodent(t_rodent r1, t_rodent r2)
{
    printf("\ncharacteristiques : \n");
    printf("rodent 1 : dex %3d, for %3d, sta %3d, pdv %3d, att %3d, deg %3d, prob %.3f\n", r1.dex, r1.force, r1.stam, r1.pdv, r1.att, r1.deg, prob(r1, r2.dex));
    printf("rodent 2 : dex %3d, for %3d, sta %3d, pdv %3d, att %3d, deg %3d, prob %.3f\n\n", r2.dex, r2.force, r2.stam, r2.pdv, r2.att, r2.deg, prob(r2, r1.dex));
}

int main(int argc, char **argv)
{
    t_rodent r1;
    t_rodent r2;

    srand(time(NULL));
    if (argc != 7)
        return (printf("usage :\n   ./a.out att1 dex1 stam1 att2 dex2 stam2\n"));
    if (atoi(argv[2]) <= 0 && atoi(argv[5]) <= 0)
    	return (printf("...\n"));
    r1 = init_rodent(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    r2 = init_rodent(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
    print_rodent(r1, r2);
    combat_moy(r1, r2);
    combat_stats(r1, r2, 10000);
    combat_print(r1, r2);
    return (0);
}