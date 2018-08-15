#ifndef WODLAUNCHER_H
# define WODLAUNCHER_H

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define PRINT 1

typedef struct	s_dice
{
	long int	succes;
	int			throw_again;
	int			ones;
}				t_dice;

typedef	struct	s_ast
{
	int				node_type;
	int				node_value;
	struct s_ast	*nb_dice;
	struct s_ast	*threshold;
	struct s_ast	*again;
	struct s_ast	*nb_rote;

}				t_ast;

char		*ft_itoa(int n);
int			is_num(char c);
int			d_10(void);
t_dice		add_dice(t_dice a, t_dice b);
int			str_is_num(char *str);
int 		size_till_space(char *str);
int			bracket(char *str);
int 		size_of_bra(char *str);
long int	wod_result(int n, int threshold, int again, int nb_rote);

#endif
