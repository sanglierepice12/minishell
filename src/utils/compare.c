/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:48:37 by gsuter            #+#    #+#             */
/*   Updated: 2024/09/25 05:46:27 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_export_is_printable(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!c[i])
			return (0);
		if ((c[i] < 'a' || c[i] > 'z') && (c[i] < 'A' || c[i] > 'Z')
			&& (c[i] < '0' || c[i] > '9') \
			&& c[i] != '=' && c[i] != '/' && c[i] != '+' \
			&& c[i] != '_')
			return (1);
		if (c[i] == '-' && c[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_str_chr(const char *src, const char str)
{
	size_t	i;

	if (!str || !src)
		return (0);
	i = 0;
	while (src[i])
	{
		if (src[i] == str)
			return (1);
		i++;
	}
	if (src[i])
		return (0);
	return (0);
}

int	ft_comp_str(const char *src, const char *str)
{
	size_t	i;

	if (!str || !src)
		return (0);
	if (ft_strlen(src) != ft_strlen(str))
		return (0);
	i = 0;
	while (src[i])
	{
		if (src[i] == str[i])
			i++;
		else
			return (0);
	}
	if (src[i] || str[i])
		return (0);
	return (1);
}

int	ft_comp_str_for_alpha(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
