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

void	ft_swap_nodes(t_env *a, t_env *b)
{
	char	*temp_value;
	char	*temp_path;
	bool	temp_flag;

	temp_value = a->value;
	temp_path = a->path;
	temp_flag = a->flag;

	a->value = b->value;
	a->path = b->path;
	a->flag = b->flag;

	b->value = temp_value;
	b->path = temp_path;
	b->flag = temp_flag;
}

void	bubble_sort(t_env **head)
{
	bool	swapped;
	t_env	*ptr1;
	t_env	*lptr;

	if (*head == NULL)
		return ;
	lptr = NULL;
	swapped = true;
	while (swapped)
	{
		swapped = false;
		ptr1 = *head;
		while (ptr1->next != lptr)
		{
			if (ft_comp_str_for_alpha(ptr1->value, ptr1->next->value) > 0)
			{
				ft_swap_nodes(ptr1, ptr1->next);
				swapped = true;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

t_env	*copy_node(t_env *head)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (fprintf(stderr, "Malloc new node error.\n"), NULL);
	new_node->value = ft_dup(head->value);
	if (head->path)
		new_node->path = ft_dup(head->path);
	else
		new_node->path = NULL;
	new_node->flag = head->flag;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_env	*copy_list(t_env *head)
{
	t_env	*new_head;
	t_env	*current;
	t_env	*new_current;

	if (!head)
		return (NULL);
	new_head = copy_node(head);
	current = head->next;
	new_current = new_head;
	while (current)
	{
		new_current->next = copy_node(current);
		new_current->next->prev = new_current;
		new_current = new_current->next;
		current = current->next;
	}
	return (new_head);
}