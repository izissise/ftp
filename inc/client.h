/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef CLIENT_H_INCLUDED
# define CLIENT_H_INCLUDED

# include <signal.h>
# include "str.h"
# include "network.h"
# include "select.h"

typedef struct	s_cstate
{
  t_net		*net;
  t_net		*pasv;
  char		**pending_cmds;
  int		end;
}		t_cstate;

void	handle_ui(t_net *client);
void	do_commands(t_cstate *state, char *line);

void	cd(t_cstate *state, char *arg);
void	lpwd(t_cstate *state, char *arg);
void	lcd(t_cstate *state, char *arg);
void	lls(t_cstate *state, char *arg);
void	list(t_cstate *state, char *arg);
void	put(t_cstate *state, char *arg);
void	get(t_cstate *state, char *arg);

#endif /* !CLIENT_H_INCLUDED */
