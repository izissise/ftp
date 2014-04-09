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

void	user_input(int fd, t_cstate *state)
{
  char	*line;

  if ((line = get_next_line(fd)) != NULL)
    {
      do_commands(state, line);
      write_sock("ftp> ", 1, -1);
    }
  else
    state->end = 1;
  free(line);
}

void	print_line(int fd, UNSEDP t_cstate *state)
{
  char	*line;
  char	buff[BUFSIZ];

  if ((line = get_next_line(fd)) != NULL)
    {
      snprintf(buff, sizeof(buff), "%s\n", line);
      write_sock(buff, 1, -1);
    }
  else
    state->end = 1;
  free(line);
}

void		handle_ui(t_net *client)
{
  t_cstate	state;
  char		*line;
  int		actu;
  char	buff[BUFSIZ];

  memset(&state, 0, sizeof(t_cstate));
  state.net = client;
  if ((line = get_next_line(state.net->socket)) != NULL)
    {
      snprintf(buff, sizeof(buff), "%s\n", line);
      write_sock(buff, 1, -1);
      free(line);
    }
  write_sock("ftp> ", 1, -1);
  while (!state.end)
    {
      if ((line = get_next_line(0)) != NULL)
        {
          do_commands(&state, line);
          actu = (line[0] != '\0');
          free(line);
          line = NULL;
          if (actu && (line = get_next_line(state.net->socket)) != NULL)
            {
              snprintf(buff, sizeof(buff), "%s\n", line);
              write_sock(buff, 1, -1);
            }
          write_sock("ftp> ", 1, -1);
        }
      else
        state.end = 1;
      free(line);
    }
}
