#ifndef MINICLIENT_H
# define MINICLIENT_H

# include "minitalk.h"

void	mini_request(int ac, char **av);
void	handle_args(int ac, char **av);
void	send_string(int pid, char *str);
void	send_char(int pid, unsigned char c);
void	send_strlen(int pid, char *str);

int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
int		ft_isspace(int c);
size_t	ft_strlen(const char *str);

#endif /* MINICLIENT_H */
