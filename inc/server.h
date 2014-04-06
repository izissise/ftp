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
  char		*basedir;
  char		*currdir;
  int		quit;
}		t_fclient;

void	handle_clients(t_fclient *client);

void	noop(t_fclient *client, UNSEDP char **args);
void	list(t_fclient *client, char **args);
void	cd(t_fclient *client, char **args);
void	pwd(t_fclient *client, UNSEDP char **args);

#endif /* !SERVER_H_INCLUDED */
