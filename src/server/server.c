#include "miniserver.h"

static char *str;

/*
** DESCRIPTION:
**	This function output program's PID to STDOUT.
**	Set the first signal handler.
*/
int	run_server(void)
{
	pid_t	pid;

	pid = getpid();
	putnbr_fd(pid, STDOUT_FILENO);
	putchar_fd('\n', STDOUT_FILENO);
	set_catcher(len_catcher);
	while (1)
	{
		pause();
	}
	return (EXIT_SUCCESS);
}

/*
** DESCRIPTION:
**	This function collect bits one by one and store it
**	in global str variable.
**	When '\0' received, string is outputed to STDOUT 
*/
void	char_catcher(int signum)
{
	static unsigned char	chr;
	static unsigned char	mask = 0x01;
	static size_t		i;	

	if (signum == SIGUSR1)
		chr |= mask;
	mask = mask << 1;
	//printf("%#4x\n", mask);
	if (mask == 0x80)
	{
		mask = 0x01;
		str[i] = chr;
	//	printf("chr - %c | i = %ld\n", chr, i);
		if (chr == '\0')
		{
			putstr_fd(str, STDOUT_FILENO);
			putchar_fd('\n', STDOUT_FILENO);
			free(str);
			str = NULL;
			set_catcher(len_catcher);
			i = 0;
		}
		else
			i++;
		chr = '\0';	
	}
}

/*
** DESCRIPTION:
**	This function collect bits one by one and store it
**	in short int variable and then allocate + 1 byte.
*/
void	len_catcher(int signum)
{
	static unsigned short int	size;
	static unsigned int			mask = 0x0001;

	if (signum == SIGUSR1)
		size |= mask;
	mask = mask << 1;
	if (mask & 0x10000)
	{
		printf("len is %hd\n",size);
		str = malloc(sizeof(*str) * (size + 1));
		if (!str)
			exit(EXIT_FAILURE);
		set_catcher(char_catcher);
		mask = 0x0001;
		size = 0;
	}
}

/*
** DESCRIPTION:
**	This function set 1 handler for SIGUSR1 & SIGUSR2 signals.
*/
void	set_catcher(void (*sig_catcher)(int))
{
	static struct sigaction	sigact;

	if (sigemptyset(&sigact.sa_mask) < 0)
		exit(1);
//	if (sigaddset(&sigact.sa_mask, SIGUSR1) < 0
//		|| sigaddset(&sigact.sa_mask, SIGUSR2) < 0)
//		exit(1);
	sigact.sa_handler = sig_catcher;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
}
