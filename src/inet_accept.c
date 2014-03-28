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

t_net	*accept_connection(int sockfd)
{
  t_net	*res;

  if ((res = malloc(1 * sizeof(t_net))) == NULL)
    return (NULL);
  res->addrlen = sizeof(struct sockaddr_storage);
  res->socket = accept(sockfd, (struct sockaddr*)(&(res->addr)),
                       &(res->addrlen));
  if (res->socket == -1)
    {
      perror("accept");
      free(res);
      return (NULL);
    }
  return (res);
}
