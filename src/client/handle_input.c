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

void		handle_ui(t_net *client)
{
  t_cstate	state;
  char		*line;

  memset(&state, 0, sizeof(t_cstate));
  state.net = client;
  if ((line = get_next_line(state.net->socket)) != NULL)
    {
      send_line(line, 1);
      free(line);
    }
  write_sock(PROMPT, 1, -1);
  while (!state.end)
    {
      if ((line = get_next_line(0)) != NULL)
        {
          if (line[0] != '\0')
            do_commands(&state, line);
          free(line);
          line = NULL;
          write_sock(PROMPT, 1, -1);
        }
      else
        state.end = 1;
      free(line);
    }
}
