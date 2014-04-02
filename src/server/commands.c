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

void	cd(t_fclient *client, char **args)
{
  if (ptr_tab_size((void**)args) != 2)
    write_sock("cd require 1 argument\n", client->net->socket, -1);
  else if (is_path_out(client->basedir, args[1]))
    write_sock("cd: Invalid path\n", client->net->socket, -1);
  else if (!(cd_base(&(args[1]), client->net->socket)))
    {
      free(client->currdir);
      client->currdir = get_pwd();

    }
}
