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
		value = ft_find_value(cmd->argv[j], 0);
		temp = *env;
		temp = ft_find_thing_in_env(env, value);
		if (temp)
			ft_dell_node(&temp, env);
		if (ft_str_chr(cmd->argv[j], '='))
			path = ft_find_value(cmd->argv[j], 1);
		else
			path = NULL;
		if (flag == 1)
			ft_new_node(value, path, 1);
		else
			ft_lst_add_back(env, ft_new_node(value, path, 1));
		free(value);
		free(path);
		j++;
	}
}

void	ft_swap_nodes(t_env **temp, t_env **head)
{
	t_env	*temp_two;
	t_env	*head_temp;

	temp_two = (*temp)->prev;
	head_temp = (*head)->prev;
	while (head_temp->next)
	{
		if (!ft_comp_str(temp_two->value, head_temp->value))
		{
			head_temp->prev = temp_two->prev->next;
			head_temp->prev->next = head_temp->prev;
			temp_two->next = head_temp->next;
			temp_two->next->prev = temp_two->next;
			head_temp->next = temp_two->prev;
			temp_two->prev = head_temp->next;
		}
	}
}

void	ft_atoz_env(t_env **env)
{
	t_env	*temp;
	size_t	i;

	temp = *env;
	i = 0;
	while (temp->next)
	{
		if (temp->value[i] > temp->next->value[i])
			ft_swap_nodes(&temp, env);
		i++;
	}
}

void	ft_export(t_env **env, t_input *cmd)
{
	size_t	i;

	if (cmd->args == 1 && env)
		print_env(env, 1);
	else if (cmd->args > 1)
	{
		i = 1;
		while (i < cmd->args)
		{
			if (ft_comp_str(cmd->argv[i], "="))
			{
				printf("bash: export: `%s': not a valid identifier\n",
					   cmd->argv[i]);
				return;
			}
			i++;
		}
	}
	if (!env)
		ft_create_env_nodes(env, cmd, 1);
	else
		ft_create_env_nodes(env, cmd, 0);
	ft_atoz_env(env);
}
