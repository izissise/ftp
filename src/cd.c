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

int	cd_base(char **argv, int out)
{
  if (chdir(argv[1]))
    {
      write_sock(strerror(errno), out, -1);
      return (1);
    }
  return (0);
}
