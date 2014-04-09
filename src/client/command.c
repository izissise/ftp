/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "client.h"

static t_strfunc	cmds[] = {
  {"LIST", &list},
  {"LS", &list},
  {"CWD", &cd},
  {"CD", &cd},
  {"PWD", &pwd},
  {"GET", &get},
  {"PUT", &put},
  {"USER", &user},
  {"PASS", &pass}
};

void	do_commands(t_cstate *state, char *line)
{
  char	*arg;
  void	(*f)();

  arg = strdup(find_arguments(line));
  if (strlen(line))
    {

    }
  free(arg);
//  snprintf(buff, sizeof(buff), "%s\n", line);
//  write_sock(buff, state->net->socket, -1);
}
