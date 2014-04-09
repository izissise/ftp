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

void	list(t_cstate *state, char *arg)
{
  t_net	*pasv;
  char	*line;
  int	tmp;
  char	buff[BUFSIZ];

  if ((pasv = init_epsv_connection(state)) != NULL)
    {
      snprintf(buff, sizeof(buff), "%s %s\n", "LIST", arg);
      write_sock(buff, state->net->socket, -1);
      if ((line = get_next_line(state->net->socket)) != NULL)
        {
          snprintf(buff, sizeof(buff), "%s\n", line);
          write_sock(buff, 1, -1);
          free(line);
          while ((tmp = read(pasv->socket, buff, sizeof(buff))) > 0)
            write_sock(buff, 1, tmp);
        }
    }
  close_connection(pasv);
}

void	put(t_cstate *state, char *arg)
{

}

void	get(t_cstate *state, char *arg)
{

}

