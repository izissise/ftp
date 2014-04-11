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
  char	buff[BUFSIZ];

  if ((pasv = init_epsv_connection(state)) != NULL)
    {
      snprintf(buff, sizeof(buff), "%s %s\n", "LIST", arg);
      write_sock(buff, state->net->socket, -1);
      if ((line = get_next_line(state->net->socket)) != NULL)
        {
          send_line(line, 1);
          free(line);
          cat(pasv->socket, 1);
        }
    }
  close_connection(pasv);
}

void	stor(t_cstate *state, char *arg)
{
  t_net	*pasv;
  char	*line;
  char	buff[BUFSIZ];

  if ((pasv = init_epsv_connection(state)) != NULL)
    {
      snprintf(buff, sizeof(buff), "%s %s\n", "STOR", arg);
      write_sock(buff, state->net->socket, -1);
      if ((line = get_next_line(state->net->socket)) != NULL)
        {
          send_line(line, 1);
          free(line);
          recv_file(pasv, arg);
        }
    }
  close_connection(pasv);
}

void	retr(t_cstate *state, char *arg)
{
  t_net	*pasv;
  char	*line;
  char	buff[BUFSIZ];

  if ((pasv = init_epsv_connection(state)) != NULL)
    {
      snprintf(buff, sizeof(buff), "%s %s\n", "RETR", arg);
      write_sock(buff, state->net->socket, -1);
      if ((line = get_next_line(state->net->socket)) != NULL)
        {
          send_line(line, 1);
          free(line);
          send_file(pasv, arg);
        }
    }
  close_connection(pasv);
}

