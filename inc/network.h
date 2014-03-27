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
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

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

#endif // NETWORK_H_INCLUDED
