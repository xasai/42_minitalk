#include "miniclient.h"

void	handle_args(int ac, char **av)
{
	int			i;
	const char	usage[] = "client: Usage: client <pid> str1 str2 ...\n";

	i = 0;
	if (ac < 3)
	{
		write(STDOUT_FILENO, usage, sizeof(usage));
		exit(EXIT_FAILURE);
	}
	while (ft_isspace(av[1][i]) || ft_isdigit(av[1][i]))
		i++;
	if (av[1][i])
	{
		write(STDOUT_FILENO, usage, sizeof(usage));
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av)
{
	handle_args(ac, av);
	mini_request(ac, av);
	return (EXIT_SUCCESS);
}
