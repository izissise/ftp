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

void	cat(int in, int out)
{
  int	tmp;
  char	buff[BUFSIZ];

  while ((tmp = read(in, buff, BUFSIZ)) > 0)
    write(out, buff, tmp);
}

int	send_file(t_net *net, const char *filename)
{
  int	file;

  if ((file = open(filename, O_RDONLY)) == -1)
    {
      perror(filename);
      return (1);
    }
  cat(file, net->socket);
  close(file);
  return (0);
}

int	recv_file(t_net *net, const char *filename)
{
  int	file;

  if ((file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
    {
      perror(filename);
      return (1);
    }
  cat(net->socket, file);
  close(file);
  return (0);
}
