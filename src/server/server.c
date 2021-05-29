#include "miniserver.h"

#include <signal.h>

int	run_server(void)
{
	pid_t				pid;

	pid = getpid();
	putnbr_fd(pid, STDOUT_FILENO);
	while (1)
	{
		set_catcher();
		pause();
	}
	return (EXIT_SUCCESS);
}

void	sig_catcher(int signum)
{
	static unsigned char chr;
	static unsigned char mask = 0x01;

	if (signum == SIGUSR1)
		chr |= mask;
	mask = mask << 1;
	if (mask == 0x80)
	{
		mask = 0x01;
		if (!chr)
			putchar_fd('\n', STDOUT_FILENO);
		else 
			putchar_fd(chr, STDOUT_FILENO);
		chr = '\0';
	}
}

void	set_catcher(void)
{
	static struct sigaction	sigact;

	if (sigemptyset(&sigact.sa_mask) < 0)
		exit(1);
	sigact.sa_handler = &sig_catcher;
	sigaction(SIGUSR1, &sigact, NULL);	
	sigaction(SIGUSR2, &sigact, NULL);	
}
