/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "server.h"

void		new_client(t_net *server, t_net *client)
{
  t_fclient	fcli;
  pid_t		tmp;

  tmp = fork();
  if (tmp == 0)
    {
      close_connection(server);
      fcli.net = client;
      fcli.basedir = get_pwd();
      fcli.currdir = strdup(fcli.basedir);
      fcli.quit = 0;
      handle_clients(&fcli);
      close_connection(client);
      exit(0);
    }
  else if (tmp < 0)
    perror("fork");
  close_connection(client);
}

int	main(UNSEDP int ac, UNSEDP char **av)
{
  t_net	*server;
  t_net	*client;

  signal(SIGCHLD, SIG_IGN);
  server = create_connection(NULL, "8001", SOCK_STREAM, &bind);
  if (!server)
    return (1);
  if (listen(server->socket, MAX_CLIENTS) == -1)
    perror("listen");
  printf("server: waiting for connections...\n");
  while (1)
    {
      if (!(client = accept_connection(server->socket)))
        continue;
      new_client(server, client);
    }
  close_connection(server);
  return (0);
}

