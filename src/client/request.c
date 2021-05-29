#include "miniclient.h"

void	mini_request(int ac, char **av)
{
	int	i;
	int	pid;

	i = 1;
	pid = ft_atoi(av[1]);
	while (++i < ac)
	{
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
	int				signum;

	mask = 0x01;
	while (mask != 0x80)
	{
		signum = SIGUSR2;
		if (mask & c)
			signum = SIGUSR1;
		kill(pid, signum);
		mask = (mask << 1);
		usleep(1000);
	}
}
