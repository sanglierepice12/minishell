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

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_env
{
	char	*value;
	char	*path;
	bool	flag;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

void    print_lst(t_env **head)
{
	t_env        *temp;
	size_t  i;

	i = 0;
	if (*head)
	{
		temp = *head;
		while (temp->next)
		{
			printf("Elem n'%zu: %s \npath : %s\n"
				   "flag : %d\n", i, temp->value, temp->path, temp->flag);
			temp = temp->next;
			i++;
		}
		printf("Elem n'%zu: %s \npath : %s\n"
			   "flag : %d\n", i, temp->value, temp->path, temp->flag);
	}
	else
		printf("empty list\n");
	//free_lst(head);
}

/*t_env	ft_free_lst(t_env *lst)
{
	t_env	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		(*lst)->value = NULL;
		(*lst)->path = NULL;
		(*lst).flag = NULL;
		free(*lst);
		*lst = temp;
	}

}*/

t_env	*ft_lst_last(t_env **lst)
{
	t_env	*temp;

	if (!*lst)
		return (*lst);
	temp = *lst;
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
		last = ft_lst_last(head);
		last->next = new;
		new->prev = last;
	}
	else
		*head = new;
}

t_env	*ft_new_node(char *value, char *path, bool flag)
{
	t_env	*env;

	env = calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->value = strdup(value);
	env->path = strdup(path);
	env->flag = flag;
	env->next = NULL;
	env->prev = NULL;
	return (env);
}

int	main(int arc, char **argv, char **environnement)
{
	if (arc)
		printf("ok, next\n");
	t_env	*env;
	int i;

	i = 1;
	while (argv[i])
	{
		env = ft_lst_add_back(environnement[i], ft_new_node(env, argv[i], 0));
		if (!env)
			return (printf("crash\n"), 0);
		i++;
	}
	print_lst(&env);
	return (0);
}