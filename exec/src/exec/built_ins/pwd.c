/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:38:16 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/21 16:38:16 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_print_this_node(t_env **env, char *value)
{
	t_env	*temp;

	if (!env)
		return (printf("no env found\n"), (void)0);
	temp = *env;
	while (temp)
	{
		if (!ft_strncmp(temp->value, value, ft_strlen(value)))
			return (printf("%s\n", temp->path), (void)0);
		temp = temp->next;
	}
	printf("Value PWD not found\n");
}

void	ft_pwd(t_input *cmd, t_env **env)
{
	char	*path;

	path = NULL;
	if (*env && cmd->args < 2)
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (perror("getcwd : error\n"), (void)0);
		printf("%s\n", path);
		free(path);
	}
	else if (cmd->argv[1] && cmd->argv[1][0] == '-' && cmd->argv[1][1])
		dprintf(2, "bash: pwd: %c%c: invalid option\n"
				   "pwd: usage: pwd [-LP]\n", cmd->argv[1][0], cmd->argv[1][1]);
	else
		ft_print_this_node(env, "PWD");
}
