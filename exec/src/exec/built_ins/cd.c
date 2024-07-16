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

#include "../../../include/minishell.h"

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

	if (!*env)
		return (perror("MinisHell"), (void)0);
	if (!path)
	{
		temp = *env;
		temp = ft_find_thing_in_env(&temp, "PWD");
		path = ft_dup(temp->path);
		if (!path)
			return (perror("MinisHell PWD"), (void) 0);
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
	t_env	*temp;

	if (!cmd->args)
		return (printf("pas dargv \n"), (void)0);
	if (cmd->args == 1 || ft_comp_str(cmd->argv[1], "~") || \
			ft_comp_str(cmd->argv[1], "--"))
		return (chdir("/"), ft_update_pwd(&glob->env, \
			"PWD", getcwd(NULL, 0)), (void) 0);
	else if (ft_comp_str(cmd->argv[1], "-"))
	{
		temp = ft_find_thing_in_env(&glob->env, "OLDPWD");
		if (temp)
		{
			if (chdir(temp->path) != 0)
				dprintf(2, "MinisHell: cd: %s: No such file or directory\n", \
					temp->path);
		}
		else
			printf("MinisHell: cd: OLDPWD not set\n");
	}
	else if (cmd->argv[1][0] == '-')
	{
		if (cmd->argv[1][1] != 'L' && cmd->argv[1][1] != 'P')
		{
			dprintf(2, "MinisHell: cd: %c%c: invalid option\n" \
					"cd: usage: [-L|[-P [-e]] [-@]] [dir]\n", \
						cmd->argv[1][0], cmd->argv[1][1]);
		}
		else
			chdir("~");
	}
	else
	{
		if (chdir(cmd->argv[1]) != 0)
			dprintf(2, "MinisHell: cd: %s: No such file or directory\n", \
				cmd->argv[1]);
	}
	ft_update_pwd(&glob->env, "PWD", getcwd(NULL, 0));
}
