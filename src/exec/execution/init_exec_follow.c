/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_follow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:47:05 by gsuter            #+#    #+#             */
/*   Updated: 2024/09/25 17:47:05 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_test_access(char *temp_cmd, t_input *cmd)
{
	if (!access(temp_cmd, F_OK | X_OK))
	{
		if (cmd->argv[0])
			free(cmd->argv[0]);
		cmd->argv[0] = ft_dup(temp_cmd);
		cmd->command = cmd->argv[0];
		free(temp_cmd);
		return (1);
	}
	return (0);
}

bool	ft_joiner_access(t_input *cmd)
{
	size_t	i;
	char	*temp_cmd;

	i = 0;
	while (cmd->path[i])
	{
		temp_cmd = ft_str_join(cmd->command, cmd->path[i]);
		if (!temp_cmd)
			return (ft_err_printf("no cmd", 1), 1);
		if (ft_test_access(temp_cmd, cmd))
			break ;
		else
		{
			i++;
			free(temp_cmd);
		}
	}
	return (false);
}

int	ft_open_dir(t_input *cmd)
{
	DIR		*dir;

	dir = opendir(cmd->argv[0]);
	if (dir)
	{
		closedir(dir);
		printf("minisHell: %s: Is a directory\n", cmd->command);
		return (g_error_code = 126, 0);
	}
	else
		return (printf("\n"), 1);
}

bool	ft_init_begin(t_glob *glob, size_t *i)
{
	size_t	j;
	char	*temp_path;

	j = 0;
	while (glob->cmd[*i].path[j])
	{
		temp_path = NULL;
		temp_path = ft_str_join("/", glob->cmd[*i].path[j]);
		if (!temp_path)
			return (ft_err_printf("nothing in temp path", 1), 1);
		free(glob->cmd[*i].path[j]);
		glob->cmd[*i].path[j] = ft_dup(temp_path);
		if (!glob->cmd[*i].path[j])
			return (free(temp_path), \
					ft_err_printf("glob->cmd->path empty", 1), 1);
		free(temp_path);
		j++;
	}
	return (false);
}
