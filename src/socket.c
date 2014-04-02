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

void	write_sock(const char *str, int socket, int strlen)
{
  int	len;

  len = 0;
  if (str != NULL)
    {
      if (strlen == -1)
        {
          while (str[len] != '\0')
            len++;
          strlen = len;
        }
      while ((len = write(socket, str, strlen)) != strlen)
        {
          if (len == -1)
            {
              perror("write");
              return ;
            }
          str = &(str[len]);
          strlen -= len;
        }
    }
}