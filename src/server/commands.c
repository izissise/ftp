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
  char	buff[BUFSIZ];

  snprintf(buff, sizeof(buff), "%s\n", "200 NOOP ok.");
  write_sock(buff, client->net->socket, -1);
}

void	list(t_fclient *client, char **args)
{
  if (client->pasv == NULL)
    {
      write_sock("425 Use EPSV first.\n", client->net->socket, - 1);
      return ;
    }
  accept_passive_connection(client);
  write_sock("150 Here comes the directory listing.\n",
             client->net->socket, -1);
  if (args[1] != NULL && !switch_paths(client->basedir, &(args[1])))
    write_sock("ls: No such file or directory\n", client->pasv->socket, -1);
  else
    ls_base(&(args[1]), client->pasv->socket);
  close_connection(client->pasv);
  client->pasv = NULL;
  write_sock("226 Directory send OK.\n", client->net->socket, -1);
}

void	cd(t_fclient *client, char **args)
{
  if (ptr_tab_size((void**)args) != 2)
    write_sock("cd require one argument\n", client->net->socket, -1);
  else if (!switch_paths(client->basedir, &(args[1])))
    write_sock("cd: No such file or directory\n", client->net->socket, -1);
  else if (!(cd_base(&(args[1]), client->basedir, client->net->socket)))
    {
      free(client->currdir);
      client->currdir = get_pwd();
    }
}

void	pwd(t_fclient *client, UNSEDP char **args)
{
  char	*tmp;
  char	buff[BUFSIZ];
  int	i;

  i = 0;
  if (!(tmp = get_pwd()))
    return ;
  while ((tmp[i] == client->basedir[i]) && tmp[i])
    ++i;
  snprintf(buff, sizeof(buff), "257 \"/%s\"\n", &(tmp[i + (tmp[i] == '/')]));
  write_sock(buff, client->net->socket, -1);
  free(tmp);
}

void	quit(t_fclient *client, UNSEDP char **args)
{
  client->quit = 1;
  write_sock("221 Goodbye.\n", client->net->socket, -1);
}
