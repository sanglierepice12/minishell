/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:01:38 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/23 16:01:38 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_update_old_pwd(t_env **env, char *value, char *path)
{
	t_env	*temp;

	if (!*env)
		return ;
	temp = *env;
	while (temp)
	{
		if (ft_comp_str(temp->value, value))
		{
			if (temp->path)
				free(temp->path);
			temp->path = ft_dup(path);
			break ;
		}
		temp = temp->next;
	}
}

void	ft_update_pwd(t_env **env, char *value, char *path)
{
	t_env	*temp;

	if (!*env || !path)
	{
		perror("PWD : error\n");
		return;
	}
	temp = *env;
	while (temp)
	{
		if (ft_comp_str(temp->value, value))
		{
			if (temp->path[0])
			{
				ft_update_old_pwd(env, "OLDPWD", temp->path);
				free(temp->path);
			}
			temp->path = ft_dup(path);
			free(path);
			break ;
		}
		temp = temp->next;
	}
}

void	ft_cd(t_glob *glob, t_input *cmd)
{
	if (cmd->argv[1][3] == '-' && cmd->argv[1][4] == '-')
		chdir("~");
	else if (!cmd->argv[1][2] || (cmd->argv[1][3] == '~' && !cmd->argv[1][4]))
		chdir("/");
	else if (cmd->argv[1][3] == '-' && cmd->argv[1][4] != '-')
		dprintf(2, "bash: cd: %c%c: invalid option\n"
			"cd: usage: [-L|[-P [-e]] [-@]] [dir]\n", cmd->argv[1][3], cmd->argv[1][4]);
	else if (chdir(cmd->argv[1]) != 0)
	{
		perror("bash: cd");
		dprintf(2, "bash: cd: %s: No such file or directory\n", cmd->argv[1] + 3);
	}
	ft_update_pwd(&glob->env, "PWD", getcwd(NULL, 0));
}
