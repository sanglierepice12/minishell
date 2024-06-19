/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:39:16 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/31 17:39:16 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*ft_find_value(char *env, int flag)
{
	size_t	j;
	char	*value;

	value = NULL;
	j = 0;
	while (env[j])
	{
		if (env[j] == '=' && !flag)
		{
			value = ft_str_copy_n(env, j);
			break ;
		}
		else if (env[j] == '=')
		{
			value = ft_dup(env + j + 1);
			break ;
		}
		j++;
	}
	return (value);
}

static void	ft_create_env_nodes(t_env **env, t_input *cmd, int flag)
{
	size_t	len;
	size_t	j;
	char	*value;
	char	*path;

	value = ft_find_value(cmd->argv[1], 0);
	path = ft_find_value(cmd->argv[1], 1);
	len = ft_strlen_double(cmd->argv);
	j = 1;
	if (flag == 1)
		ft_new_node(value, path, 1);
	free(value);
	free(path);
	while (j < len)
	{
		value = ft_find_value(cmd->argv[j], 0);
		path = ft_find_value(cmd->argv[j], 1);
		ft_lst_add_back(env, ft_new_node(value, path, 1));
		free(value);
		free(path);
		j++;
	}
}

void	ft_export(t_env **env, t_input *cmd)
{
	if (!cmd->argv[1])
		print_env(env, 1);
	else if (!env)
		ft_create_env_nodes(env, cmd, 1);
	else
		ft_create_env_nodes(env, cmd, 0);
	//ft_tri env
}
