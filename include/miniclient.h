#ifndef MINICLIENT_H
# define MINICLIENT_H

# include "minitalk.h"

/*	main.c		*/
void	_exit_error(const char *message);

/*	request.c	*/

void	kill_wrapper(int pid, int signal);
void	mini_request(char **av);

/*	send_data	*/
void	send_string(int pid, char *str);
void	send_char(int pid, char c);
void	send_int(int pid, int num);
void	send_pid(int pid, int mypid);

/*	auxillary.c	*/
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
int		ft_isspace(int c);
size_t	ft_strlen(const char *str);
void	putstr_fd(const char *str, int fd);

#endif /* MINICLIENT_H */
