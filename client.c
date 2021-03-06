/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:33:05 by tjose             #+#    #+#             */
/*   Updated: 2017/02/16 20:12:39 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	int		sock_fd;
	char	sendline[1000];
	char	recline[1000];
	struct	sockaddr_in	servaddr;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(22000);
	inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));
	connect(sock_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	while(1)
	{
		bzero(sendline, 1000);
		bzero(recline, 1000);
		fgets(sendline, 1000, stdin);
		write(sock_fd, sendline, strlen(sendline) + 1);
		read(sock_fd, recline, 1000);
		write(1, recline, strlen(recline) + 1);
	}
}
