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

#include "../../../include/minishell.h"

static void	ft_print_echo(t_input *cmd, int flag)
{
	size_t	i;

	i = 0;
	while (++i, cmd[0].argv[i])
		printf("%s", cmd[0].argv[i]);
	if (!flag)
		printf("\n");
}

void	ft_echo(t_input *cmd)
{
	size_t	i;

	if (!cmd->argv)
		return ;
	/*if (cmd->argv[1] && !cmd->argv[1][0])
		dprintf(2, "echo%s: command not found\n", cmd->argv[0]);*/
	if (cmd->argv[1][0] == '-' && cmd->argv[1][1] == 'n' && cmd->argv[1][2])
	{
		i = 1;
		while (++i, cmd->argv[1][i] && cmd->argv[1][2] != ' ')
		{
			if (cmd->argv[1][i] != 'n')
				return (ft_print_echo(cmd, 0), (void)0);
		}
		if (!cmd->argv[1][i])
			return ;
		else
			ft_print_echo(cmd, 1);
	}
	else if (cmd->argv[1][0] == '-' && cmd->argv[1][1] == 'n')
		return ;
	else
		ft_print_echo(cmd, 0);
}
