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
	;
}

void	ft_act_zero(int sig, siginfo_t *info, void *context)
{
	;
}

_Bool	main_handler()
{
	while (1)
	{
		pause();

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
		return (-1);
	}
	if (!(sigaction(SIGUSR2, &act_zero, NULL)))
	{
		ft_putstr_fd("signal error\n", _STD_OUT);
		return (-1);
	}
	ft_putnbr_fd(getpid(), _STD_OUT);
	ft_bzero(message.content, BUFFER_SIZE);
	main_handler();
}
