#include "miniclient.h"

static sig_atomic_t	g_ack;

/* receiving ack via signal handler _ack */
static void	_ack(int signum)
{
	g_ack = true;
	(void)signum;
}

/* establishing sigaction for ack packer */
static void	_set_sigaction(int signum)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = _ack;
	sigaction(signum, &sa, NULL);
}

/*here we send signal and waiting for acknoledgment from server*/
void	kill_wrapper(int pid, int signal)
{
	int		sleep_time;
	int		max_sleep;

	sleep_time = 0;
	max_sleep = 10;
	if (kill(pid, signal) == -1)
		 _exit_error("ERROR: Can't send data to server.\n");
	while (g_ack != true)
	{
		if (max_sleep > 10000)
			_exit_error("ERROR: Timeout!\n");
		else if (sleep_time > max_sleep)
		{
			max_sleep += 10;
			if (kill(pid, signal) == -1)
				 _exit_error("ERROR: Can't send data to server.\n");
		}
		else
			usleep(100);
		sleep_time += 1;
	}
	g_ack = false;
}

void	mini_request(char **av)
{
	int		len;
	int		server_pid;
	int		cli_pid;
	char	*str;

	g_ack = false;
	str = av[2];
	len = ft_strlen(str);
	server_pid = ft_atoi(av[1]);
	cli_pid = getpid();
	_set_sigaction(SIGUSR1);
	send_pid(server_pid, cli_pid);
	send_int(server_pid, len);
	send_string(server_pid, str);
	send_char(server_pid, EOT);
	putstr_fd("String successfully send to server!");
}
