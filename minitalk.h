/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:17:27 by ahocine           #+#    #+#             */
/*   Updated: 2021/12/14 17:17:33 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <zconf.h>
# include <stdint.h>
# include "../libft_private/libft.h"

# ifndef	BUFFER_SIZE
#  define	BUFFER_SIZE		4096
# endif

# ifndef	FALSE
#  define	FALSE			0
# endif

# ifndef	TRUE
#  define	TRUE			1
# endif

# define	_STD_OUT		1

typedef struct s_minitalk
{
	char	content[BUFFER_SIZE];
	int		curr_bit;
	int		curr_octet;
	_Bool	complet;
	_Bool	overflow;
}			t_message;

t_message	g_message = {{0}, 1 << 6, 0, FALSE, FALSE};

#endif
