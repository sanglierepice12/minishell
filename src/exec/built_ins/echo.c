/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:03:59 by gsuter            #+#    #+#             */
/*   Updated: 2024/09/25 15:52:47 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ft_print_echo(t_input *cmd, int flag, size_t *i)
{
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

static int	ft_check_flag(t_input *cmd, size_t *i, int *flag)
{
	size_t	j;

	j = 1;
	while (cmd->argv[*i][j] == 'n' && cmd->argv[*i][j])
		j++;
	if (cmd->argv[*i][j])
	{
		*flag = 0;
		return (0);
	}
	*i += 1;
	return (1);
}

void	ft_echo(t_input *cmd)
{
	size_t	i;
	int		flag;

	if (!cmd->argv)
		return (g_error_code = 0, (void)0);
	if (!cmd->argv[1])
		return (g_error_code = 0, printf("\n"), (void)0);
	flag = 1;
	i = 1;
	while (i < cmd->args)
	{
		if (cmd->argv[i][0] == '-' && cmd->argv[i][1] == 'n' && flag)
			ft_check_flag(cmd, &i, &flag);
		else if (i > 1)
			return (ft_print_echo(cmd, 1, &i), g_error_code = 0, (void) 0);
		else
			return (ft_print_echo(cmd, 0, &i), g_error_code = 0, (void) 0);
	}
}
