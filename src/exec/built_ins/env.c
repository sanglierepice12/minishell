/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:39:13 by gsuter            #+#    #+#             */
/*   Updated: 2024/09/25 18:01:00 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**ft_get_all_path(t_env	**env)
{
	char	**test;
	size_t	len;
	ssize_t	i;
	t_env	*temp;

	if (!env)
		return (ft_err_printf("no env", 1), NULL);
	temp = *env;
	if (!temp)
		return (NULL);
	len = 0;
	ft_get_all_path_follow(temp, &len);
	test = ft_cal_loc(len + 1, sizeof(char *));
	if (!test)
		return (ft_err_printf("error malloc", 1), NULL);
	i = -1;
	while (++i, temp->next)
	{
		if (temp->value)
			test[i] = ft_dup(temp->value);
		temp = temp->next;
	}
	return (test);
}

t_env	*ft_find_thing_in_env(t_env **env, char *value)
{
	t_env	*temp;

	if (!env)
		return (NULL);
	temp = *env;
	while (temp)
	{
		if (ft_comp_str(temp->key, value))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static void	ft_get_first_node(t_glob *glob, char **env)
{
	int		j;

	if (!env)
		return ;
	j = 0;
	while (env[0][j])
	{
		if (env[0][j] == '=')
		{
			ft_copy_env(j, env, glob);
			break ;
		}
		j++;
	}
}

void	ft_get_env(t_glob *glob, char **env)
{
	ft_get_first_node(glob, env);
	if (!glob->env)
		return (ft_err_printf("error malloc", 1));
	if (!env)
		return (ft_err_printf("no env", 1));
	ft_get_env_follow(env, glob);
}

void	ft_env(t_glob *glob, t_input *cmd)
{
	size_t	i;

	g_error_code = 0;
	if (cmd->args == 1)
		return (print_env(&glob->env, 0));
	else if (cmd->args > 1)
	{
		i = 0;
		while (++i, i < cmd->args)
			if (!ft_comp_str(cmd->argv[i], "env"))
				return (ft_derror("env", cmd->argv[1], \
					"no such file or directory", 127));
		if (i == cmd->args)
			print_env(&glob->env, 0);
	}
}
