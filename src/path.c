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

char	*abs_path(char *currpath)
{
  char	*res;

  if (currpath == NULL)
    return (NULL);
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

char	*is_path_out(char *basepath, char *path)
{
  char	*abspath;
  char	*tmppath;

  if (!path || (tmppath = malloc(strlen(path) + 3)) == NULL)
    return (NULL);
  snprintf(tmppath, strlen(path) + 3, "%s%s%s", path[0] == '/' ? "" : "./",
           &(path[path[0] == '/']), "/");
  abspath = abs_path(tmppath);
  free(tmppath);
  if ((abspath == NULL) || (basepath == NULL))
    return (NULL);
  if (strncmp(basepath, abspath, strlen(basepath)))
    {
      printf("%s\n", abspath);
      free(abspath);
      return (NULL);
    }
  printf("%s\n", abspath);
  return (abspath);
}
