/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:10:44 by gostr             #+#    #+#             */
/*   Updated: 2024/09/25 17:19:49 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isspace(char c)
{
	if (c == '\n' || c == '\t' || c == '\v' \
		|| c == '\f' || c == '\r' || c == ' ')
		return (0);
	return (1);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *) s)[i] = c;
		i++;
	}
	return (s);
}

int	get_length_num(char *input, unsigned long number)
{
	unsigned long	num_args;
	int				i;

	num_args = 0;
	i = 0;
	if (number == 0)
		return (0);
	while (input[i])
	{
		if (input[i] == '|' && if_in_quote(input, i) == 3)
			num_args++;
		i++;
		if (num_args == number)
			break ;
	}
	return (i);
}
