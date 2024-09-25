/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_node_follow.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:35:09 by gsuter            #+#    #+#             */
/*   Updated: 2024/09/25 20:35:09 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_create_env_follow(t_export *export, t_input *cmd)
{
	if (ft_str_chr(cmd->argv[export->j], '='))
	{
		export->equal = 1;
		if (export->temp)
			export->path = ft_find_value(cmd->argv[export->j], 1, \
				export->temp->value, export);
		else
			export->path = ft_find_value(cmd->argv[export->j], 1, NULL, export);
	}
	else
		export->path = NULL;
}

bool	ft_existant_key(t_export *export, t_env **env)
{
	if (export->temp && export->equal == 1)
		ft_dell_node(&export->temp, env);
	else if (export->temp)
	{
		if (export->value)
			free(export->value);
		return (free(export->path), 1);
	}
	return (0);
}
