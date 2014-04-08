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

void	user(t_fclient *client, char *arg)
{
  if (arg[0] == '\0')
    write_sock("530 Permission denied.\n", client->net->socket, -1);
  else
    {
      if (client->user)
        free(client->user);
      client->user = strdup(arg);
      write_sock("331 Specify the password.\n", client->net->socket, -1);
    }
}

void	pass(t_fclient *client, char *arg)
{
  int	ok;

  ok = 0;
  if (client->user)
    {
      if (!strcmp(client->user, "ftp") && !strcmp(arg, "ftp"))
        ok = 1;
      if (ok)
        {
          client->logged = 1;
          write_sock("230 Login successful.\n", client->net->socket, -1);
        }
      else
        write_sock("530 Permission denied.\n", client->net->socket, -1);
    }
  else
    write_sock("503 Login with USER first.\n", client->net->socket, -1);
}
