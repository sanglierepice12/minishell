/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:39:13 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/23 16:39:13 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*char	**ft_double_join(char **src, char **dest)
{
	char	**value;
	size_t	i;
	size_t	j;
	size_t	len;

	*//*if (!src && !dest)
		return (NULL);*//*
	len = ft_strlen_double(src) + ft_strlen_double(dest);
	if (!len)
		return (NULL);
	value = ft_cal_loc(len, sizeof(char *));
	if (!value)
		return (printf("calloc error\n"), NULL);
	i = 0;
	while (src[i])
	{
		value[i] = ft_dup(src[i]);
		i++;
	}
	j = 0;
	while (dest[j])
	{
		value[i] = ft_dup(dest[j]);
		i++;
		j++;
	}
	return (value);
}*/
/*char	*ft_copy_stack(char *str, char	*src)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	i = 0;
	while (str[i])
	{
		src[len] = str[i];
		i++;
		len++;
	}
	return (src);
}*/

/*char	*ft_get_all_path(t_env	*temp)
{
	char	*test;
	size_t	len;

	len = 0;
	while (temp->next)
	{
		len += ft_strlen(temp->path);
		temp = temp->next;
	}
	while (temp->prev)
		temp = temp->prev;
	test = ft_cal_loc(len + 1, sizeof(char));
	if (!test)
		return (printf("malloc null\n"), NULL);
	while (temp->next)
	{
		test = ft_copy_stack(temp->path, test);
		temp = temp->next;
	}
	return (test);
}*/

t_env	*ft_find_thing_in_env(t_env **env, char *value)
{
	t_env	*temp;

	if (!env)
		return (NULL);
	temp = *env;
	while (temp)
	{
		if (ft_comp_str(temp->value, value))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static void	ft_get_first_node(t_glob *glob, char **env)
{
	char	*value;
	char	*path;
	int		j;

	if (!env)
		return ;
	j = 0;
	while (env[0][j])
	{
		if (env[0][j] == '=')
		{
			path = ft_dup(env[0] + j + 1);
			value = ft_str_copy_n(env[0], j);
			glob->env = ft_new_node(value, path, 0);
			free(path);
			free(value);
			break ;
		}
		j++;
	}
}

void	ft_get_env(t_glob *glob, char **env)
{
	int			i;
	int			j;
	char		*value;
	char		*path;

	ft_get_first_node(glob, env);
	if (!env)
		return (dprintf(2, "No env\n"), (void)0);
	i = 1;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				path = ft_dup(env[i] + j + 1);
				value = ft_str_copy_n(env[i], j);
				ft_lst_add_back(&glob->env, ft_new_node(value, path, 0));
				free(path);
				free(value);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	ft_env(t_glob *glob, t_input *cmd)
{
	size_t	i;

	if (cmd->args == 1)
		return (print_env(&glob->env, 0), (void)0);
	else if (cmd->args > 1)
	{
		i = 0;
		while (++i, i < cmd->args)
		{
			if (!ft_comp_str(cmd->argv[i], "env"))
				return (printf("env: ‘%s’: No such file or directory\n",\
							cmd->argv[1]), (void)0);
		}
		if (i == cmd->args)
			print_env(&glob->env, 0);
	}
}
