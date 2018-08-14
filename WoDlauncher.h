#ifndef WODLAUNCHER_H
# define WODLAUNCHER_H

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef struct s_dice
{
	long int succes;
	int throw_again;
	int ones;
}				t_dice;

long int	WoD_result(int n, int threshold, int again, int nb_rote);

#endif