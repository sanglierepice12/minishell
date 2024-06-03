/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:19:11 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/23 17:19:11 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env(t_env **head, int flag)
{
	t_env	*temp;
	if (*head)
	{
		temp = *head;
		while (temp->next)
		{
			if (flag == 0)
			{
				if (temp->flag == 0)
					printf("%s=%s\n", temp->value, temp->path);
			}
			else
			{
				if (temp->flag == 1 && !temp->path)
					printf("declare -x %s\n", temp->value);
				else
					printf("declare -x %s=\"%s\"\n", temp->value, temp->path);
			}
			temp = temp->next;
		}
		if (flag == 0)
		{
			if (temp->flag == 0)
				printf("%s=%s\n", temp->value, temp->path);
		}
		else
		{
			if (temp->flag == 1 && !temp->path)
				printf("declare -x %s\n", temp->value);
			else
				printf("declare -x %s=\"%s\"\n", temp->value, temp->path);
		}
	}
	else
		printf("\n");
}

void	ft_free_lst(t_env **lst)
{
	t_env	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		(*lst)->flag = 0;
		if ((*lst)->path)
			free((*lst)->path);
		if ((*lst)->value)
			free((*lst)->value);
		free(*lst);
		*lst = temp;
	}
	free(*lst);
}

char	*ft_dup(const char *s)
{
	size_t	i;
	char	*new;

	if (!s)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s[++i])
		new[i] = s[i];
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
		env->value = ft_dup(value);
	if (path)
		env->path = ft_dup(path);
	if (flag)
		env->flag = flag;
	env->next = NULL;
	env->prev = NULL;
	return (env);
}
