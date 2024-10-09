/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:01:38 by gsuter            #+#    #+#             */
/*   Updated: 2024/10/09 15:07:26 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_get_pwd_path(t_env **env, char *path)
{
	t_env	*temp;

	if (!path)
	{
		temp = ft_find_thing_in_env(env, "PWD");
		if (!temp)
			return (NULL);
		path = ft_dup(temp->value);
		if (!path)
		{
			perror("minisHell");
			return (NULL);
		}
	}
	return (path);
}

void	ft_update_pwd(t_env **env, char *value, char *path)
{
	t_env	*temp;

	if (!*env)
		return (perror("minisHell"), (void)0);
	path = ft_get_pwd_path(env, path);
	if (!path)
		return ;
	temp = *env;
	while (temp)
	{
		if (ft_comp_str(temp->key, value))
		{
			ft_update_env_value(temp, path, env);
			free(path);
			path = NULL;
			break ;
		}
		temp = temp->next;
	}
	if (!ft_find_thing_in_env(env, "PWD"))
		ft_lst_add_back(env, ft_new_node("PWD", path, 0));
	if (path)
		free(path);
}

void	ft_cd_to_oldpwd(t_glob *glob)
{
	t_env	*temp;
	char	*gcp;

	temp = ft_find_thing_in_env(&glob->env, "OLDPWD");
	if (!temp)
		return (ft_lst_add_back(&glob->env, \
			ft_new_node("PWD", getcwd(NULL, 0), 0)));
	if (chdir(temp->value) != 0)
		ft_derror("cd", temp->value, "No such file or directory", 1);
	else
	{
		gcp = getcwd(NULL, 0);
		printf("%s\n", gcp);
		free(gcp);
	}
}

void	ft_cd_handle_invalid_option(t_input *cmd)
{
	g_error_code = 2;
	dprintf(2, "minisHell: cd: %c%c: invalid option\n"
		"cd: usage: [-L|[-P [-e]] [-@]] [dir]\n" \
		, cmd->argv[1][0], cmd->argv[1][1]);
}

void	ft_cd(t_glob *glob, t_input *cmd)
{
	char	*get;

	get = NULL;
	g_error_code = 0;
	if (cmd->args > 2)
		return (ft_err_printf("minisHell: cd: too many arguments", 1));
	if (cmd->args == 1 || ft_comp_str(cmd->argv[1], "~") \
		|| ft_comp_str(cmd->argv[1], "--"))
	{
		get = getcwd(NULL, 0);
		chdir("/");
	}
	else if (ft_comp_str(cmd->argv[1], "-"))
		ft_cd_to_oldpwd(glob);
	else if (cmd->argv[1][0] == '-' && (cmd->argv[1][1] != 'L' \
		&& cmd->argv[1][1] != 'P'))
		ft_cd_handle_invalid_option(cmd);
	else
	{
		if (chdir(cmd->argv[1]) != 0)
			ft_derror("cd", cmd->argv[1], "No such file or directory", 1);
		get = getcwd(NULL, 0);
	}
	ft_update_pwd(&glob->env, "PWD", get);
}
