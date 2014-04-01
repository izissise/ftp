/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Thu May 23 16:19:19 2013 maxime lavandier
*/

#include <glob.h>
#include "str.h"

char		**expand_reg_exp(char *regexp)
{
  glob_t	res;
  char		**tab;
  char		*tmp;
  int		flags;
  unsigned int	i;

  flags = GLOB_MARK | GLOB_NOCHECK | GLOB_BRACE | GLOB_TILDE;
  tab = NULL;
  if (regexp == NULL)
    return (NULL);
  if (glob(regexp, flags, NULL, &res) != 0)
    {
      fprintf(stderr, "%s\n", "Globbing error");
      return (NULL);
    }
  i = 0;
  tab = NULL;
  while (i < res.gl_pathc)
    {
      tmp = strdup(res.gl_pathv[i]);
      tab = (char**)add_ptr_t_tab((void**)tab, (void*)tmp);
      i++;
    }
  globfree(&res);
  return (tab);
}

void	expand_reg_exp_on_tab(char ***tab)
{
  int	i;
  char	**res;
  char	**tmp;
  char	**tmptfree;

  i = 0;
  res = NULL;
  if (((*tab) == NULL) || ((*tab)[0] == NULL))
    return ;
  res = (char**)add_ptr_t_tab((void**)res, (void*)(*tab)[0]);
  while ((*tab)[++i] != NULL)
    {
      if ((tmp = expand_reg_exp((*tab)[i])) != NULL)
        {
          tmptfree = res;
          res = (char**)concat_ptr_tab((void**)res, (void**)tmp);
          free((*tab)[i]);
          free(tmp);
          free(tmptfree);
        }
      else
        res = (char**)add_ptr_t_tab((void**)res, (void*)(*tab)[i]);
    }
  free(*tab);
  (*tab) = res;
}
