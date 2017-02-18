/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:33:10 by tjose             #+#    #+#             */
/*   Updated: 2017/02/16 20:12:37 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	char	str[1000];
	int		listen_fd;
	int		comm_fd;
	struct	sockaddr_in	servaddr;
	pid_t	pid;

	if (argc == 2)
	{
		if (!strcmp(argv[1], "-D"))
		{
			pid = fork();
			if (pid < 0)
			{
				printf("fork failed\n");
				exit(1);
			}
			if (pid > 0)
			{
				printf("pid of child is %d\n", pid);
				exit(0);
			}
		}
	}
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(22000);
	bind(listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	listen(listen_fd, 10);
	comm_fd = accept(listen_fd, NULL, NULL);
	while(1)
	{
		bzero(str, 1000);
		read(comm_fd, str, 1000);
		if (!strcmp(str, "ping\n"))
			write(comm_fd, "pong\npong\n", 11);
		else
			write(comm_fd, "", 1);
	}
}
