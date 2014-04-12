/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Sat Apr 12 16:14:36 2014 Hugues
*/

#include "client.h"

void	list(t_cstate *state, char *arg)
{
  t_net	*pasv;
  char	buff[BUFSIZ];

  if ((pasv = init_epsv_connection(state)) != NULL)
    {
      snprintf(buff, sizeof(buff), "%s %s\n", "LIST", arg);
      write_sock(buff, state->net->socket, -1);
      serv_response(state);
      cat(pasv->socket, 1);
      serv_response(state);
    }
  close_connection(pasv);
}

void	stor(t_cstate *state, char *arg)
{
  t_net	*pasv;
  char	buff[BUFSIZ];

  if (switch_paths("./", &arg, 0))
    {
      if ((pasv = init_epsv_connection(state)) != NULL)
        {
          snprintf(buff, sizeof(buff), "%s %s\n", "STOR", arg);
          write_sock(buff, state->net->socket, -1);
          if (serv_response(state) == 0)
            send_file(pasv, arg);
          free(arg);
          serv_response(state);
        }
      close_connection(pasv);
    }
}

void	retr(t_cstate *state, char *arg)
{
  t_net	*pasv;
  char	buff[BUFSIZ];

  if ((pasv = init_epsv_connection(state)) != NULL)
    {
      snprintf(buff, sizeof(buff), "%s %s\n", "RETR", arg);
      write_sock(buff, state->net->socket, -1);
      if (serv_response(state) == 0)
        {
          recv_file(pasv, arg);
          serv_response(state);
        }
    }
  close_connection(pasv);
}

void	quit(t_cstate *state, UNSEDP char *arg)
{
  state->end = 1;
}
