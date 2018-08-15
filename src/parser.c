#include "WoDlauncher.h"

char	*extract_bracket(char *str)
{
	char	*bra;
	int size;
	int k;
	int i;

	i = 0;
	size = size_of_bra(str);
	if (!(bra = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (str[i] && str[i] != '(')
		i++;
	i++;
	k = 0;
	while (k < size)
	{
		bra[k] = str[i + k];
		k++;
	}
	bra[size] = '\0';
	return (bra);
}

char 	**split_roll(char *str)
{
	char **tab;
	int size;
	int i;
	int j;

	if (!str || !(tab = (char**)malloc(sizeof(char*) * 5)))
		return (NULL);
	i = 0;
	while (i < 4)
	{
		j = 0;
		size = size_till_space(str);
		if (!(tab[i] = malloc(sizeof(char) * (size + 1))))
			return (NULL);
		while (j < size)
		{
			tab[i][j] = str[j];
			j++;
		}
		tab[i][j] = 0;
		str = str + size + 1;
		i++;
	}
	return (tab);
}

long int	parse(char *str)
{
	char	*roll;
	char	**split;
	int		num[4];
	int		i;
	long int res;

	if (!str || !bracket(str))
		return (0);
	roll = extract_bracket(str);
	split = split_roll(roll);
	i = 0;
	while (i < 4)
	{
		if (!str_is_num(split[i]))
			split[i] = ft_itoa(parse(split[i]));
		i++;
	}
	res = wod_result(atoi(split[0]), atoi(split[1]), atoi(split[2]), atoi(split[3]));
	if (PRINT)
		printf("resultat :%ld\n", res);
	return (res);
}

int main(int argc, char **argv)
{
	long int tab;

	srand(time(NULL));
	if (argc == 2)
	{
		tab = parse(argv[1]);
		printf("%ld\n", tab);
	}
	return (0);
}