#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int D_10(void)
{
	double p;

	p = (double)rand()/RAND_MAX;
	p *= 10;
	return(p + 1);
}

int WoD_result(int n, int seuil)
{
	int i = 0;
	int dixs = 0;
	int reussites = 0;
	int d = 0;

	if (n <= 0 || seuil > 10)
		return (reussites);
	while (i < n)
	{
		d = D_10();
//		printf("%d ", d);
		if (d >= seuil)
		{
			reussites++;
			if (d == 10)
				dixs++;
		}
		if (d == 1)
		{
			reussites--;
			dixs--;
		}
		i++;
	}
//	printf("\n");
	if (dixs > 0)
		reussites += WoD_result(dixs, seuil);
	return (reussites);
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
		while (i < 10000000)
		{
			if (WoD_result(j, 7) < 0)
				count++;

//			sum += WoD_result(j, 7);
//			printf("%d\n", WoD_result(j, 7));
			i++;
		}
		printf("%d %f\n", j, count/10000000.0);
		printf("\n");
//		printf("%f\n", sum / 100000.0);
		j++;
	}
}