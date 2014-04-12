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

char	*find_arguments(char *line)
{
  int	i;

  i = 0;
  while (line[i] && line[i] != ' ')
    ++i;
  if (line[i] == ' ')
    line[i] = '\0';
  else
    --i;
  return (&(line[i + 1]));
}

void	(*commands(char *command, t_strfunc *cmds, int size))()
{
  int	i;

  i = 0;
  while (i < size)
    {
      if (!(strncasecmp((cmds[i]).str, command, strlen((cmds[i]).str))))
        return ((cmds[i]).func);
      i++;
    }
  return (NULL);
}