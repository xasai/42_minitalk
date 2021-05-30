#include "miniclient.h"

int	ft_atoi(const char *nptr)
{
	long	num;
	int		sign;

	sign = 1;
	num = 0;
	while (*nptr == ' ' || (*nptr >= 7 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*(nptr++) == '-')
			sign = -1;
	}
	while (ft_isdigit(*nptr))
	{
		num = num * 10 + *nptr - '0';
		nptr++;
	}
	return (sign * (int)num);
}

int	ft_isdigit(int c)
{
	return (c <= '9' && '0' <= c);
}

int	ft_isspace(int c)
{
	return ((c > 8 && c < 14) || c == 32);
}

size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*(p++))
		;
	return (p - 1 - s);
}
