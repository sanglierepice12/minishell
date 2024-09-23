/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:38:16 by gsuter            #+#    #+#             */
/*   Updated: 2024/09/23 05:48:48 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_print_this_node(t_env **env, char *value)
{
	t_env	*temp;

	if (!env)
		return (ft_err_printf("no env found", 1));
	temp = *env;
	while (temp)
	{
		if (!ft_strncmp(temp->value, value, ft_strlen(value)))
			return (printf("%s\n", temp->path), (void)0);
		temp = temp->next;
	}
	ft_err_printf("no value found", 1);
}

static char	*get_path_from_env(t_env **env)
{
	t_env	*temp;

	temp = *env;
	temp = ft_find_thing_in_env(&temp, "PWD");
	if (!temp)
		return (NULL);
	return (ft_dup(temp->path));
}

void	ft_pwd(t_input *cmd, t_env **env)
{
	char	*path;

	g_error_code = 0;
	if (*env && cmd->args < 2)
	{
		path = getcwd(NULL, 0);
		if (!path)
			path = get_path_from_env(env);
		if (!path)
			return (ft_err_printf("no path in PWD", 1));
		printf("%s\n", path);
		free(path);
	}
	else if (cmd->argv[1] && cmd->argv[1][0] == '-' && cmd->argv[1][1])
	{
		dprintf(2, "bash: pwd: %c%c: invalid option\n", cmd->argv[1][0],
			cmd->argv[1][1]);
		ft_err_printf("pwd: usage: pwd [-LP]", 2);
	}
	else
		ft_print_this_node(env, "PWD");
}
