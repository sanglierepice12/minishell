/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:01:38 by gsuter            #+#    #+#             */
/*   Updated: 2024/08/29 20:34:56 by arbenois         ###   ########.fr       */
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
			return ;
		}
		temp = temp->next;
	}
	ft_lst_add_back(env, ft_new_node("OLDPWD", path, 0));
}

void	ft_update_pwd(t_env **env, char *value, char *path)
{
	t_env	*temp;

	if (!*env)
		return (perror("minisHell"), (void)0);
	if (!path)
	{
		temp = *env;
		temp = ft_find_thing_in_env(&temp, "PWD");
		path = ft_dup(temp->path);
		if (!path)
			return (perror("minisHell PWD"), (void) 0);
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
	temp = *env;
	if (!ft_find_thing_in_env(&temp, "PWD"))
		ft_lst_add_back(env, ft_new_node("PWD", getcwd(NULL, 0), 0));
}

void	ft_cd(t_glob *glob, t_input *cmd)
{
	t_env	*temp;
	char	*gcp;

	g_error_code = 0;
	if (!cmd->args)
		return (printf("no argv \n"), (void)0);
	if (cmd->args > 2)
		return (ft_err_printf("minisHell: cd: too many arguments", 1));
	if (cmd->args == 1 || ft_comp_str(cmd->argv[1], "~") || \
			ft_comp_str(cmd->argv[1], "--"))
		return (chdir("/"), ft_update_pwd(&glob->env, \
			"PWD", getcwd(NULL, 0)));
	else if (ft_comp_str(cmd->argv[1], "-"))
	{
		temp = ft_find_thing_in_env(&glob->env, "OLDPWD");
		if (temp)
		{
			if (chdir(temp->path) != 0)
				ft_derror("cd", temp->path, "No such file or directory", 1);
			else
			{
				gcp = getcwd(NULL, 0);
				printf("%s\n", gcp);
				free(gcp);
			}
		}
		else
			ft_lst_add_back(&glob->env, ft_new_node("PWD", getcwd(NULL, 0), 0));
	}
	else if (cmd->argv[1][0] == '-')
	{
		if (cmd->argv[1][1] != 'L' && cmd->argv[1][1] != 'P')
		{
			g_error_code = 2;
			dprintf(2, "minisHell: cd: %c%c: invalid option\n" \
					"cd: usage: [-L|[-P [-e]] [-@]] [dir]\n", \
						cmd->argv[1][0], cmd->argv[1][1]);
		}
		else
			chdir("~");
	}
	else
	{
		if (chdir(cmd->argv[1]) != 0)
			ft_derror("cd", cmd->argv[1], "No such file or directory", 1);
	}
	ft_update_pwd(&glob->env, "PWD", getcwd(NULL, 0));
}
