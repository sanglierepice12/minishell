/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_followed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:10:29 by gsuter            #+#    #+#             */
/*   Updated: 2024/09/25 19:10:29 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_double_check_arg(t_valuef *var, char *env)
{
	if (!env[var->i] && !var->value)
	{
		var->value = ft_dup(env);
		ft_chk_expt_args(var->value, var->flag, var, env);
	}
}

void	ft_find_value_init(t_valuef *var, int flag, char *env, t_export *export)
{
	var->flag = flag;
	var->len = ft_strlen(env);
	var->k = export->j;
	var->value = NULL;
	var->i = -1;
}

void	ft_equal_value(t_valuef *var, char *temp, char *env, t_export *export)
{
	if (env[var->i - 1] == '+' && temp)
		var->value = ft_str_join(env + var->i + 1, temp);
	else
		var->value = ft_dup(env + var->i + 1);
	if (env[var->i - 1] == '-' && !var->flag)
	{
		ft_env_derror("export", env, "invalid option", 2);
		printf("export: usage: export \\"
			"[-fn] [name[=value] ...] or export -p \n");
		var->k += 1;
		export->j = var->k;
	}
}
