#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "TCP.h"

void clinet(){

  char *ip = "127.0.0.1";
  int port = 5566;

  struct sockaddr_in addr;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
    perror("[-]Socket error");
    exit(1);
  }
  printf("[+]TCP server socket created.\n");

  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = inet_addr(ip);

  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  printf("Connected to the server.\n");

}
