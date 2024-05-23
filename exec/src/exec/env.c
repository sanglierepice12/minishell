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

void	ft_filter_env(char **env, t_env *the_env)
{
	char	*value;
	char	*path;
	int	i;
	int j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				path = ft_str_dup(env[i] + j + 1, NULL);
				value = ft_str_copy_n(env[i], j)
			}
			j++;
		}
		i++;
	}
}

void	ft_get_env(t_glob *glob, char **env)
{
	ft_filter_env(env, glob->env);
	/*t_env	*the_env;
	int	i;

	i = 0;
	while (env[i])
	{
		ft_lst_add_back(&the_env, ft_new_node())
	}*/
}