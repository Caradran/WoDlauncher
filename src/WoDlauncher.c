#include "WoDlauncher.h"

static t_dice	wod_launch(int n, int threshold, int again)
{
	t_dice	dice;
	int		i;
	int		d;

	dice = (t_dice){0, 0};
	if (n <= 0 || threshold > 10 || again <= 1)
		return (dice);
	i = 0;
	while (i < n)
	{
		d = d_10();
		if (PRINT)
		{
			if (d >= threshold)
				printf("***%d*** ", d);
			else
				printf("%d ", d);
		}
		if (d >= threshold)
			dice.succes++;
		if (d >= again)
			dice.throw_again++;
		i++;
	}
	if (DEBUG)
		printf("\nsucces %ld, again %d", dice.succes, dice.throw_again);
	if (PRINT)
		printf("\n");
	return (dice);
}

static t_dice	launch_rote(int n, int threshold, int again, int nb_rote)
{
	t_dice dice;

	dice = (t_dice){0, 0};
	if (nb_rote <= 0 || n <= 0)
		return (dice);
	if (PRINT)
		printf("rote: ");
	dice = wod_launch(n, threshold, again);
	return (add_dice(dice, launch_rote(n - dice.succes, threshold, again, nb_rote - 1)));
}

static t_dice	reroll(int n, int threshold, int again)
{
	t_dice dice;

	dice = (t_dice){0, 0};
	if (n <= 0)
		return (dice);
	if (PRINT)
		printf("reroll: ");
	dice = wod_launch(n, threshold, again);
	return (add_dice(dice, reroll(dice.throw_again, threshold, again)));
}

long int		wod_result(int n, int threshold, int again, int nb_rote)
{
	t_dice		rote;
	t_dice		dice;
	t_dice		retry;

	if (n <= 0 || threshold > 10 || again <= 1 || nb_rote < 0 || n > 10000000)
		return (0);
	dice = wod_launch(n, threshold, again);
	rote = launch_rote(n - dice.succes, threshold, again, nb_rote);
	if (nb_rote > 0)
		retry = reroll(dice.throw_again + rote.throw_again, threshold, again);
	else
		retry = reroll(dice.throw_again, threshold, again);
	if (retry.succes < 0)
		retry.succes = 0;
	if (nb_rote > 0)
		return (retry.succes + dice.succes + rote.succes);
	return (retry.succes + dice.succes + rote.succes);
}
/*
int				main(int agrc, char **argv)
{
	srand(time(NULL));
	printf("\nsucces : %ld\n", wod_result(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])));
}
*/