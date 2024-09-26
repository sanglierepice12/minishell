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

static bool	ft_access(t_input *cmd)
{
	char	*tempo;

	if (!cmd)
		return (ft_err_printf("no cmd", 1), 1);
	if (cmd->command[0] == '/' || cmd->command[0] == '.')
	{
		if (!access(cmd->command, F_OK | X_OK))
			return (0);
		if (ft_open_dir(cmd))
			return (1);
	}
	if (ft_is_builtin(cmd->command))
		return (0);
	if (ft_joiner_access(cmd))
		return (true);
	tempo = ft_str_join(cmd->argv[0], "/");
	if (access(tempo, X_OK))
	{
		free(tempo);
		return (ft_not_found(cmd->argv[0], ": command not found", 127), 1);
	}
	free(tempo);
	return (0);
}

static bool	ft_init_path(t_glob *glob, t_env *temp)
{
	size_t	i;

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
		if (ft_init_begin(glob, &i))
			return (true);
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
	else if (!ft_is_builtin(glob->cmd[0].command) && \
		access(glob->cmd[0].command, X_OK))
		return (ft_error_dir(glob->cmd[0].command));

	ft_free_double_tab(glob->cmd->path);
	glob->cmd->path = ft_get_all_path(&glob->env);
	ft_executor(glob);
}
