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

const char	*first_word_f_str(const char *str, char **word,
                              const char *sepa)
{
  int		i;
  int		k;
  int		dq;

  i = 0;
  k = 0;
  dq = 0;
  if (((*word) = malloc((strlen(str) + 1) * sizeof(char))) == NULL)
    return (str);
  while ((str[i] != '\0') && ((strncmp(&(str[i]), sepa, strlen(sepa))) || dq))
    {
      if ((str[i] == '\\') && (str[i + 1] != '\0' && !dq))
        i += 1;
      else if ((str[i] == '"') && (str[i + 1] != '\0'))
        {
          i += 1;
          dq = dq ? 0 : 1;
        }
      (*word)[k] = str[i];
      k++;
      i++;
    }
  (*word)[k - (k != 0 && dq)] = '\0';
  return (&(str[i]));
}

char	**str_wt(const char *str, const char *sepa)
{
  char	**res;
  char	*strtadd;

  res = NULL;
  if (str == NULL)
    return (NULL);
  while (str[0] != '\0')
    {
      str = first_word_f_str(str, &strtadd, sepa);
      res = (char**)add_ptr_t_tab((void**)res, (void*)strtadd);
      str = str[0] ? &(str[1]) : str;
    }
  rm_empty_str_f_tab(res);
  return (res);
}
