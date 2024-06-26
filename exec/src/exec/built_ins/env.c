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
			value = ft_str_copy_n(env[0], j);
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

	ft_get_first_node(glob, env);
	if (!env)
		return (dprintf(2, "No env\n"), (void)0);
	i = 1;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				path = ft_dup(env[i] + j + 1);
				value = ft_str_copy_n(env[i], j);
				ft_lst_add_back(&glob->env, ft_new_node(value, path, 0));
				free(path);
				free(value);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	ft_env(t_glob *glob, t_input *cmd)
{
	size_t	i;
	if (cmd->args == 1)
		return (print_env(&glob->env, 0), (void)0);
	else if (cmd->args > 1)
	{
		i = 0;
		while (++i, i < cmd->args)
		{
			if (!ft_comp_str(cmd->argv[i], "env"))
				return (printf("env: ‘%s’: No such file or directory\n",\
							cmd->argv[1]), (void)0);
		}
		if (i == cmd->args)
			print_env(&glob->env, 0);
	}
}