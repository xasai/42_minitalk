#include "miniserver.h"

static t_data	g_data;

/*
** DESCRIPTION:
**	This function collect bits one by one and store it
**	in g_data.str.
**	When EOT received, string is outputed to STDOUT.
**	Setting stage_pid in g_data structure.
*/
static void	str_catcher(int signum)
{
	static size_t			i;
	static unsigned char	mask = 1;
	static unsigned char	chr;

	_send_ack(g_data.client_pid);
	if (signum == SIGUSR1)
	{
		chr |= mask;
		//write(1, "1", 1);
	}
//	else
//		write(1, "0", 1);
	mask = mask << 1;
	if (mask == 0x80)
	{
	//	putchar_fd(chr, 1);
		g_data.str[i] = chr;
		if (g_data.str[i] == EOT)
		{
			g_data.str[i] = '\0';
			putstr_fd(g_data.str, STDOUT_FILENO);
			free(g_data.str);
			g_data = (t_data){0};
			g_data.stage_pid = true;
			i = -1;
		}
		chr = 0;
		mask = 1;
		i++;
	}
}

/*
** DESCRIPTION:
**	This function collect bits one by one and store it
**	in size variable.
**	When its fully stored, allocate string g_data.str.
**
**	Sending SIGUSR1 to g_data.client_pid as acknowledgment.
*/
static void	len_catcher(int signum)
{
	static long long int mask = 1;
	static size_t		 size = 0;

	
	_send_ack(g_data.client_pid);
	if (signum == SIGUSR1)
		size |= mask;
	mask = mask << 1;
//	if (g_data.stage_str == true)
//	{
//		write(1, "HERE\n", 6);
//	}
	if (mask & 0x100000000)
	{
//		printf("SIZE = %ld\n", size);
		g_data.str = malloc(sizeof(*g_data.str) * (size + 1));
		if (!g_data.str)
			exit(EXIT_FAILURE);
		mask = 1;
		size = 0;
		g_data.stage_str = true;

	}
}

static void	pid_catcher(int signum)
{
	static unsigned int	mask = 1;

	if (signum == SIGUSR1)
		g_data.client_pid |= mask;
	mask = mask << 1;
	if (mask == 0x80000000)
	{
		mask = 1;
		g_data.stage_len = true;
	}
}

/*
** DESCRIPTION:
**	This function set 1 same handler for SIGUSR1 & SIGUSR2 signals.
*/
static void	set_catcher(void (*sig_catcher)(int))
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_handler = sig_catcher;
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) < 0
		|| sigaction(SIGUSR2, &sa, NULL) < 0)
		_exit_error("Error establishing signal handler\n");
}

/*
** DESCRIPTION:
**	This function output program's PID to STDOUT.
**	Reset catcher in this sequence:
**		pid -> len -> str -> pid ...
*/
void	run_server(void)
{
	pid_t	pid;

	pid = getpid();
	putnbr_fd(pid, STDOUT_FILENO);
	g_data = (t_data){.stage_pid = true, 0};
	while (true)
	{
		if (g_data.stage_pid == true)
		{
			set_catcher(pid_catcher);
//			write(1, "stage 1\n", 8);
			g_data.stage_pid = false;
			putchar_fd('\n', STDOUT_FILENO);
		}
		else if (g_data.stage_len == true)
		{
			set_catcher(len_catcher);
//			write(1, "stage 2\n", 8);
			g_data.stage_len = false;
		}
		else if (g_data.stage_str == true)
		{
			set_catcher(str_catcher);
//			write(1, "stage 3\n", 8);
			g_data.stage_str = false;
		}
		usleep(1);
	}
}
