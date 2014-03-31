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

void	handle_clients(t_net *client)
{
  char	buff[128];
  int	t;

  write(client->socket, "Send your stuff\n", sizeof("Send your stuff\n"));
  while ((t = read(client->socket, buff, 128)) > 0)
    {
      write(client->socket, buff, t);
    }
}
