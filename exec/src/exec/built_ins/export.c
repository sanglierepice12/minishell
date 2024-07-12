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

static void	ft_check_export_args(char *cmd, size_t	flag, size_t *j)
{
	if (!ft_is_numbalpha(cmd[0]) && !flag)
	{
		printf("bash: export: `%s': not a valid identifier\n", \
				cmd);
		*j = *j + 1;
		return ;
	}
	if (ft_export_is_printable(cmd))
	{
		printf("bash: export: `%s': not a valid identifier\n", \
				cmd);
		*j = *j + 1;
		return ;
	}
	if (ft_comp_str(cmd, "="))
	{
		printf("bash: export: `%s': not a valid identifier\n", \
				cmd);
		*j = *j + 1;
		return ;
	}
}

static char	*ft_find_value(char *env, int flag, char *temp, size_t *j)
{
	size_t	i;
	char	*value;

	value = NULL;
	i = 0;
	while (env[i])
	{
		if (env[i] == '=' && !flag)
		{
			if (env[i - 1] == '+')
				value = ft_str_copy_n(env, i - 1);
			else
				value = ft_str_copy_n(env, i);
			ft_check_export_args(value, flag, j);
			break ;
		}
		else if (i != 0 && env[i] == '=')
		{
			if (env[i - 1] == '+' && temp)
				value = ft_str_join(env + i + 1, temp);
			else
				value = ft_dup(env + i + 1);
			break ;
		}
		i++;
	}
	if (!env[i])
		value = ft_dup(env);
	return (value);
}

static void	ft_create_env_nodes(t_env **env, t_input *cmd, int flag)
{
	size_t	j;
	size_t	j_copy;
	char	*value;
	char	*path;
	t_env	*temp;

	j = 1;
	while (j <= cmd->args - 1)
	{
		j_copy = j;
		value = ft_find_value(cmd->argv[j], 0, NULL, &j);
		if (j_copy + 1 == j)
			continue ;
		temp = ft_find_thing_in_env(env, value);
		if (ft_str_chr(cmd->argv[j], '='))
		{
			if (temp)
				path = ft_find_value(cmd->argv[j], 1, temp->path, &j);
			else
				path = ft_find_value(cmd->argv[j], 1, NULL, &j);
		}
		else
			path = NULL;
		if (j_copy + 1 == j)
			continue ;
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
