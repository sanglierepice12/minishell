/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:06:24 by gsuter            #+#    #+#             */
/*   Updated: 2024/09/24 08:37:30 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_str_join(char *begin, char *end)
{
	char	*final;
	size_t	i;
	size_t	j;

	final = ft_cal_loc(ft_strlen(begin) + ft_strlen(end) + 1, sizeof(char));
	if (!final)
		return (NULL);
	i = 0;
	while (end[i])
	{
		final[i] = end[i];
		i++;
	}
	j = 0;
	while (begin[j])
	{
		final[i] = begin[j];
		i++;
		j++;
	}
	return (final);
}

char	*ft_str_copy_n(const char *str, size_t n)
{
	char	*dup;
	size_t	i;

	dup = ft_cal_loc(n + 1, sizeof(char));
	if (!dup)
		return (NULL);
	dup[n] = 0;
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
	ssize_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

size_t	ft_strlen_double(char **str)
{
	size_t	len;

	if (!str)
		return (0);
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

char	*ft_strdup(const char *str)
{
	char	*tab;
	size_t	i;

	if (!str)
		return (NULL);
	tab = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (str[i])
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	**ft_strstrdup(char **str)
{
	char	**tab;
	size_t	i;

	i = 0;
	tab = ft_cal_loc(ft_strlen_bis(str), sizeof(char *));
	while (str[i])
	{
		tab[i] = ft_strdup(str[i]);
		if (!tab[i])
			return (free_tab(tab, ft_strlen_bis(str)), NULL);
		i++;
	}
	return (tab);
}