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
    do_commands(state, line);
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
  t_selfd		**fds;
  t_selfd		*active;

  memset(&state, 0, sizeof(t_cstate));
  state.net = client;
  fds = NULL;
  fds = (t_selfd**)add_ptr_t_tab(
          (void**)fds, (void*)create_fd(client->socket, FDREAD, &print_line));
  fds = (t_selfd**)add_ptr_t_tab(
          (void**)fds, (void*)create_fd(0, FDREAD, &user_input));
  while (!state.end)
    if ((active = do_select(fds)) != NULL)
      (active->callback)(active->fd, &state);
  free_ptr_tab((void**)fds, &free);
}
