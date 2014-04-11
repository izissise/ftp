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
#include <string.h>

#include "network.h"

void	send_line(char *line, int fd)
{
  char	*rline;
  int	len;

  len = line ? strlen(line) : 0;
  if (!line || (rline = malloc((len + 3) * sizeof(char))) == NULL)
    return ;
  strcpy(rline, line);
  strcpy(&(rline[len]), "\n");
  write_sock(rline, fd, len + 1);
  free(rline);
}

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

void	cat(int in, int out)
{
  int	tmp;
  char	buff[64 * 1024];

  while ((tmp = read(in, buff, BUFSIZ)) > 0)
    write_sock(buff, out, tmp);
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
