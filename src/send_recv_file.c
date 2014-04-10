/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "network.h"

int	send_file(t_net *net, const char *filename)
{
  int	file;
  int	tmp;
  char	buff[BUFSIZ];

  if ((file = open(filename, O_RDONLY)) == -1)
    {
      perror(filename);
      return (1);
    }
  while ((tmp = read(file, buff, BUFSIZ)) > 0)
    write(net->socket, buff, tmp);
  close(file);
  return (0);
}

int	recv_file(t_net *net, const char *filename)
{

}
