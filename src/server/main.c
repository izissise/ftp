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

int	main(int ac, char **av)
{
  (void)ac;
  (void)av;
  t_net *net;

  net = create_connection("localhost", "8001", SOCK_STREAM, &bind);

  return (0);
}
