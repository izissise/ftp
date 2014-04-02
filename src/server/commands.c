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

void	noop(t_fclient *client, UNSEDP char **args)
{
  char	buff[READ_SIZE];

  snprintf(buff, READ_SIZE, "%s\n", "200 NOOP ok.");
  write_sock(buff, client->net->socket, -1);
}

void	list(t_fclient *client, char **args)
{
  ls_base(&(args[1]), client->net->socket);
}
