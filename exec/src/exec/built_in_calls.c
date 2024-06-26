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

#include "../../include/minishell.h"

void	ft_call(t_glob *glob, t_input *cmd)
{
	if (!cmd->args)
		return ;
	if (ft_comp_str(cmd->command, "cd"))
		ft_cd(glob, &cmd[0]);
	if (ft_strncmp(cmd->command, "pwd", 3) == 0)
		ft_pwd(cmd, &glob->env);
	if (ft_strncmp(cmd->command, "ls", 2) == 0)
		ft_ls();
	if (ft_strncmp(cmd->command, "echo", 4) == 0)
		ft_echo(&cmd[0]);
	if (ft_strncmp(cmd->command, "clear", 5) == 0)
		printf("\033[2J\033[H");
	if (ft_strncmp(cmd->command, "env", 3) == 0)
		ft_env(glob, &cmd[0]);
	if (ft_strncmp(cmd->command, "unset", 5) == 0)
		ft_unset(glob, &cmd[0]);
	if (ft_strncmp(cmd->command, "export", 6) == 0)
		ft_export(&glob->env, &cmd[0]);
	/*if (ft_strncmp(cmd->command, "exit", 4) == 0)
		ft_exit(glob);*/
}
