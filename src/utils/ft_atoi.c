/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:22:22 by arbenois          #+#    #+#             */
/*   Updated: 2024/10/09 15:25:54 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_isdigit(int nb)
{
	if (nb > 47 && nb < 58)
		return (1);
	return (0);
}

int	ft_atoi_bis(const char *str)
{
	int			result;
	ssize_t		i;
	int			minus;

	minus = 1;
	i = -1;
	result = 0;
	while (++i, (str[i] > 8 && str[i] < 14) || str[i] == 32)
		;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	if (ft_isdigit(str[i]) == 0)
		return (0);
	while (str[i] && ft_isdigit(str[i]) == 1)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * minus);
}
