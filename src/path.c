/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "network.h"

char	*abs_path(char *currpath)
{
  char	*res;
  res = canonicalize_file_name(currpath);
  if (res == NULL)
    perror("realpath");
  return (res);
}

char	*get_pwd()
{
  char	*res;

  res = getcwd(NULL, 0);
  if (res == NULL)
    perror("getcwd");
  return (res);
}
