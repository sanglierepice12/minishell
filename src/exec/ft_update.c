/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:08:37 by arbenois          #+#    #+#             */
/*   Updated: 2024/10/08 19:14:49 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_update_old_pwd(t_env **env, char *value, char *path)
{
	t_env	*temp;

	if (!*env)
		return ;
	temp = *env;
	while (temp)
	{
		if (ft_comp_str(temp->key, value))
		{
			if (temp->value)
				free(temp->value);
			temp->value = ft_dup(path);
			return ;
		}
		temp = temp->next;
	}
	ft_lst_add_back(env, ft_new_node("OLDPWD", path, 0));
}

void	ft_update_env_value(t_env *temp, char *path, t_env **env)
{
	if (temp->value[0])
	{
		ft_update_old_pwd(env, "OLDPWD", temp->value);
		free(temp->value);
	}
	temp->value = ft_dup(path);
}
