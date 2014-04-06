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

char	*calculate_pasvconnection_info(char *addr, int port)
{
  char	*tmp;
  int	i;
  int	len;

  i = 0;
  len = (strlen(addr) + 12);
  if ((tmp = malloc(len * sizeof(char))) == NULL)
    return (NULL);
  while (addr[i])
    {
      if (addr[i] == '.')
        tmp[i] = ',';
      else
        tmp[i] = addr[i];
      i++;
    }
  snprintf(&(tmp[i]), len - i, ",%d,%d", port / 256, port % 256);
  return (tmp);
}

t_net		*create_passive_connection(t_fclient *client)
{
  t_net		*res;
  struct sockaddr	*addr;

  addr = (struct sockaddr*)(&(client->net->addr));
  if ((res = create_connection(listening_ip(addr->sa_family),
                               NULL, SOCK_STREAM, &bind)) == NULL)
    return (NULL);
  return (res);
}
