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
			if (env[j - 1] == '+')
				value = ft_str_copy_n(env, j - 1);
			else
				value = ft_str_copy_n(env, j);
			break ;
		}
		else if (j != 0 && env[j] == '=')
		{
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
		if (ft_str_chr(cmd->argv[j], '='))
		{
			if (temp)
				path = ft_find_value(cmd->argv[j], 1, temp->path);
			else
				path = ft_find_value(cmd->argv[j], 1, NULL);
		}
		else
			path = NULL;
		if (temp)
			ft_dell_node(&temp, env);
		if (flag == 1)
			ft_new_node(value, path, 1);
		else if (!temp && !path)
			ft_lst_add_back(env, ft_new_node(value, path, 1));
		else
			ft_lst_add_back(env, ft_new_node(value, path, 0));
		free(value);
		free(path);
		j++;
	}
}

void	ft_export(t_env **env, t_input *cmd)
{
	t_env	*printer;
	t_env	*tmp;

	if (cmd->args == 1 && env)
	{
		printer = copy_list(*env);
		bubble_sort(&printer);
		print_env(&printer, 1);
		while (printer)
		{
			tmp = printer;
			printer = printer->next;
			free(tmp->value);
			if (tmp->path)
				free(tmp->path);
			free(tmp);
		}
	}
	if (!env)
		ft_create_env_nodes(env, cmd, 1);
	else
		ft_create_env_nodes(env, cmd, 0);
}
