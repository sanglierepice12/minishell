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

#include "../../include/minishell.h"

static void	ft_get_first_node(t_glob *glob, char **env)
{
	char	*value;
	char	*path;
	int	j;

	j = 0;
	while (env[0][j])
	{
		if (env[0][j] == '=')
		{
			path = ft_dup(env[0] + j + 1);
			value = ft_str_copy_n(env[0], j);
			glob->env = ft_new_node(value, path, 0);
			/*	if (!env)
					exit(0);*/
			free(path);
			free(value);
			break;
		}
		j++;
	}
}

void	ft_get_env(t_glob *glob, char **env)
{
	int		i;
	int		j;
	char	*value;
	char	*path;

	ft_get_first_node(glob, env);
	i = 0;
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
			/*	if (!env)
					exit(0);*/
				free(path);
				free(value);
				break ;
			}
			j++;
		}
		i++;
	}
}
