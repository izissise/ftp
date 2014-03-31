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

typedef struct	s_fclient
{
  t_net		*net;
  char		*basedir;
  char		*currdir;
  int		quit;
}		t_fclient;

typedef struct	s_strfunc
{
  const char	*str;
  void		(*func)(t_fclient *client);
}		t_strfunc;

void	handle_clients(t_fclient *client);

#endif /* !SERVER_H_INCLUDED */
