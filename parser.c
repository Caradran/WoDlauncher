#include "WoDlauncher.h"

char	*ft_itoa(int n)
{
	int		sign;
	int		nb;
	int		len;
	char	*res;

	sign = 1;
	len = 1;
	if (n < 0)
		sign = -(len++);
	nb = n;
	while (nb /= 10)
		len++;
	if (!(res = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	res[len] = '\0';
	nb = n;
	while (len--)
	{
		res[len] = sign * (n % 10) + 48;
		n /= 10;
	}
	if (sign == -1 && nb != 0)
		res[0] = '-';
	return (res);
}

int		is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '-')
		return (1);
	return (0);
}

int		str_is_num(char *str)
{
	while (str && *str)
	{
		if (!is_num(*str))
			return (0);
		str++;
	}
	return (1);
}

int size_till_space(char *str)
{
	int i;
	int j;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '(')
		{
			j = 1;
			while (j != 0)
			{
				i++;
				if (str[i] == '(')
					j++;
				if (str[i] == ')')
					j--;
			}
		}
		i++;
	}
	return (i);
}

int		bracket(char *str)
{
	int i;
	int j;
	int nb_bra;
	int flag;

	i = 0;
	j = 0;
	nb_bra = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '(')
		{
			flag = 1;
			j++;
		}
		else if (str[i] == ')')
			j--;
		i++;
		if (j < 0)
			return (0);
		if (str[i] == '(' && j == 0 && flag)
			return (0);
	}
	if (j == 0)
		return (1);
	return (0);
}

int size_of_bra(char *str)
{
	int i;
	int j;
	int k;

	i = 0;
	while (str[i] && str[i] != '(')
		i++;
	if (!str[i])
		return (0);
	i++;
	k = 1;
	j = 0;
	while (str[i] && k)
	{
		if (str[i] == '(')
			k++;
		if (str[i] == ')')
			k--;
		j++;
		i++;
	}
	return (j - 1);
}

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