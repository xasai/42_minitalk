#include "miniserver.h"

int	run_server(void)
{
	pid_t	pid;

	pid = getpid();
	putnbr_fd(pid, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
