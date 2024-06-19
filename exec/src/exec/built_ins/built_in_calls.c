/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_calls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:53:07 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/21 17:53:07 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
void	ft_pwd_call(t_glob *glob, char *dup)
{
	if (dup[4] && dup[4] == '-' && dup[5])
		dprintf(2, "bash: pwd: %c%c: invalid option\n"
			"pwd: usage: pwd [-LP]\n", dup[4], dup[5]);
	else if (dup[3] && dup[3] != ' ')
		dprintf(2, "Command : '%s' not found, did you mean: pwd ?\n", dup);
	else
	{
		ft_pwd(&glob->build);
		printf("%s\n", glob->build.pwd);
		free(glob->build.pwd);
	}
}
*/

/*void	ft_pwd_call(t_glob *glob, t_input *cmd)
{
	if (cmd->argv[1][4] && cmd->argv[1][4] == '-' && cmd->argv[1][5])
		dprintf(2, "bash: pwd: %c%c: invalid option\n"
				   "pwd: usage: pwd [-LP]\n", cmd->argv[1][4], cmd->argv[1][5]);
	else if (cmd->argv[1][3] && cmd->argv[1][3] != ' ')
		dprintf(2, "Command : '%s' not found, did you mean: pwd ?\n", cmd->argv[1]);
	else
	{
		ft_pwd(&glob->build);
		printf("%s\n", glob->build.pwd);
		free(glob->build.pwd);
	}
}*/

void	ft_call(t_glob *glob, t_input *cmd)
{
	if (!cmd->args)
		return ;
	if (ft_strncmp(cmd->command, "cd", 2) == 0)
		ft_cd(glob, cmd);
	if (ft_strncmp(cmd->command, "pwd", 3) == 0)
		ft_pwd(cmd, &glob->env);
	if (ft_strncmp(cmd->command, "ls", 2) == 0)
		ft_ls();
	if (ft_strncmp(cmd->command, "echo", 4) == 0)
		ft_echo(cmd);
	if (ft_strncmp(cmd->command, "clear", 5) == 0)
		printf("\033[2J\033[H");
	if (ft_strncmp(cmd->command, "env", 3) == 0)
		print_env(&glob->env, 0);
	if (ft_strncmp(cmd->command, "unset", 5) == 0)
		ft_unset(glob, cmd);
	if (ft_strncmp(cmd->command, "export", 6) == 0)
		ft_export(&glob->env, cmd);
}
