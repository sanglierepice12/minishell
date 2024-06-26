/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:48:37 by gsuter            #+#    #+#             */
/*   Updated: 2024/06/03 16:48:37 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_export_is_printable(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == '+' && c[i + 1] == '=')
			i++;
		if (!c[i])
			return (0);
		if ((c[i] < 'a' || c[i] > 'z') && (c[i] < 'A' || c[i] > 'Z')
			&& (c[i] < '0' || c[i] > '9') && c[i] != '=')
				return (1);
		i++;
	}
	return (0);
}

bool	ft_is_numbalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
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