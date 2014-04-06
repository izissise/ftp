/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "server.h"

t_net		*create_passive_connection(t_fclient *client)
{
  t_net		*res;
  struct sockaddr	*addr;

  addr = &(client->net->addr);
  if ((res = create_connection(listening_ip((addr->sa_family_t),
                               NULL, &bind))) == NULL)
    return (NULL);
  return (res);
}

