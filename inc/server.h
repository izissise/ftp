/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef SERVER_H_INCLUDED
# define SERVER_H_INCLUDED

# include <sys/types.h>
# include <sys/wait.h>

# include "network.h"

void	handle_clients(t_net *client);

#endif // SERVER_H_INCLUDED
