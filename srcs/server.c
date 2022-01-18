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

#include "../includes/minitalk.h"

static void	ft_act_one(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	if (!g_message.curr_bit)
	{
		g_message.curr_bit = 1 << 6;
		g_message.curr_char++;
	}
	g_message.content[g_message.curr_char] += g_message.curr_bit;
	g_message.curr_bit >>= 1;
	if (g_message.curr_char == BUFFER_SIZE - 2 && !g_message.curr_bit)
		g_message.overflow = TRUE;
	kill(info->si_pid, SIGUSR1);
}

static void	ft_act_zero(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	if (!g_message.curr_bit)
	{
		g_message.curr_bit = 1 << 6;
		g_message.curr_char++;
	}
	g_message.curr_bit >>= 1;
	if (g_message.curr_char == BUFFER_SIZE - 2 && !g_message.curr_bit)
		g_message.overflow = TRUE;
	else if (!g_message.content[g_message.curr_char] && !g_message.curr_bit)
		g_message.complet = TRUE;
	kill(info->si_pid, SIGUSR1);
}

static _Bool	main_handler(void)
{
	while (g_message.active)
	{
		pause();
		usleep(100);
		if (g_message.complet || g_message.overflow)
		{
			ft_putstr_fd(g_message.content, _STD_OUT);
			ft_bzero(g_message.content, BUFFER_SIZE);
			g_message.curr_char = 0;
			g_message.curr_bit = 1 << 6;
			if (g_message.complet)
				ft_putchar_fd('\n', _STD_OUT);
			g_message.complet = FALSE;
			g_message.overflow = FALSE;
		}
	}
	return (TRUE);
}

int	main(void)
{
	struct sigaction	act_one;
	struct sigaction	act_zero;

	act_one.sa_sigaction = ft_act_one;
	act_zero.sa_sigaction = ft_act_zero;
	act_one.sa_flags = SA_SIGINFO;
	act_zero.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act_one, NULL) < 0)
		ft_putstr_fd("signal error\n", _STD_OUT);
	if (sigaction(SIGUSR2, &act_zero, NULL) < 0)
		ft_putstr_fd("signal error\n", _STD_OUT);
	ft_putstr_fd("Server PID : ", _STD_OUT);
	ft_putnbr_fd(getpid(), _STD_OUT);
	ft_putstr_fd("\nMessages :\n", _STD_OUT);
	ft_bzero(g_message.content, BUFFER_SIZE);
	main_handler();
	return (0);
}
