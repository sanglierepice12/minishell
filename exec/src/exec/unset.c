/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:38:04 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/31 14:38:04 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_this_node(t_env *head)
{
	head->flag = 0;
	if (head->path)
		free(head->path);
	if (head->value)
		free(head->value);
	free(head);
}

void	dell_node(t_env **temp, t_env **head)
{
	t_env	*temp_two;

	temp_two = (*temp)->prev;
	if (temp_two)
		temp_two->next = (*temp)->next;
	else
		*head = (*temp)->next;
	if ((*temp)->next)
		(*temp)->next->prev = temp_two;
	ft_free_this_node((*temp));
	*temp = NULL;
}

static void	unset_variable(t_env **head, char *input)
{
	t_env		*temp;
	size_t		len;

	len = ft_strlen(input);
	if (!*head)
		return ;
	temp = *head;
	while (temp && temp->next)
	{
		if (ft_strlen(temp->value) == len && ft_strncmp(temp->value, input, len) == 0)
		{
			dell_node(&temp, head);
			return ;
		}
		temp = temp->next;
	}
	if (ft_strlen(temp->value) == len && ft_strncmp(temp->value, input, len) == 0)
		dell_node(&temp, head);
}

void	ft_unset(t_glob *glob, char *input)
{
	unset_variable(&glob->env, input + 6);
}