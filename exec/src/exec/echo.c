/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:03:59 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/23 16:03:59 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(char *dup)
{
	size_t	i;

	if (dup[0] && dup[0] != ' ')
	{
		dprintf(2, "echo%s: command not found\n", dup);
		return;
	}
	if (dup[1] == '-' && dup[2] == 'n' && dup[3])
	{
		i = 3;
		while (++i, dup[i] && dup[3] != ' ')
		{
			if (dup[i] != 'n')
				return((printf("%s\n", dup + 1), (void)0));
		}
		if (!dup[i])
			return ;
		else
			printf("%s", dup + 4);
	}
	else if (dup[1] == '-' && dup[2] == 'n' && !dup[3])
		return ;
	else
		printf("%s\n", dup + 1);
}