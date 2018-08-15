#include <WoDlauncher.h>


static int D_10(void)
{
	double p;

	p = (double)rand()/RAND_MAX;
	p *= 10;
	return(p + 1);
}

static t_dice add_dice(t_dice a, t_dice b)
{
	t_dice c;

	c.succes = a.succes + b.succes;
	c.throw_again =  a.throw_again + b.throw_again;
	c.ones = a.ones + b.ones;
	
	return c;
}

static t_dice WoD_Launch(int n, int threshold, int again)
{
	t_dice	dice = {0, 0, 0};
	int i = 0;
	int d = 0;


	if (n <= 0 || threshold > 10 || again <= 1)
		return (dice);
	while (i < n)
	{
		d = D_10();
		printf("%d ", d);
		if (d >= threshold)
		{
			dice.succes++;
			if (d >= again)
				dice.throw_again++;
		}
		if (d == 1)
			dice.ones++;
		i++;
	}
	printf("\n");
	return (dice);
}

static t_dice	launch_rote(int n, int threshold, int again, int nb_rote, int flag)
{
	t_dice dice = {0, 0, 0};

	if (nb_rote <= 0 || n <= 0)
		return (dice);
	printf("rote: ");
	dice = WoD_Launch(n, threshold, again);
	if (!flag)
		dice.ones = 0;
	return (add_dice(dice, launch_rote(n - dice.succes, threshold, again, nb_rote - 1, 0)));
}

static t_dice	reroll(int n, int threshold, int again)
{
	t_dice dice = {0, 0, 0};

	if (n <= 0)
		return (dice);
	printf("reroll: ");
	dice = WoD_Launch(n, threshold, again);
	return (add_dice(dice, reroll(dice.throw_again - dice.ones, threshold, again)));
}

long int WoD_result(int n, int threshold, int again, int nb_rote)
{
	t_dice		rote = {0, 0, 0};
	t_dice		dice = {0, 0, 0};
	t_dice		retry = {0, 0, 0};

	if (n <= 0 || threshold > 10 || again <= 1 || nb_rote < 0)
		return (0);
	dice = WoD_Launch(n, threshold, again);
	rote = launch_rote(n - dice.succes, threshold, again, nb_rote, 1);
	retry = reroll(dice.throw_again + rote.throw_again - rote.ones, threshold, again);
	if (nb_rote > 0)
		return (retry.succes + dice.succes + rote.succes - rote.ones);
	return (retry.succes + dice.succes + rote.succes - dice.ones);
}

int main(int agrc, char **argv)
{
	srand(time(NULL));
	printf("\nsucces : %ld\n", WoD_result(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])));
}