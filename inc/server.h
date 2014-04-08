/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef SERVER_H_INCLUDED
# define SERVER_H_INCLUDED

# include <signal.h>
# include <string.h>

# include "network.h"
# include "str.h"

typedef struct	s_fclient
{
  t_net		*net;
  t_net		*pasv;
  char		*basedir;
  char		*currdir;
  char		*user;
  int		logged;
  int		quit;
}		t_fclient;

void	handle_clients(t_fclient *client);

void	noop(t_fclient *client, UNSEDP char *arg);
void	list(t_fclient *client, char *arg);
void	cd(t_fclient *client, char *arg);
void	pwd(t_fclient *client, UNSEDP char *arg);
void	quit(t_fclient *client, UNSEDP char *arg);
void	get(t_fclient *client, char *arg);
void	pasv(t_fclient *client, char *arg);
void	user(t_fclient *client, char *arg);
void	pass(t_fclient *client, char *arg);

t_net	*create_passive_connection(t_fclient *client);
char	*calculate_pasvconnection_info(t_net *net);
char	*calculate_epsvconnection_info(t_net *net);
void	accept_passive_connection(t_fclient *client);

#endif /* !SERVER_H_INCLUDED */
