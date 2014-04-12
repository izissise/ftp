/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef STR_H_INCLUDED
# define STR_H_INCLUDED

# define _GNU_SOURCE
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>

# define UNSEDP __attribute__((unused))
# define PTRT_PACK 10

# define MASK_IT(x, y, z) (((x) & (y)) == (z))
# define CHECKTYPE(x, y, z) (MASK_IT(perm, (y), (z)) * (x))

typedef struct	s_strfunc
{
  const char	*str;
  void		(*func)();
}		t_strfunc;

char	*get_pwd();
char	*abs_path(char *currpath);
char	*path_to_bd_path(char *basepath, char *path);
int	switch_paths(char *basepath, char **path, int removefile);

int	ptr_tab_size(void **tab);
void	**add_ptr_t_tab(void **tab, void *add);
void	rm_ptr_f_tab(void **tab, void *ptr);
void	free_ptr_tab(void **tab, void	(*f)(void *ptr));
void	rm_empty_str_f_tab(char **tab);
void	**concat_ptr_tab(void **tab1, void **tab2);
void	swap_ptr(void **pt1, void **pt2);
char	*stradd(char *s1, char *s2);

char	*get_next_line(const int fd);
void	write_sock(const char *str, int socket, int strlen);

void	ls_base(char **argv, int out);
int	cd_base(char **argv);

char	*find_arguments(char *line);
void	(*commands(char *command, t_strfunc *cmds, int size))();

#endif /* !STR_H_INCLUDED */
