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

void	init_client(t_fclient *fcli)
{
  fcli->pasv = NULL;
  fcli->user = NULL;
  fcli->basedir = get_pwd();
  fcli->currdir = fcli->basedir ? strdup(fcli->basedir) : NULL;
  fcli->quit = 0;
  fcli->logged = 0;
}

void	destroy_client(t_fclient *fcli)
{
  free(fcli->basedir);
  free(fcli->currdir);
  free(fcli->user);
}

void		new_client(t_net *server, t_net *client)
{
  t_fclient	fcli;
  pid_t		tmp;
  char		*ip;

  if ((tmp = fork()) == 0)
    {
      close_connection(server);
      printf("client connected %s:%d\n",
             (ip = get_ip_addr(client)) ? ip : "unknow", port_number(client));
      fcli.net = client;
      init_client(&fcli);
      handle_clients(&fcli);
      destroy_client(&fcli);
      printf("client disconnected %s:%d\n", ip ? ip : "unknow",
             port_number(client));
      free(ip);
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
  char	*ip;

  signal(SIGCHLD, SIG_IGN);
  if (!(server = create_connection(listening_ip(SERVERTYPE),
                                   av[1] ? av[1] : "22", SOCK_STREAM, &bind)))
    return (1);
  if (listen(server->socket, MAX_CLIENTS) == -1)
    perror("listen");
  ip = get_ip_addr(server);
  if (ip)
    printf("server %s:%d : waiting for connections...\n", ip,
           port_number(server));
  free(ip);
  while (1)
    {
      if (!(client = accept_connection(server->socket)))
        continue ;
      new_client(server, client);
    }
  close_connection(server);
  return (0);
}
