#include "miniserver.h"

void	_send_ack(int pid)
{
	if (kill(pid, SIGUSR1) < 0)
		_exit_error("Error while sending ack signal to client\n");
}

void	_exit_error(char *message)
{
	if (message != NULL)
		write(STDERR_FILENO, message, ft_strlen(message));
	exit(EXIT_FAILURE);
}

int	main(void)
{
	run_server();
	return (EXIT_SUCCESS);
}
