/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef NETWORK_H_INCLUDED
# define NETWORK_H_INCLUDED

# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

# define UNSEDP __attribute__((unused))
# define PTRT_PACK 10
# define MAX_CLIENTS 50

typedef struct			s_net
{
  struct sockaddr_storage	addr;
  socklen_t			addrlen;
  int				socket;
  int				socktype;
}				t_net;

t_net		*create_connection(const char *host, const char *port,
                           int socktype, int	(*f)(int sockfd,
                               const struct sockaddr *addr,
                               socklen_t addrlen));
void		close_connection(t_net *net);
t_net	*accept_connection(int sockfd);
void		*get_ip_addr(t_net *net);

int	ptr_tab_size(void **tab);
void	**add_ptr_t_tab(void **tab, void *add);
void	rm_ptr_f_tab(void **tab, void *ptr);
void	free_ptr_tab(void **tab, void	(*f)(void *ptr));

#endif /* !NETWORK_H_INCLUDED */
