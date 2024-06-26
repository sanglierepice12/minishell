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

	if (flag)
		i = 1;
	else
		i = 0;
	while (++i, i < cmd->args && cmd->argv[i])
		printf("%s", cmd->argv[i]);
	if (!flag)
		printf("\n");
}

void	ft_echo(t_input *cmd)
{
	size_t	i;

	if (cmd->args <= 1)
		return (printf("\n"), (void)0);
	if (ft_comp_str(cmd->argv[1], "-n") && cmd->args <= 2)
		return ;
	/*if (cmd->argv[1] && !cmd->argv[1][0])
		dprintf(2, "echo%s: command not found\n", cmd->argv[0]);*/
	if (cmd->argv[1][0] == '-' && cmd->argv[1][1] == 'n')
	{
		i = 1;
		while (++i, cmd->argv[1][i])
		{
			if (cmd->argv[1][i] != 'n')
				return (ft_print_echo(cmd, 0), (void)0);
		}
		if (!cmd->argv[1][i] && cmd->args <= 2)
			return ;
		else
			ft_print_echo(cmd, 1);
		return ;
	}
	else
		ft_print_echo(cmd, 0);
}
