/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:39:13 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/23 16:39:13 by gsuter           ###   ########.fr       */
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
	len = 0;
	while (temp->next)
	{
		if (temp->path)
			len += 1;
		temp = temp->next;
	}
	while (temp->prev)
		temp = temp->prev;
	test = ft_cal_loc(len + 1, sizeof(char *));
	if (!test)
		return (ft_err_printf("error malloc", 1), NULL);
	i = -1;
	while (++i, temp->next)
	{
		if (temp->path)
			test[i] = ft_dup(temp->path);
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
		if (ft_comp_str(temp->value, value))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static void	ft_get_first_node(t_glob *glob, char **env)
{
	char	*value;
	char	*path;
	int		j;

	if (!env)
		return ;
	j = 0;
	while (env[0][j])
	{
		if (env[0][j] == '=')
		{
			path = ft_dup(env[0] + j + 1);
			if (!path)
				return (ft_err_printf("error malloc", 1));
			value = ft_str_copy_n(env[0], j);
			if (!value)
				return (ft_err_printf("error malloc", 1));
			glob->env = ft_new_node(value, path, 0);
			free(path);
			free(value);
			break ;
		}
		j++;
	}
}

void	ft_get_env(t_glob *glob, char **env)
{
	int			i;
	int			j;
	char		*value;
	char		*path;
	t_env		*temp;

	ft_get_first_node(glob, env);
	if (!env)
		return (ft_err_printf("no env", 1));
	i = 1;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				path = ft_dup(env[i] + j + 1);
				if (!path)
					return (ft_err_printf("error malloc", 1));
				value = ft_str_copy_n(env[i], j);
				if (!value)
					return (ft_err_printf("error malloc", 1));
				ft_lst_add_back(&glob->env, ft_new_node(value, path, 0));
				free(path);
				free(value);
				break ;
			}
			j++;
		}
		i++;
	}
	temp = glob->env;
	if (!ft_find_thing_in_env(&temp, "PATH"))
		ft_main_get_env(glob);
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
