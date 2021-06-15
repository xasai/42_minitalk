#include "miniserver.h"

size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*(p++))
		;
	return (p - 1 - s);
}

inline void	putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		putchar_fd('-', fd);
		n *= -1;
	}
	if (n < 10 && n >= 0)
	{
		putchar_fd(n + '0', fd);
		return ;
	}
	putnbr_fd(n / 10, fd);
	putnbr_fd(n % 10, fd);
}

inline void	putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
