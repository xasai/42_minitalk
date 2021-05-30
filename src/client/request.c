#include "miniclient.h"

void	mini_request(int ac, char **av)
{
	int	i;
	int	pid;

	i = 1;
	pid = ft_atoi(av[1]);
	while (++i < ac)
	{
		send_strlen(pid, av[i]);
		send_string(pid, av[i]);
	}
}

void	send_string(int pid, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, '\0');
}

void	send_char(int pid, unsigned char c)
{
	unsigned char	mask;

	mask = 0x01;
	while (mask != 0x80)
	{
		if (mask & c)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		mask = (mask << 1);
		usleep(100);
	}
	usleep(500);
}

void	send_strlen(int pid, char *str)
{
	unsigned short	len;
	unsigned short	mask; 

	len = ft_strlen(str);
	mask = 0x0001;
	while (mask & 0xffff)
	{
		if (mask & len)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		mask = (mask << 1);
		usleep(100);
	}
}
