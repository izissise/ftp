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

char	*calculate_pasvconnection_info(t_net *net)
{
  char	*tmp;
  int	i;
  int	len;
  char	*ip;
  int	port;

  i = 0;
  tmp = NULL;
  ip = NULL;
  if ((port = port_number(net)) || (ip = get_ip_addr(net))
      || !(len = (strlen(ip) + 12))
      || ((tmp = malloc(len * sizeof(char))) == NULL))
    {
      free(tmp);
      free(ip);
      return (NULL);
    }
  while (ip[i])
    {
      tmp[i] = (ip[i] == '.') ? ',' : ip[i];
      i++;
    }
  snprintf(&(tmp[i]), len - i, ",%d,%d", port / 256, port % 256);
  free(ip);
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

