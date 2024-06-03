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

void	ft_echo(char *input)
{
	size_t	i;

	if (input && input[0] && input[0] != ' ')
	{
		dprintf(2, "echo%s: command not found\n", input);
		return ;
	}
	if (input && input[1] == '-' && input[2] == 'n' && input[3])
	{
		i = 3;
		while (++i, input[i] && input[3] != ' ')
		{
			if (input[i] != 'n')
				return ((printf("%s\n", input + 1), (void)0));
		}
		if (!input[i])
			return ;
		else
			printf("%s", input + 4);
	}
	else if (input[1] == '-' && input[2] == 'n' && !input[3])
		return ;
	else
		printf("%s\n", input + 1);
}
