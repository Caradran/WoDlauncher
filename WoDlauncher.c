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

t_des	WoD_result(int n, int seuil, int again)
{
	int		i = 0;
	int		d = 0;
	t_des	des = {0, 0, 0};
	t_des	relance = {0, 0, 0};

	if (n <= 0 || seuil > 10 || again <= 1)
		return (des);
	while (i < n)
	{
		d = D_10();
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
	if (des.relances > 0)
	{
		relance = WoD_result(des.relances - des.uns, seuil, again);
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
	while (j <= 10)
	{
		count = 0;
		sum = 0;
		i = 0;
		while (i < 100000)
		{

			sum += WoD_result(j, 7, 6).reussites;
			i++;
		}

		printf("%d %f\n", j, sum / 100000.0);
		j++;
	}
}