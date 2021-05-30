#ifndef MINISERVER_H
# define MINISERVER_H

# include "minitalk.h"

int		run_server(void);
void	set_catcher(void (*sig_catcher)(int));
void	len_catcher(int signum);
void	char_catcher(int signum);

/*	auxillary.c */
void	putchar_fd(char c, int fd);
void	putnbr_fd(int n, int fd);
void	putstr_fd(char *str, int fd);
size_t	ft_strlen(const char *str);

#endif /* MINISERVER_H */
