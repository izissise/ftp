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

int	responseokay(char *resp)
{
  if (resp && resp[0] == '2')
    {
      return (1);
    }
  return (0);
}

int	wait_response(void (*f)())
{
  if (f != &lls && f != &lcd && f != &lpwd)
    return (1);
  return (0);
}