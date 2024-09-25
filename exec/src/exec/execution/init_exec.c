/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:47:43 by gostr             #+#    #+#             */
/*   Updated: 2024/09/25 05:23:13 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_reset_in_out(t_glob *glob)
{
	int	temp_stdout;
	int	temp_stdin;

	temp_stdin = dup(0);
	temp_stdout = dup(1);
	if (temp_stdout == -1 || temp_stdin == -1)
		return (ft_error(1));
	close (temp_stdin);
	close (temp_stdout);
	if (glob->cmd[0].heredoc.is_there_any)
	{
		dup2(temp_stdin, 0);
		dup2(temp_stdout, 1);
	}
}

bool	ft_is_builtin(char *cmd)
{
	if ((ft_comp_str(cmd, "cd")) || (ft_comp_str(cmd, "pwd")) \
		|| (ft_comp_str(cmd, "echo")) || (ft_comp_str(cmd, "env")) \
		|| (ft_comp_str(cmd, "printenv")) || (ft_comp_str(cmd, "unset")) \
		|| (ft_comp_str(cmd, "export")) || (ft_comp_str(cmd, "exit")) \
		|| (ft_comp_str(cmd, "clear")))
		return (1);
	else
		return (0);
}

bool	ft_access(t_input *cmd)
{
	size_t	i;
	char	*temp_cmd;
	char	*tempo;
	//DIR		*dir;

	if (!cmd)
		return (ft_err_printf("no cmd", 1), 1);
	if (cmd->command[0] == '/' || cmd->command[0] == '.')
	{
		if (!access(cmd->command, F_OK | X_OK))
			return (0);
	}
	if (ft_is_builtin(cmd->command))
		return (0);
	i = 0;
	while (cmd->path[i])
	{
		/*dir = opendir(cmd->argv[0]);
		if (dir)
		{
			printf("la\n");
			return (closedir(dir), ft_error(1), 1);
		}
		else if (cmd->argv[0][0] == '/')
		{
			printf("ici\n");
			return (ft_error_dir(cmd->argv[0]), 1);
		}*/
		temp_cmd = ft_str_join(cmd->command, cmd->path[i]);
		if (!temp_cmd)
			return (ft_err_printf("no cmd", 1), 1);
		if (!access(temp_cmd, F_OK | X_OK))
		{
			if (cmd->argv[0])
				free(cmd->argv[0]);
			cmd->argv[0] = ft_dup(temp_cmd);
			cmd->command = cmd->argv[0];
			free(temp_cmd);
			break ;
		}
		else
		{
			i++;
			free(temp_cmd);
		}
	}

	//printf("ici\n");
	tempo = ft_str_join(cmd->argv[0], "/");
	if (access(tempo, X_OK))
	{
		free(tempo);
		return (ft_not_found(cmd->argv[0], ": biche command not found", 127), 1);
	}
	free(tempo);
	//(void)tempo;
	return (0);
}

bool	ft_init_path(t_glob *glob, t_env *temp)
{
	size_t	i;
	size_t	j;
	char	*temp_path;

	if (!temp || !glob)
		return (ft_err_printf("nothing in temp", 1), 1);
	i = 0;
	while (i < glob->count_cmd)
	{
		if (ft_is_builtin(glob->cmd[i].command))
		{
			i++;
			continue ;
		}
		glob->cmd[i].path = ft_split(temp->value, ':');
		if (!glob->cmd[i].path)
			return (ft_err_printf("nothing in path", 1), 1);
		j = 0;
		while (glob->cmd[i].path[j])
		{
			temp_path = NULL;
			temp_path = ft_str_join("/", glob->cmd[i].path[j]);
			if (!temp_path)
				return (ft_err_printf("nothing in temp path", 1), 1);
			free(glob->cmd[i].path[j]);
			glob->cmd[i].path[j] = ft_dup(temp_path);
			if (!glob->cmd[i].path[j])
				return (free(temp_path), \
					ft_err_printf("glob->cmd->path empty", 1), 1);
			free(temp_path);
			j++;
		}
		if (ft_access(&glob->cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_init_exec(t_glob *glob)
{
	t_env	*temp;

	if (!glob)
		return (ft_err_printf("Nothing in glob", 1));
	if (glob->env)
		temp = glob->env;
	temp = ft_find_thing_in_env(&glob->env, "PATH");
	if (temp && ft_comp_str(temp->key, "PATH"))
	{
		if (ft_init_path(glob, temp))
			return ;
	}
	ft_free_double_tab(glob->cmd->path);
	glob->cmd->path = ft_get_all_path(&glob->env);
	ft_executor(glob);
}
