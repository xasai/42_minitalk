#include "miniclient.h"

void	mini_request(int ac, char **av)
{
	int	i;
	int	pid;

	i = 1;
	pid = ft_atoi(av[1]);
	while (++i < ac)
		send_string(pid, av[i]);
}

void	send_string(int pid, char *str)
{
	size_t	i;
	size_t	mask;
	int		signum;

	i = 0;
	while (str[i])
	{
		mask = 0x01;
		while (mask != 0x80)
		{
			signum = SIGUSR2;
			if (mask & str[i])	
				signum = SIGUSR1;
			kill(pid, signum);
			mask = (mask << 1);
		}
		i++;
	}
}
