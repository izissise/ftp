/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "client.h"

t_net	*parse_epsv(char *ip, char *resp)
{
  t_net	*res;
  char	*port;
  int	i;

  i = 0;
  if (!(port = strstr(resp, "|||")))
    return (NULL);
  while (port[i] == '|')
    i++;
  port = &(port[i]);
  i = 0;
  while (port[i] != '|' && port[i])
    i++;
  port[i] = '\0';
  printf("epsv: ip: %s port: %s\n", ip, port);
  res = create_connection(ip, port, SOCK_STREAM, &connect);
  return (res);
}

t_net	*init_epsv_connection(t_cstate *state)
{
  char	*resp;
  char	*ip;
  t_net	*res;
  t_net	*peers;

  res = NULL;
  write_sock("EPSV\n", state->net->socket, -1);
  if ((resp = get_next_line(state->net->socket)) == NULL)
    return (NULL);
  if ((peers = peer(state->net)) == NULL)
    {
      free(resp);
      return (NULL);
    }
  if ((ip = get_ip_addr(peers)) != NULL)
    {
      res = parse_epsv(ip, resp);
      free(ip);
    }
  close_connection(peers);
  free(resp);
  return (res);
}
