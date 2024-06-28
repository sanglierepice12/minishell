/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_follow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostr <gostr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:04:40 by gostr             #+#    #+#             */
/*   Updated: 2024/06/28 11:04:40 by gostr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_change_node(t_env **temp, char *value, char *path)
{
	t_env	*temp2;

	temp2 = *temp;
	if (temp2->path)
		free(temp2->path);
	if (temp2->value)
		free(temp2->value);
	temp2->value = ft_dup(value);
	temp2->path = ft_dup(path);
}