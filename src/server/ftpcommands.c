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

void	epsv(t_fclient *client, UNSEDP char *arg)
{
  char	*info;
  char	buff[BUFSIZ];

  if (((client->pasv = create_passive_connection()) == NULL)
      || (info = calculate_epsvconnection_info(client->pasv)) == NULL)
    {
      write_sock("500 Can't create epsv.\n", client->net->socket, - 1);
      close_connection(client->pasv);
      client->pasv = NULL;
      return ;
    }
  snprintf(buff, sizeof(buff), "229 Entering Extended Passive Mode (%s).\n",
           info);
  free(info);
  write_sock(buff, client->net->socket, - 1);
}

void	pasv(t_fclient *client, UNSEDP char *arg)
{
  char	*info;
  char	buff[BUFSIZ];

  if (client->pasv)
    close_connection(client->pasv);
  if (((client->pasv = create_passive_connection()) == NULL)
      || (info = calculate_pasvconnection_info(client->pasv)) == NULL)
    {
      write_sock("500 Can't create pasv.\n", client->net->socket, - 1);
      close_connection(client->pasv);
      client->pasv = NULL;
      return ;
    }
  snprintf(buff, sizeof(buff), "227 Entering Passive Mode (%s).\n",
           info);
  free(info);
  write_sock(buff, client->net->socket, - 1);
}

void	type(t_fclient *client, char *arg)
{
  if (!strcmp(arg, "I") || !strcmp(arg, "A"))
    {
      client->bin = (!strcmp(arg, "I")) ? 1 : 0;
      write_sock("200 Switching to mode.\n", client->net->socket, -1);
    }
  else
    write_sock("500 Unrecognized TYPE command.\n", client->net->socket, -1);
}

void	retr(t_fclient *client, char *arg)
{
  char	*file;

  file = arg;
  if (client->pasv == NULL)
    {
      write_sock("425 Use EPSV first.\n", client->net->socket, - 1);
      return ;
    }
  accept_passive_connection(client);
  if (strlen(arg) && !switch_paths(client->basedir, &(file), 0))
    write_sock("550 Failed to open file.\n", client->net->socket, -1);
  else
    {
      write_sock("150 Transferring file.\n", client->net->socket, -1);
      send_file(client->pasv, file);
      if (file != arg)
        free(file);
      close_connection(client->pasv);
      client->pasv = NULL;
      write_sock("226 Transfer complete.\n", client->net->socket, -1);
    }
}

void	stor(t_fclient *client, char *arg)
{
  char	*file;

  file = arg;
  if (client->pasv == NULL)
    {
      write_sock("425 Use EPSV first.\n", client->net->socket, - 1);
      return ;
    }
  accept_passive_connection(client);
  if (strlen(arg) && !switch_paths(client->basedir, &(file), 1))
    write_sock("550 Permission denied.\n", client->net->socket, -1);
  else
    {
      write_sock("150 Transferring file.\n", client->net->socket, -1);
      recv_file(client->pasv, file);
      if (file != arg)
        free(file);
      close_connection(client->pasv);
      client->pasv = NULL;
      write_sock("226 Transfer complete.\n", client->net->socket, -1);
    }
}
