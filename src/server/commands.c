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

void	noop(t_fclient *client, UNSEDP char *arg)
{
  char	buff[BUFSIZ];

  snprintf(buff, sizeof(buff), "%s\n", "200 NOOP ok.");
  write_sock(buff, client->net->socket, -1);
}

void	list(t_fclient *client, char *arg)
{
  char	*tmp[2];

  tmp[0] = arg;
  if (client->pasv == NULL)
    {
      write_sock("425 Use EPSV first.\n", client->net->socket, - 1);
      return ;
    }
  accept_passive_connection(client);
  write_sock("150 Here comes the directory listing.\n",
             client->net->socket, -1);
  if (strlen(arg) && !switch_paths(client->basedir, &(tmp[0])))
    write_sock("ls: No such file or directory\n", client->pasv->socket, -1);
  else
    {
      if (arg[0] == '\0')
        tmp[0] = NULL;
      tmp[1] = NULL;
      ls_base(tmp, client->pasv->socket);
      if (tmp[0] != arg)
        free(tmp[0]);
    }
  close_connection(client->pasv);
  client->pasv = NULL;
  write_sock("226 Directory send OK.\n", client->net->socket, -1);
}

void	cd(t_fclient *client, char *arg)
{
  char	*tmp[2];

  tmp[0] = arg;
  tmp[1] = NULL;
  if (arg[0] == '\0')
    write_sock("cd require one argument\n", client->net->socket, -1);
  else if (!switch_paths(client->basedir, &(tmp[0])))
    write_sock("cd: No such file or directory\n", client->net->socket, -1);
  else if (!(cd_base(tmp, client->basedir, client->net->socket)))
    {
      free(client->currdir);
      client->currdir = get_pwd();
      free(tmp[0]);
      write_sock("250 Directory successfully changed.\n",
                 client->net->socket, -1);
    }
}

void	pwd(t_fclient *client, UNSEDP char *arg)
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

void	quit(t_fclient *client, UNSEDP char *arg)
{
  client->quit = 1;
  write_sock("221 Goodbye.\n", client->net->socket, -1);
}
