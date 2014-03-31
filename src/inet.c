/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "network.h"

void		*get_ip_addr(t_net *net)
{
  struct sockaddr	*sa;

  if (!net)
    return (NULL);
  sa = (struct sockaddr*)(&(net->addr));
  if (sa->sa_family == AF_INET)
    return (&(((struct sockaddr_in*)sa)->sin_addr));
  else if (sa->sa_family == AF_INET6)
    return (&(((struct sockaddr_in6*)sa)->sin6_addr));
  return (NULL);
}

int		use_ipsocket(t_net *net, struct addrinfo *tmp,
                   int	(*f)(int sockfd, const struct sockaddr *addr,
                            socklen_t addrlen))
{
  int		ret;
  memcpy(&(net->addr), tmp->ai_addr, tmp->ai_addrlen);
  net->addr.ss_family = tmp->ai_addr->sa_family;
  net->socktype = tmp->ai_socktype;
  net->addrlen = tmp->ai_addrlen;
  ret = f(net->socket, (struct sockaddr*)(&(net->addr)), net->addrlen);
  if (ret == -1)
    close(net->socket);
  return (ret);
}

int				ipaddress_init(const char *ip, const char *port,
                         t_net *net, int	(*f)(int sockfd,
                             const struct sockaddr *addr,
                             socklen_t addrlen))
{
  struct addrinfo	req;
  struct addrinfo	*res;
  struct addrinfo	*tmp;
  int			ret;

  memset(&req, 0, sizeof(struct addrinfo));
  req.ai_family = AF_UNSPEC;
  req.ai_socktype = net->socktype;
  req.ai_flags = AI_PASSIVE | AI_NUMERICSERV | AI_ADDRCONFIG;
  if ((ret = getaddrinfo(ip, port, &req, &res)))
    return (ret);
  tmp = res;
  while (tmp)
    {
      net->socket = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
      if (!((net->socket == -1) || ((ret = use_ipsocket(net, tmp, f)) == -1)))
        break;
      tmp = tmp->ai_next;
    }
  freeaddrinfo(res);
  return (ret);
}

t_net		*create_connection(const char *host, const char *port,
                           int socktype, int	(*f)(int sockfd,
                               const struct sockaddr *addr,
                               socklen_t addrlen))
{
  t_net		*res;
  int		err;

  if ((res = malloc(1 * sizeof(t_net))) == NULL)
    return (NULL);
  res->socktype = socktype;
  if ((err = ipaddress_init(host, port, res, f)))
    {
      if (err > 0)
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
      else
        perror("ipadress_init");
      free(res);
      return (NULL);
    }
  return (res);
}

void		close_connection(t_net *net)
{
  if (net && close(net->socket) == -1)
    perror("close");
  free(net);
}