/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 05:48:15 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 05:49:03 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_env_var(t_env *temp, int flag)
{
	if (flag == 0)
	{
		if (temp->flag == 0)
			printf("%s=%s\n", temp->key, temp->value);
	}
	else
	{
		if (temp->flag == 1 && !temp->value)
			printf("declare -x %s\n", temp->key);
		else
			printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
	}
}

void	print_env(t_env **head, int flag)
{
	t_env	*temp;

	if (!*head)
	{
		printf("\n");
		return ;
	}
	temp = *head;
	while (temp->next)
	{
		print_env_var(temp, flag);
		temp = temp->next;
	}
	print_env_var(temp, flag);
}
