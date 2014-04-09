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
  {"LLS", &lls},
  {"LCD", &lcd},
  {"LPWD", &lpwd},
  {"LS", &list},
  {"LIST", &list},
  {"CD", &cd},
  {"GET", &get},
  {"PUT", &put}
};

void	do_commands(t_cstate *state, char *line)
{
  char	*arg;
  char	buff[BUFSIZ];
  void	(*f)();

  arg = strdup(find_arguments(line));
  if (strlen(line))
    {
      f = commands(line, cmds, (sizeof(cmds) / sizeof(t_strfunc)));
      if (f)
        f(state, arg);
      snprintf(buff, sizeof(buff), "%s %s\n", line, arg);
      write_sock(buff, state->net->socket, -1);
    }
  free(arg);
}
