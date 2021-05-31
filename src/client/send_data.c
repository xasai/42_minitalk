#include "miniclient.h"


void	send_string(int pid, char *str)
{
	size_t	i;

	i = 0; while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
}

void	send_char(int pid, char c)
{
	unsigned char	mask;
	int				signal;

	mask = 1;
	while (mask != 0x80)
	{
		if (mask & c)
			signal = SIGUSR1;
		else
			signal = SIGUSR2;
		mask = (mask << 1);
		kill_wrapper(pid, signal);
	}
}

void	send_int(int pid, int num)
{
	long long int	mask;
	int				signal;

	mask = 1;
	while (mask != 0x100000000)
	{
		if (mask & num)
			signal = SIGUSR1;
		else
			signal = SIGUSR2;
		mask = (mask << 1);
		kill_wrapper(pid, signal);
	}
}

void	send_pid(int pid, int mypid)
{
	unsigned int	mask;
	int				signal;

	mask = 1;
	while (mask != 0x80000000)
	{
		if (mask & mypid)
			signal = SIGUSR1;
		else
			signal = SIGUSR2;
		mask = mask << 1;
		if (kill(pid, signal) < 0)
			_exit_error("Signal sending Error\n");
		usleep(10000);
	}
}
