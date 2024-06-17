/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:06:24 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/21 17:06:24 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_str_copy_n(char *str, int n)
{
	char	*dup;
	int		i;

	dup = ft_cal_loc(n, sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

size_t	ft_strlen_double(char **str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_super_dup(char *src, char *msg)
{
	char	*dup;
	ssize_t	i;
	ssize_t	j;
	size_t	len;

	if (!src)
		return (NULL);
	if (msg)
		len = ft_strlen(src) + ft_strlen(msg);
	else
		len = ft_strlen(src);
	dup = ft_cal_loc(len + 1, sizeof(char));
	if (!dup)
		return (NULL);
	i = -1;
	j = -1;
	while (++i, src[i])
		dup[i] = src[i];
	if (msg)
	{
		while (++j, msg[j])
			dup[i++] = msg[j];
	}
	return (dup);
}
