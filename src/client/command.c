/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Sat Apr 12 16:14:56 2014 Hugues
*/

#include "client.h"

static t_strfunc	cmds[] = {
  {"LLS", &lls},
  {"LCD", &lcd},
  {"LPWD", &lpwd},
  {"LS", &list},
  {"LIST", &list},
  {"CD", &cd},
  {"GET", &retr},
  {"RETR", &retr},
  {"PUT", &stor},
  {"STOR", &stor},
  {"PASS", &pass},
  {"QUIT", &quit}
};

static void	send_unk_cmd(t_cstate *state, char *line, char *arg)
{
  char		buff[BUFSIZ];

  snprintf(buff, sizeof(buff), "%s %s\n", line, arg);
  write_sock(buff, state->net->socket, -1);
  serv_response(state);
}

int	serv_response(t_cstate *state)
{
  char	*line;
  int	ret;

  ret = -1;
  if ((line = get_next_line(state->net->socket)) != NULL)
    {
      ret = 0;
      if (line[0] == '5')
        ret = 1;
      send_line(line, 1);
      free(line);
    }
  return (ret);
}

void	do_commands(t_cstate *state, char *line)
{
  char	*arg;
  void	(*f)();

  arg = strdup(find_arguments(line));
  if ((strlen(line))
      && (f = commands(line, cmds, (sizeof(cmds) / sizeof(t_strfunc)))))
    f(state, arg);
  else if (strlen(line))
    send_unk_cmd(state, line, arg);
  free(arg);
}
