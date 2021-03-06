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

#include "../includes/minitalk.h"

static void	ft_void(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	(void)info;
}

static void	send_char(int pid, unsigned char byte)
{
	uint8_t	counter;

	counter = 1 << 6;
	while (counter)
	{
		if (byte & counter)
		{
			if (kill(pid, SIGUSR1) < 0)
				ft_putstr_fd("bad pid\n", _STD_OUT);
		}
		else
		{
			if (kill(pid, SIGUSR2) < 0)
				ft_putstr_fd("bad pid\n", _STD_OUT);
		}
		counter >>= 1;
		usleep(100);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	act;
	int					server_pid;
	char				*message;

	if (argc != 3)
	{
		ft_putstr_fd("usage: ./client [server pid] [message]\n", _STD_OUT);
		return (-1);
	}
	ft_memset(&act, 0, sizeof(act));
	act.sa_sigaction = ft_void;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	if (sigaction(SIGUSR1, &act, NULL) < 0)
		return (-1);
	while (*message)
	{
		send_char(server_pid, *message);
		message++;
	}
	send_char(server_pid, *message);
	return (0);
}
