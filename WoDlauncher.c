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
	t_des	des = {0, 0, 0};
	t_des	relance = {0, 0, 0};

	if (n <= 0 || seuil > 10 || again <= 1 || rote < 0)
		return (des);
	while (i < n)
	{
		d = D_10();
		printf("%d\n", d);
		if (d >= seuil)
		{
			des.reussites++;
			if (d >= again)
				des.relances++;
		}
		if (d == 1)
		{
			des.reussites--;
			des.uns++;
		}
		i++;
	}
	if (rote > 0)
	{
		if (des.reussites - des.uns >= 0)
			relance = WoD_result(n - des.reussites + des.uns, seuil, again, rote - 1, 0);
		else
		{
			relance = WoD_result(n, seuil, again, rote - 1, 0);
			des.reussites = 0;
		}
		des.relances = des.relances + des.uns - relance.uns + relance.relances;
		des.reussites += relance.reussites;
	}
	if (des.relances > 0 && flag)
	{
		relance = WoD_result(des.relances - des.uns, seuil, again, 0, 1);
		des.reussites += relance.reussites + relance.uns;
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
			printf("reussites : %d\n", WoD_result(2, 7, 10, 1, 1).reussites);
//			i++;
//		}

//		printf("%d %f\n", j, sum / 100000.0);
//		j++;
//	}
}