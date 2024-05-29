/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 03:43:51 by arbenois          #+#    #+#             */
/*   Updated: 2024/05/29 03:43:52 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_quote(char *str, int len, int *checkquote, char c)
{
	if (str[len] == c && (*checkquote == 1 || *checkquote == 0))
	{
		if (*checkquote == 1)
			*checkquote = 0;
		else
		{
			*checkquote = 1;
			return (1);
		}
	}
	return (0);
}

int	ft_strlen_quote(char *str, int len, int *quote)
{
	int	i;
	int	checkquote;

	checkquote = 0;
	i = 0;
	while (str[len + i])
	{
		if (check_quote(str, len + i, &checkquote, 34) == 1)
			(*quote)++;
		else if (check_quote(str, len + i, &checkquote, 39) == 1)
			(*quote)++;
		if (str[len + i] == ' ' && checkquote == 0)
			break ;
		i++;
	}
	return (i);
}
