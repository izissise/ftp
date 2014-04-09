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

void	cd(t_cstate *state, char *arg)
{
  char	buff[BUFSIZ];

  snprintf(buff, sizeof(buff), "%s %s\n", "CWD", arg);
  write_sock(buff, state->net->socket, -1);
}

void	lls(UNSEDP t_cstate *state, char *arg)
{
  char	*tmp[2];

  tmp[0] = arg;
  if (arg[0] == '\0')
    tmp[0] = NULL;
  tmp[1] = NULL;
  ls_base(tmp, 1);
}

void	lcd(UNSEDP t_cstate *state, char *arg)
{
  char	*tmp[2];
  char	*tmp2;

  tmp[0] = arg;
  tmp[1] = NULL;
  if (arg[0] == '\0')
    write_sock("cd: Require one argument\n", 1, -1);
  else
    {
      cd_base(tmp);
      tmp2 = get_pwd();
      write_sock(tmp2, 1, -1);
      free(tmp2);
      write_sock("\n", 1, -1);
    }
}

void	lpwd(UNSEDP t_cstate *state, UNSEDP char *arg)
{
  char	*tmp2;

  tmp2 = get_pwd();
  write_sock(tmp2, 1, -1);
  free(tmp2);
  write_sock("\n", 1, -1);
}
