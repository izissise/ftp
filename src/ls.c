/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Thu Apr 10 21:08:18 2014 Hugues
*/

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>

#include "str.h"

char		*get_perm(mode_t perm, char *res)
{
  unsigned int	tmp;
  int		i;

  res[0] = CHECKTYPE('s', S_IFMT, S_IFSOCK) + CHECKTYPE('l', S_IFMT, S_IFLNK)
           + CHECKTYPE('-', S_IFMT, S_IFREG) + CHECKTYPE('d', S_IFMT, S_IFDIR)
           + CHECKTYPE('b', S_IFMT, S_IFBLK) + CHECKTYPE('c', S_IFMT, S_IFCHR)
           + CHECKTYPE('p', S_IFMT, S_IFIFO);
  i = 0;
  tmp = 0b100000000;
  while (i < 3)
    {
      res[i * 3 + 1] = CHECKTYPE('r', tmp, tmp)
                       + ('-' * (CHECKTYPE('r', tmp, tmp) == 0));
      res[i * 3 + 2] = CHECKTYPE('w', tmp >> 1, tmp >> 1)
                       + ('-' * (CHECKTYPE('w', tmp >> 1, tmp >> 1) == 0));
      res[i * 3 + 3] = CHECKTYPE('x', tmp >> 2, tmp >> 2)
                       + ('-' * (CHECKTYPE('x', tmp >> 2, tmp >> 2) == 0));
      i++;
      tmp = tmp >> 3;
    }
  res[10] = '\0';
  return (res);
}

char	*ls_time(struct timespec *t)
{
  char	*res;

  res = ctime((time_t*)t);
  if (res == NULL)
    res = "???";
  else if (strlen(res) > 16)
    res[16] = '\0';
  return (&(res[4]));
}

void		print_file(char *file, char *filena, char *buff)
{
  char		prm[11];
  struct stat	stat;
  char	       	*user;
  char 		*group;
  struct passwd	*pass;
  struct group	*gr;

  if (lstat(file, &stat) == -1)
    snprintf(buff, BUFSIZ, "%s %s\n", filena, strerror(errno));
  else
    {
      user = "???";
      group = "???";
      if ((pass = getpwuid(stat.st_uid)) != NULL)
        user = pass->pw_name;
      if ((gr = getgrgid(stat.st_gid)) != NULL)
        group = gr->gr_name;
      get_perm(stat.st_mode, prm);
      snprintf(buff, BUFSIZ, "%s %4ld %s %s %10ld %s %s\n", prm, stat.st_nlink,
               user, group, stat.st_size, ls_time(&stat.st_mtim), filena);
    }
}

void		ls_base(char **argv, int out)
{
  DIR		*rep;
  struct dirent	*curr_file;
  char		buff[BUFSIZ];
  char		*dir;
  char		file[BUFSIZ];

  if ((dir = argv[0]) == NULL)
    dir = ".";
  if ((rep = opendir(dir)))
    while ((curr_file = readdir(rep)) != NULL)
      {
        if (curr_file->d_name[0] != '.')
          {
            snprintf(file, sizeof(file), "%s/%s", dir, curr_file->d_name);
            print_file(file, curr_file->d_name, buff);
            write_sock(buff, out, -1);
          }
      }
  else
    {
      snprintf(file, sizeof(file), "%s\n", strerror(errno));
      write_sock(file, out, -1);
    }
  closedir(rep);
}
