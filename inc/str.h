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

char	*get_pwd();
char	*abs_path(char *currpath);
int	is_path_out(char *basepath, char *path);

int	ptr_tab_size(void **tab);
void	**add_ptr_t_tab(void **tab, void *add);
void	rm_ptr_f_tab(void **tab, void *ptr);
void	free_ptr_tab(void **tab, void	(*f)(void *ptr));
void	rm_empty_str_f_tab(char **tab);
void	**concat_ptr_tab(void **tab1, void **tab2);

char	**expand_reg_exp(char *regexp);
void	expand_reg_exp_on_tab(char ***tab);

#endif /* !STR_H_INCLUDED */
