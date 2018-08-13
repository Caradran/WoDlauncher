#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct s_des
{
	int reussites;
	int relances;
	int uns;
}				t_des;

int D_10(void)
{
	double p;

	p = (double)rand()/RAND_MAX;
	p *= 10;
	return(p + 1);
}

t_des	WoD_result(int n, int seuil, int again, int rote, int flag)
{
	int		i = 0;
	int		d = 0;
	int		k = 0;
	t_des	des = {0, 0, 0};
	t_des	relance = {0, 0, 0};

	if (n <= 0 || seuil > 10 || again <= 1 || rote < 0)
		return (des);
	while (i < n)
	{
		d = D_10();
		if (!flag)
			printf("rote : %d\n", d);
		else
			printf("%d\n", d);
		if (d >= seuil)
		{
			k++;
			des.reussites++;
			if (d >= again)
				des.relances++;
		}
		if (d == 1)
		{
			des.relances--;
			des.reussites--;
			des.uns++;
		}
		i++;
	}
	if (rote > 0 && n - k > 0)
	{
		relance = WoD_result(n - k, seuil, again, rote - 1, 0);
		des.relances = des.relances + des.uns - relance.uns + relance.relances;
		des.reussites += relance.reussites;
		des.uns = relance.uns;
	}
	if (des.relances > 0 && flag)
	{
		relance = WoD_result(des.relances, seuil, again, 0, 1);
		if (relance.reussites > 0)
			des.reussites += relance.reussites;
	}
	return (des);
}

int main()
{
	int i;
	int j = 1;
	int	sum;
	int count;

	srand(time(NULL));
//	while (j <= 10)
//	{
		count = 0;
		sum = 0;
		i = 0;
//		while (i < 100000)
//		{
			printf("reussites : %d\n", WoD_result(2, 7, 7, 1, 1).reussites);
//			i++;
//		}

//		printf("%d %f\n", j, sum / 100000.0);
//		j++;
//	}
}