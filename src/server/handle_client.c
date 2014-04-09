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
  {"NOOP", &noop},
  {"LIST", &list},
  {"CWD", &cd},
  {"PWD", &pwd},
  {"QUIT", &quit},
  {"PASV", &pasv},
  {"EPSV", &epsv},
  {"SPSV", &epsv},
  {"TYPE", &type},
  {"GET", &get},
  {"PUT", &put},
  {"USER", &user},
  {"PASS", &pass}
};

void	unknow_cmd(t_fclient *client, char *arg)
{
  char	buff[BUFSIZ];

  if (client->logged)
    snprintf(buff, sizeof(buff), "500 %s: unknow commands\n", arg);
  else
    snprintf(buff, sizeof(buff), "530 Please login with USER and PASS.\n");
  write_sock(buff, client->net->socket, -1);
}

void	handle_clients(t_fclient *client)
{
  char	*line;
  char	*arg;
  void	(*f)();

  write_sock("220 Welcome ! Type HELP for help.\n", client->net->socket, -1);
  while (!(client->quit) && (line = get_next_line(client->net->socket)))
    {
      arg = strdup(find_arguments(line));
      if (strlen(line))
        {
          f = client_commands(line, cmds, (sizeof(cmds) / sizeof(t_strfunc)));
          if (f && (client->logged || ((f == &user) || (f == &quit)
                                       || (f == &pass) || (f == &unknow_cmd))))
            f(client, arg);
          else
            unknow_cmd(client, arg);
        }
      free(arg);
      free(line);
    }
  if (client->pasv)
    close_connection(client->pasv);
}
