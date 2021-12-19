/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 15:47:23 by ahocine           #+#    #+#             */
/*   Updated: 2021/12/19 15:47:27 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char *argv[])
{
	struct sigaction	act;
	int					server_pid;
	char				*message;
	int					i;

	if (argc != 3)
		ft_putstr_fd("usage: ./client [server-pid] [message]\n", _STD_OUT);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	signal(SIGUSR1, success);
	main_handler(argv[1], argv[2]);
	return (0);
}
