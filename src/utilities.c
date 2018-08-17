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

int		d_10(void)
{
	uint32_t p;

	if (sodium_init() < 0)
        return -1; 

	p = randombytes_uniform(10);
	return (p + 1);
}

t_dice	add_dice(t_dice a, t_dice b)
{
	t_dice c;

	c.succes = a.succes + b.succes;
	c.throw_again = a.throw_again + b.throw_again;
	c.ones = a.ones + b.ones;
	return (c);
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