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
  char	*info;
  char	buff[BUFSIZ];

  if (((client->pasv = create_passive_connection(client)) == NULL)
      || (info = calculate_epsvconnection_info(client->pasv)) == NULL)
    {
      write_sock("Can't create epsv connection.\n", client->net->socket, - 1);
      close_connection(client->pasv);
      client->pasv = NULL;
      return ;
    }
  snprintf(buff, sizeof(buff), "229 Entering Extended Passive Mode (%s).\n",
           info);
  free(info);
  write_sock(buff, client->net->socket, - 1);
}

void	get(t_fclient *client, UNSEDP char **args)
{
}
