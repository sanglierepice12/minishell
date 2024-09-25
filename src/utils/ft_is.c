/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 05:46:11 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 05:50:21 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_is_minus(char *c)
{
	if (c[0] == '-' && c[1] == '=')
	{
		printf("minisHell: export: `%s': invalid option\n", c);
		return (0);
	}
	return (1);
}

bool	ft_is_numbalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
		|| (c == '_') || (c == '-'))
		return (1);
	return (0);
}