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

void	pasv(t_fclient *client, UNSEDP char **args)
{
  char	*ip;
  int	port;
  char	*info;
  char	buff[READ_SIZE];

  client->pasv = create_passive_connection(client);
  ip = get_ip_addr(client->pasv);
  port = port_number(client->pasv);
  if ((port == -1) || (ip == NULL))
    {
      close_connection(client->pasv);
      client->pasv = NULL;
      return ;
    }
  info = calculate_pasvconnection_info(ip, port);
  if (info == NULL)
    {
      close_connection(client->pasv);
      client->pasv = NULL;
      return ;
    }
  snprintf(buff, sizeof(buff), "227 Entering Passive Mode (%s)", info);
  free(ip);
  free(info);
  write_sock(buff, client->net->socket, - 1);
}

void	get(t_fclient *client, UNSEDP char **args)
{
}
