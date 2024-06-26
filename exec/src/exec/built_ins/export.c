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

static void	ft_check_export_args(t_input *cmd, size_t *j)
{
	if (!ft_is_numbalpha(cmd->argv[*j][0]))
	{
		printf("bash: export: `%s': not a valid identifier\n",
				cmd->argv[*j]);
		*j = *j + 1;
		return ;
	}
	if (ft_export_is_printable(cmd->argv[*j]))
	{
		printf("bash: export: `%s': not a valid identifier\n",
				cmd->argv[*j]);
		*j = *j + 1;
		return ;
	}
	if (ft_comp_str(cmd->argv[*j], "="))
	{
		printf("bash: export: `%s': not a valid identifier\n",
				cmd->argv[*j]);
		*j = *j + 1;
		return;
	}
}

static char	*ft_find_value(char *env, int flag, char *temp)
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
		else if (j != 0 && env[j] == '=')
		{
			printf("coucou = %s\n", env);
			if (env[j - 1] == '+' && temp)
				value = ft_str_join(env + j + 1, temp);
			else
				value = ft_dup(env + j + 1);
			break ;
		}
		j++;
	}
	if (!env[j])
		value = ft_dup(env);
	return (value);
}

static void	ft_create_env_nodes(t_env **env, t_input *cmd, int flag)
{
	size_t	j;
	char	*value;
	char	*path;
	t_env	*temp;

	j = 1;
	while (j <= cmd->args - 1)
	{
		ft_check_export_args(cmd, &j);
		if (j + 1 > cmd->args)
			return ;
		value = ft_find_value(cmd->argv[j], 0, NULL);
		temp = ft_find_thing_in_env(env, value);
		/*if (!temp->value)
			temp->value = strdup("");*/
		if (ft_str_chr(cmd->argv[j], '='))
			path = ft_find_value(cmd->argv[j], 1, "BITE");
		else
			path = NULL;
		if (temp)
			ft_dell_node(&temp, env);
		if (flag == 1)
			ft_new_node(value, path, 1);
		else
			ft_lst_add_back(env, ft_new_node(value, path, 1));
		printf("pa = %s\n", path);
		free(value);
		free(path);
		j++;
	}
}

void	ft_export(t_env **env, t_input *cmd)
{
	if (cmd->args == 1 && env)
		return (print_env(env, 1), (void)0);
	if (!env)
		ft_create_env_nodes(env, cmd, 1);
	else
		ft_create_env_nodes(env, cmd, 0);
	//ft_atoz_env(env);
}
