/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:13:51 by ahocine           #+#    #+#             */
/*   Updated: 2021/12/14 17:13:55 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_act_one(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	if (!message.curr_bit)
	{
		message.curr_bit = 1 << 6;
		message.curr_octet++;
	}
	message.content[message.curr_octet] += message.curr_bit;
	message.curr_bit >>= 1;
	if (message.curr_octet == BUFFER_SIZE - 2 && !message.curr_bit)
		message.overflow = TRUE;
}

void	ft_act_zero(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	if (!message.curr_bit)
	{
		message.curr_bit = 1 << 6;
		message.curr_octet++;
	}
	message.curr_bit >>= 1;
	if (message.curr_octet == BUFFER_SIZE - 2 && !message.curr_bit)
		message.overflow = TRUE;
	else if (message.content[message.curr_octet] && !message.curr_bit)
	{
		message.complet = TRUE;
		kill(info->si_pid, SIGUSR1);
	}
}

_Bool	main_handler()
{
	while (1)
	{
		pause();
		if (message.complet || message.overflow)
		{
			ft_putstr_fd(message.content, _STD_OUT);
			ft_bzero(message.content, BUFFER_SIZE);
			message.curr_octet = 0;
			message.curr_bit = 1 << 6;
			if (message.complet)
				ft_putchar_fd('\n', _STD_OUT);
			message.complet = FALSE;
			message.overflow = FALSE;
		}
	}
	return (TRUE);
}

int	main(void)
{
	struct	sigaction act_one;
	struct	sigaction act_zero;

	act_one.sa_sigaction = ft_act_one;
	act_zero.sa_sigaction = ft_act_zero;
	act_one.sa_flags = SA_SIGINFO;
	act_zero.sa_flags = SA_SIGINFO;
	if (!(sigaction(SIGUSR1, &act_one, NULL)))
	{
		ft_putstr_fd("signal error\n", _STD_OUT);
	}
	if (!(sigaction(SIGUSR2, &act_zero, NULL)))
	{
		ft_putstr_fd("signal error\n", _STD_OUT);
	}
	ft_putnbr_fd(getpid(), _STD_OUT);
	ft_bzero(message.content, BUFFER_SIZE);
	main_handler();
}
