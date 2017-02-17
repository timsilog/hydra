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

int main(void)
{
	char	str[100];
	char	str2[200];
	int		listen_fd;
	int		comm_fd;
	struct	sockaddr_in	servaddr;

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
		bzero(str, 100);
		bzero(str2, 200);
		read(comm_fd, str, 100);
		strcpy(str2, str);
		strcat(str2, str);
		write(comm_fd, str2, strlen(str2) + 1);
	}
}
