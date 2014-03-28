/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "network.h"

int	main(int ac, char **av)
{
  (void)ac;
  (void)av;
  char buff[1024];
  int t;
  t_net *server;
  t_net *client;

  server = create_connection(NULL, "8001", SOCK_STREAM, &bind);
  if (listen(server->socket, MAX_CLIENTS) == -1)
    perror("listen");



  printf("server: waiting for connections...\n");

  while(1) {  // main accept() loop
      if (!(client = accept_connection(server->socket)))
        continue;
      inet_ntop(((struct sockaddr*)(&(client->addr)))->sa_family,
                get_ip_addr(client), buff, sizeof(buff));
      printf("server: got connection from %s\n", buff);

      if (!fork()) { // this is the child process
          close_connection(server);
          if (send(client->socket, "Hello, world!", 13, 0) == -1)
            perror("send");
          close_connection(client);
          exit(0);
        }
      close_connection(client); // parent doesn't need this
    }


  /*
    while ((t = read(server->socket, buff, 1024) >= 0))
      {
        write(1, buff, t);
      }*/
  close_connection(server);
  return (0);
}
