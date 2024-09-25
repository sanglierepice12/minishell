/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:39:16 by gsuter            #+#    #+#             */
/*   Updated: 2024/09/23 05:47:25 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_chk_expt_args(char *cmd, size_t	flag, t_valuef *var, char *env)
{
	if (!ft_is_numbalpha(cmd[0]) && !flag)
	{
		ft_env_derror("export", env, "not a valid identifier", 1);
		var->k = var->k + 1;
		return ;
	}
	if (ft_export_is_printable(cmd))
	{
		ft_env_derror("export", env, "not a valid identifier", 1);
		var->k = var->k + 1;
		return ;
	}
	if (ft_comp_str(cmd, "="))
	{
		ft_env_derror("export", env, "not a valid identifier", 1);
		var->k = var->k + 1;
		return ;
	}
}

char	*ft_find_value(char *env, int flag, char *temp, t_export *export)
{
	t_valuef	var;

	ft_find_value_init(&var, flag, env, export);
	while (var.i++, env[var.i])
	{
		if (var.len > 1 && env[var.i + 1] && env[var.i] == '=' && !var.flag)
		{
			if (env[var.i - 1] == '+')
				var.value = ft_str_copy_n(env, var.i - 1);
			else
				var.value = ft_str_copy_n(env, var.i);
			ft_chk_expt_args(var.value, var.flag, &var, env);
			break ;
		}
		else if (var.i != 0 && env[var.i] == '=')
		{
			ft_equal_value(&var, temp, env, export);
			break ;
		}
	}
	ft_double_check_arg(&var, env);
	return (export->j = var.k, var.value);
}

static void	ft_create_env_nodes_follow(t_export *export)
{
	if (export->value)
		free(export->value);
	if (export->path)
		free(export->path);
	export->j++;
}

static void	ft_create_env_nodes(t_env **env, t_input *cmd, int flag)
{
	t_export	export;

	export.j = 1;
	export.equal = 0;
	while (export.j <= cmd->args - 1)
	{
		export.j_copy = export.j;
		export.value = ft_find_value(cmd->argv[export.j], 0, NULL, &export);
		if (export.j_copy + 1 == export.j)
		{
			free(export.value);
			continue ;
		}
		export.temp = ft_find_thing_in_env(env, export.value);
		ft_create_env_follow(&export, cmd);
		if (ft_existant_key(&export, env))
			return ;
		if (flag == 1 && export.j == 1)
			ft_new_node(export.value, export.path, 1);
		else if (!export.temp && !export.path)
			ft_lst_add_back(env, ft_new_node(export.value, export.path, 1));
		else
			ft_lst_add_back(env, ft_new_node(export.value, export.path, 0));
		ft_create_env_nodes_follow(&export);
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
			free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
		}
	}
	if (!env)
		ft_create_env_nodes(env, cmd, 1);
	else
		ft_create_env_nodes(env, cmd, 0);
}
