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
  {"LS", &noop},
  {"CD", &noop},
  {"GET", &noop},
  {"PUT", &noop},
  {"PWD", &noop},
  {"QUIT", &noop},
  {"USER", &noop},
  {"PASS", &noop}
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

void	handle_clients(t_fclient *client)
{
  char	*line;
  char	**args;
  int i;

  write(client->net->socket, "Send your stuff\n", sizeof("Send your stuff\n"));
  while ((line = get_next_line(client->net->socket)) && !(client->quit))
    {
      args = str_wt(line, " ");
      if (args)
        for (i = 0; args[i]; i++)
          {
            printf("%s\n", args[i]);
          }
      //client_commands(client, line);
      free(line);
    }
}
