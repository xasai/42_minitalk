#include "miniclient.h"

static void	_handle_args(int ac, char **av)
{
	int			i;
	const char	usage[] = "client: Usage: client <pid> <str1>\n";
	const char	eot_error[] = "client: String can't contain EOT char\n";

	i = 0;
	if (ac != 3)
		_exit_error(usage);
	while (ft_isspace(av[1][i]))
		i++;
	while (ft_isdigit(av[1][i]))
		i++;
	while (ft_isspace(av[1][i]))
		i++;
	if (av[1][i])
		_exit_error(usage);
	i = 0;
	while (av[2][i])
		if (av[2][i++] == EOT)
			_exit_error(eot_error);
}

void	_exit_error(const char *message)
{
	if (message != NULL)
		write(STDERR_FILENO, message, ft_strlen(message));
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	_handle_args(ac, av);
	mini_request(av);
	return (EXIT_SUCCESS);
}
