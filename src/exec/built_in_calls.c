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

void	ft_call_builtins(t_glob *glob, t_input cmd)
{
	if (!cmd.args)
		return ;
	if (ft_comp_str(cmd.command, "cd"))
		ft_cd(glob, &cmd);
	if (ft_strncmp(cmd.command, "pwd", 3) == 0)
		ft_pwd(&cmd, &glob->env);
	if (ft_strncmp(cmd.command, "echo", 4) == 0)
		ft_echo(&cmd);
	if (ft_strncmp(cmd.command, "clear", 5) == 0)
		printf("\033[2J\033[H");
	if (ft_comp_str(cmd.command, "env") || ft_comp_str(cmd.command, "printenv"))
		ft_env(glob, &cmd);
	if (ft_strncmp(cmd.command, "unset", 5) == 0)
		ft_unset(glob, &cmd);
	if (ft_strncmp(cmd.command, "export", 6) == 0)
		ft_export(&glob->env, &cmd);
	if (ft_strncmp(cmd.command, "exit", 4) == 0)
		return (ft_exit(glob, &cmd));
	if (ft_strncmp(cmd.command, "exec", 4) == 0)
		ft_init_exec(glob);
}
