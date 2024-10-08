/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_2_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:21:15 by gsuter            #+#    #+#             */
/*   Updated: 2024/10/08 18:50:13 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	ft_lst_size(t_env *lst)
{
	t_env	*temp;
	int		i;

	if (!lst)
		return (0);
	temp = lst;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

static char	*ft_super_join(char *begin, char *end)
{
	char	*final;
	size_t	i;
	size_t	j;

	final = ft_cal_loc(ft_strlen(begin) + ft_strlen(end) + 2, sizeof(char));
	if (!final)
		return (NULL);
	i = 0;
	while (end[i])
	{
		final[i] = end[i];
		i++;
	}
	final[i] = '=';
	j = 0;
	while (i++, begin[j])
	{
		final[i] = begin[j];
		j++;
	}
	return (final);
}

static char	*ft_get_key(t_env *temp)
{
	char	*key;

	key = NULL;
	key = ft_super_join(temp->value, temp->key);
	if (!key)
		return (NULL);
	return (key);
}

char	**ft_env_to_tab(t_env **env, t_glob *glob)
{
	char	**envp;
	ssize_t	i;
	t_env	*temp;

	temp = *env;
	envp = ft_cal_loc(sizeof(char *), ft_lst_size(*env) + 1);
	if (!envp)
		return (NULL);
	i = -1;
	while (++i, temp->next)
	{
		if (!temp->value)
			continue ;
		envp[i] = ft_get_key(temp);
		if (!envp[i])
			return (ft_free_double_tab(envp), \
			ft_exit(glob, NULL), NULL);
		temp = temp->next;
	}
	envp[i] = ft_get_key(temp);
	if (!envp[i])
		return (ft_free_double_tab(envp), \
		ft_exit(glob, NULL), NULL);
	return (envp);
}

void	ft_dup_two(int fd, int std, t_glob *glob)
{
	if (dup2(fd, std) == -1)
	{
		perror("miniHell");
		ft_free_all(glob);
		exit(EXIT_FAILURE);
	}
}
