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

int	main(UNSEDP int ac, UNSEDP char **av)
{
  char	buff[1024];
  int	tmp;
  t_net	*client;

  if (ac != 3)
    return (1);
  if (!(client = create_connection(av[1], av[2], SOCK_STREAM, &connect)))
    return (1);
  while ((tmp = read(1, buff, 1024)) > 0)
    {
      write(client->socket, buff, tmp);
    }
  close_connection(client);
  return (0);
}
