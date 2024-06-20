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
	if (!cmd->argv[0])
		return (printf("pas dargv \n"), (void)0);
	if (!cmd->argv[1])
		return (chdir("~"), (void) 0);
	/*if (cmd->argv[1])
	{
		*//*if (cmd->argv[1][0] == '-' && cmd->argv[1][1] == '-')
			chdir("~");*//*
		if (ft_comp_str(cmd->argv[1], "--"))
			chdir("~");
		*//*else if (cmd->argv[1][0] == '~' && !cmd->argv[1][1])
			chdir("/");*//*
		else if (ft_comp_str(cmd->argv[1], "~"))
			chdir("/");
		else if (ft_comp_str(cmd->argv[1], "-"))
		{
			ft_find_thing_in_env(&glob->env, "OLDPWD");
			printf("%s\n", glob->env->path);
			*//*getcwd(glob->env->path, 0);*//*
			//printf("bash: cd: OLDPWD not set\n");
		}
		//dprintf(2, "bash: cd: %c%c: invalid option\n"
		//	"cd: usage: [-L|[-P [-e]] [-@]] [dir]\n", cmd->argv[1][0], cmd->argv[1][1]);}
	}*/
	if (chdir(cmd->argv[1]) != 0)
		dprintf(2, "bash: cd: %s: No such file or directory\n", cmd->argv[1]);
	ft_update_pwd(&glob->env, "PWD", getcwd(NULL, 0));
}
