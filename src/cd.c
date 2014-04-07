/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "str.h"

int	cd_base(char **argv, char *basedir, int out)
{
  char	*tmp;
  int	i;
  char	buff[BUFSIZ];

  i = 0;
  if (chdir(argv[0]))
    {
      write_sock(strerror(errno), out, -1);
      return (1);
    }
  if (!(tmp = get_pwd()))
    return (0);
  while ((tmp[i] == basedir[i]) && tmp[i])
    ++i;
  snprintf(buff, sizeof(buff), "/%s\n", &(tmp[i + (tmp[i] == '/')]));
  write_sock(buff, out, -1);
  free(tmp);
  return (0);
}
