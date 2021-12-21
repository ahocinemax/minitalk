/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocine <ahocine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:08:08 by ahocine           #+#    #+#             */
/*   Updated: 2021/05/22 17:29:46 by ahocine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cntline(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] && str[i] != sep)
			count++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (count);
}

static int	ft_init(int *a, int *b)
{
	*a = 0;
	*b = 0;
	return (0);
}

static int	ft_malloc_arr(char ***arr, const char *str, char sep)
{
	int len;

	len = ft_cntline(str, sep);
	if (len > 0)
		*arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!(*arr))
		return (0);
	return (1);
}

static char	*ft_malloc_word(int size_line, const char *word_to_malloc, int *s_line)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(size_line + 1);
	if (!dest)
		return (NULL);
	while (word_to_malloc[i] && i < size_line)
	{
		dest[i] = word_to_malloc[i];
		i++;
	}
	*s_line += i;
	dest[i] = 0;
	return (dest);
}

char	**ft_split(const char *str, char sep)
{
	char	**arr;
	int		index;
	int		i;
	int		s_line;

	if (ft_init(&index, &i) || !ft_malloc_arr(&arr, str, sep))
		return (NULL);
	while (index < ft_cntline(str, sep) && i < ft_strlen(str) - 1)
	{
		s_line = 0;
		while ((char)str[s_line + i] && ((char)str[i + s_line] != sep))
			s_line++;
		if (s_line > 0)
		{
			arr[index++] = ft_malloc_word(s_line, (char *)&str[i], &i);
			if (!arr[index - 1])
				free(arr);
		}
		while ((char)str[i] && (char)str[i] == sep)
			i++;
	}
	if (str[i] && index < ft_cntline(str, sep))
		arr[index++] = ft_malloc_word(ft_strlen(str) - i, (char *)&str[i], &i);
	arr[index] = 0;
	return (arr);
}
