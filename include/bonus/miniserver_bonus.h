#ifndef MINISERVER_BONUS_H
# define MINISERVER_BONUS_H

# include "minitalk_bonus.h"

typedef struct s_data
{
	bool		stage_pid;
	bool		stage_len;	
	bool		stage_str;
	int			client_pid;
	char		*str;
}				t_data;

/*	main.c		*/
void	_exit_error(char *message);
void	_send_ack(int pid);

/*	server.c	*/
void	run_server(void);

/*	auxillary.c */
void	putchar_fd(char c, int fd);
void	putnbr_fd(int n, int fd);
void	putstr_fd(char *str, int fd);
size_t	ft_strlen(const char *str);

#endif /* MINISERVER_BONUS_H */
