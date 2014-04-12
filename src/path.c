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

char	*path_to_bd_path(char *basepath, char *path)
{
  char	*abspath;
  char	*tmppath;
  int	len;

  len = (path ? strlen(path) : 0) + (basepath ? strlen(basepath) : 0)  + 3;
  if (!path || !basepath || (tmppath = malloc(len)) == NULL)
    return (NULL);
  snprintf(tmppath, len, "%s/%s/%s", ((path[0] == '/') ? basepath : "./"),
           path, "/");
  abspath = abs_path(tmppath);
  free(tmppath);
  if ((abspath == NULL) || (basepath == NULL))
    return (NULL);
  if (strncmp(basepath, abspath, strlen(basepath)))
    {
      free(abspath);
      return (strdup(basepath));
    }
  return (abspath);
}

void	file_and_path(char **path, char **file)
{
  int	i;
  char	*res;
  char	*tmp;

  if ((i = strlen(*path)) <= 0)
    return ;
  while (--i >= 0)
    if ((*path)[i] == '/')
      {
        (*path)[i] = '\0';
        break ;
      }
  tmp = &((*path)[i + ((*path)[0] != '\0')]);
  if ((res = malloc((strlen(tmp) + 3) * sizeof(char))) == NULL)
    return ;
  strcpy(res, "/");
  strcpy(&(res[1]), tmp);
  *file = res;
  if (i == -1)
    {
      free(*path);
      *path = strdup("./");
    }
}

int	switch_paths(char *basepath, char **path, int removefile)
{
  char	*tmp;
  char	*tmp2;
  char	*file;
  char	*tmppath;

  file = NULL;
  tmp2 = NULL;
  tmppath = strdup(*path);
  if (removefile && tmppath)
    file_and_path(&tmppath, &tmp2);
  file = (tmp = path_to_bd_path(basepath, tmppath)) ? stradd(tmp, tmp2) : NULL;
  if (removefile && tmppath)
    free(tmp2);
  free(tmp);
  free(tmppath);
  if (!file)
    return (0);
  swap_ptr((void**)(path), (void**)&file);
  return (1);
}
