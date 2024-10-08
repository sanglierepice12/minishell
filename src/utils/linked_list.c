/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:19:11 by gsuter            #+#    #+#             */
/*   Updated: 2024/10/08 19:21:12 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_dup(const char *s)
{
	size_t	i;
	char	*new;

	if (!s)
		return (NULL);
	new = ft_cal_loc(sizeof(char), ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

t_env	*ft_lst_last(t_env *lst)
{
	t_env	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_lst_add_front(t_env **lst, t_env *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_lst_add_back(t_env **head, t_env *new)
{
	t_env	*last;

	if (*head)
	{
		last = ft_lst_last(*head);
		last->next = new;
		new->prev = last;
	}
	else
		*head = new;
}

t_env	*ft_new_node(char *value, char *path, bool flag)
{
	t_env	*env;

	env = ft_cal_loc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	if (value)
		env->key = ft_dup(value);
	if (path)
		env->value = ft_dup(path);
	if (flag)
		env->flag = flag;
	env->next = NULL;
	env->prev = NULL;
	return (env);
}
