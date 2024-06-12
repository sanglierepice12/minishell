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

void	ft_dell_node(t_env **temp, t_env **head)
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

	if (!*head)
		return ;
	len = ft_strlen(input);
	temp = *head;
	while (temp && temp->next)
	{
		if (ft_strlen(temp->value) == len && ft_strncmp(temp->value, input, len) == 0)
			return (ft_dell_node(&temp, head), (void)0);
		temp = temp->next;
	}
	if (ft_strlen(temp->value) == len && ft_strncmp(temp->value, input, len) == 0)
		ft_dell_node(&temp, head);
}

void	ft_unset(t_glob *glob, t_input *cmd)
{
	size_t	len;
	size_t	j;

	j = 1;
	len = ft_strlen_double(cmd->argv);
	while (j < len)
	{
		unset_variable(&glob->env, cmd->argv[len]);
		j++;
	}
}