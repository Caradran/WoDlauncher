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
		if (DEBUG)
			printf("%d, [%s]\n", size, str);
		if (!(tab[i] = malloc(sizeof(char) * (size + 1))))
			return (NULL);
		while (j < size)
		{
			tab[i][j] = str[j];
			j++;
		}
		tab[i][j] = 0;
		str = str + size;
		if (*str == ' ')
			str++;
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
	if (DEBUG)
		printf("roll [%s]\n", roll);
	split = split_roll(roll);
	i = 0;
	while (i < 4)
	{
		if (DEBUG)
			printf("test %d : '%s'\n", i, split[i]);
		if (!split[i] || !split[i][0])
		{
//			printf("test\n");
			if (i == 0)
				split[0] = "1";
			if (i == 1)
				split[1] = "8";
			if (i == 2)
				split[2] = "10";
			if (i == 3)
				split[3] = "0";
		}
		else if (!str_is_num(split[i]) && *extract_bracket(split[i]))
			split[i] = ft_itoa(parse(split[i]));
		i++;
	}
	res = wod_result(atoi(split[0]), atoi(split[1]), atoi(split[2]), atoi(split[3]));
	if (PRINT && 0)
		printf("resultat : %ld\n", res);
	return (res);
}

int main(int argc, char **argv)
{
	long int res;
	int i;
	double moy;
	double moy2;

	srand(time(NULL));
	if (argc == 2)
	{
		res = parse(argv[1]);
		printf("\n resultat final : %ld\n", res);
	}
	if (argc == 3)
	{
		i = 0;
		moy = 0;
		while (i < 10000)
		{
			res = parse(argv[1]);
			moy += res;
			moy2 += res * res;
			i++;
		}
		moy /= 10000;
		moy2 /= 10000;
		printf("moyen : %lf, ecart type : %lf\n", moy, sqrt(moy2 - moy * moy));
	}
	return (res);
}