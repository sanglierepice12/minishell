/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_part2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:18:44 by gostr             #+#    #+#             */
/*   Updated: 2024/09/25 18:01:08 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_get_all_path_follow(t_env *temp, size_t *len)
{
	while (temp->next)
	{
		if (temp->value)
			*len += 1;
		temp = temp->next;
	}
	while (temp->prev)
		temp = temp->prev;
}

void	ft_get_env_follow(char **env, t_glob *glob)
{
	int			i;
	int			j;
	char		*value;
	char		*path;

	i = -1;
	while (i++, env[i])
	{
		j = -1;
		while (j++, env[i][j] && env[i][j] != '=')
			continue ;
		path = ft_dup(env[i] + j + 1);
		if (!path)
			return (ft_err_printf("error malloc", 1));
		value = ft_str_copy_n(env[i], j);
		if (!value)
			return (free(path), ft_err_printf("error malloc", 1));
		ft_lst_add_back(&glob->env, ft_new_node(value, path, 0));
		free(path);
		free(value);
	}
}

void	ft_copy_env(int j, char **env, t_glob *glob)
{
	char	*value;
	char	*path;

	path = ft_dup(env[0] + j + 1);
	if (!path)
		return (ft_err_printf("error malloc", 1));
	value = ft_str_copy_n(env[0], j);
	if (!value)
		return (ft_err_printf("error malloc", 1));
	glob->env = ft_new_node(value, path, 0);
	if (!glob->env)
	{
		glob->env = NULL;
		return ;
	}
	free(path);
	free(value);
}
