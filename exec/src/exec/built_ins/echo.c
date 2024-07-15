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

static void	ft_print_echo(t_input *cmd, int flag, size_t *i)
{
	//size_t	i;
/*
	if (flag)
		*i = 1;
	else
		*i = 0;*/
	while (*i < cmd->args && cmd->argv[*i])
	{
		printf("%s", cmd->argv[*i]);
		if (*i + 1 < cmd->args)
			printf(" ");
		*i = *i + 1;
	}
	if (!flag)
		printf("\n");
}

void	ft_echo(t_input *cmd)
{
	size_t i;
	size_t j;

	if (!cmd->argv)
		return;
	i = 1;
	while (i < cmd->args)
	{
		if (cmd->argv[i][0] == '-' && cmd->argv[i][1] == 'n')
		{
			j = 1;
			while (j++, cmd->argv[i][j] == 'n' && cmd->argv[i][j])
				;
			i++;
			continue ;
		}
		else if (i > 1)
			return (ft_print_echo(cmd, 1, &i), (void)0);
		else
			return(ft_print_echo(cmd, 0, &i), (void)0);
	}

}

/*void	ft_echo(t_input *cmd)
{
	size_t	i;

	if (cmd->args <= 1)
		return (printf("\n"), (void)0);

	*//*if (cmd->argv[1] && !cmd->argv[1][0])
		dprintf(2, "echo%s: command not found\n", cmd->argv[0]);*//*
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
}*/
