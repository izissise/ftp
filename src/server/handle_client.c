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

void noop(t_fclient *client)
{
  (void)client;
}

static t_strfunc	cmds[] = {
  {"ls", &noop},
  {"cd", &noop},
  {"get", &noop},
  {"put", &noop},
  {"pwd", &noop},
  {"quit", &noop}
};

void	client_commands(t_fclient *client, char *command)
{
  int	i;

  i = 0;
  while (i < (int)(sizeof(cmds) / sizeof(char*)))
    {
      if (!strcmp((cmds[i]).str, command))
        ((cmds[i]).func)(client);
      i++;
    }
}

void	handle_clients(t_fclient * client)
{
  char	buff[128];
  int	t;

  write(client->net->socket, "Send your stuff\n", sizeof("Send your stuff\n"));
  while (((t = read(client->net->socket, buff, 128)) > 0) && !(client->quit))
    {
      client_commands(client, "put");
      write(client->net->socket, buff, t);
    }
  if (t == -1)
    perror("client");
}
