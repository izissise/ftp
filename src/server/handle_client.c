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

static t_strfunc	cmds[] = {
  {"LIST", &list},
  {"CWD", &cd},
  {"GET", &noop},
  {"PUT", &noop},
  {"PWD", &noop},
  {"QUIT", &noop},
  {"USER", &noop},
  {"PASS", &noop},
  {"NOOP", &noop}
};

void	unknow_cmd(t_fclient *client, char **args)
{
  char	buff[READ_SIZE];

  snprintf(buff, READ_SIZE, "%s: unknow commands\n", args[0]);
  write_sock(buff, client->net->socket, -1);
}

void	(*client_commands(char *command))()
{
  int	i;

  i = 0;
  while (i < (int)(sizeof(cmds) / sizeof(t_strfunc)))
    {
      if (!(strncasecmp((cmds[i]).str, command, strlen((cmds[i]).str))))
        return ((cmds[i]).func);
      i++;
    }
  return (&unknow_cmd);
}

void	handle_clients(t_fclient *client)
{
  char	*line;
  char	**args;

  write_sock("Welcome !\nType HELP for help.\n", client->net->socket, -1);
  while ((line = get_next_line(client->net->socket)) && !(client->quit))
    {
      if ((args = str_wt(line, " ")))
        (client_commands(args[0]))(client, args);
      free(line);
    }
}
