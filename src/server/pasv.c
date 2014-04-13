/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Thu Apr 10 21:10:26 2014 Hugues
*/

#include <stdio.h>

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
  ip = SERVERIP;
  if (!(port = port_number(net))
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
  return (tmp);
}

char	*calculate_epsvconnection_info(t_net *net)
{
  int	port;
  char	buff[BUFSIZ];

  if ((port = port_number(net)) == 0)
    return (NULL);
  snprintf(buff, sizeof(buff), "|||%d|", port);
  return (strdup(buff));
}

t_net			*create_passive_connection()
{
  t_net			*res;

  if ((res = create_connection(listening_ip(SERVERTYPE),
                               NULL, SOCK_STREAM, &bind)) == NULL)
    return (NULL);
  if (listen(res->socket, 1) == -1)
    {
      perror("listen");
      close_connection(res);
      res = NULL;
    }
  return (res);
}

void	accept_passive_connection(t_fclient *client)
{
  t_net	*tmp;

  if ((client->pasv == NULL)
      || (tmp = accept_connection(client->pasv->socket)) == NULL)
    {
      close_connection(client->pasv);
      client->pasv = NULL;
      return ;
    }
  close_connection(client->pasv);
  client->pasv = tmp;
}
