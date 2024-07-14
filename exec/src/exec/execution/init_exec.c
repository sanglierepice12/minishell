/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostr <gostr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:47:43 by gostr             #+#    #+#             */
/*   Updated: 2024/07/09 16:47:43 by gostr            ###   ########.fr       */
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
		return (perror("MinisHell"), (void)0);
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
	if ((ft_comp_str(cmd, "cd"))	\
	|| (ft_comp_str(cmd, "pwd"))	\
	|| (ft_comp_str(cmd, "echo"))	\
	|| (ft_comp_str(cmd, "env"))	\
	|| (ft_comp_str(cmd, "unset"))	\
	|| (ft_comp_str(cmd, "export"))	\
	|| (ft_comp_str(cmd, "exit")))	\
		return (1);
	else
		return (0);
}

void	ft_access(t_input *cmd)
{
	size_t	i;
	char	*temp_cmd;

	if (!cmd)
		return (printf("no cmd\n"), (void)0);
	if (!access(cmd->command, F_OK | X_OK))
		return ;
	if (ft_is_builtin(cmd->command))
		return ;
	i = 0;
	while (cmd->path[i])
	{
		temp_cmd = ft_str_join(cmd->command, cmd->path[i]);
		if (!temp_cmd)
			return (printf("no cmd\n"), (void)0);
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
	if (access(cmd->argv[0], F_OK))
		dprintf(2, "MinisHell: %s: No such file or directory\n", cmd->argv[0]);
		//perror("MinisHell");
}

void	ft_init_path(t_glob *glob, t_env *temp)
{
	size_t	i;
	size_t	j;
	char	*temp_path;

	if (!temp || !glob)
		return (printf("Nothing in temp\n"), (void)0);
	i = 0;
	while (i < glob->count_cmd)
	{
		if (ft_is_builtin(glob->cmd[i].command))
		{
			i++;
			continue ;
		}
		glob->cmd[i].path = ft_split(temp->path, ':');
		if (!glob->cmd[i].path)
			return (printf("Nothing in path\n"), (void)0);
		j = 0;
		while (glob->cmd[i].path[j])
		{
			temp_path = NULL;
			temp_path = ft_str_join("/", glob->cmd[i].path[j]);
			if (!temp_path)
				return (printf("temp_path empty\n"), (void)0);
			free(glob->cmd[i].path[j]);
			glob->cmd[i].path[j] = ft_dup(temp_path);
			if (!glob->cmd[i].path[j])
				return (free(temp_path), \
					printf("glob->cmd->path empty\n"), (void)0);
			free(temp_path);
			j++;
		}
		ft_access(&glob->cmd[i]);
		i++;
	}
}

void	ft_init_exec(t_glob *glob)
{
	t_env	*temp;

	if (!glob)
		return (printf("Nothing in glob\n"), (void)0);
	if (glob->env)
		temp = glob->env;
	temp = ft_find_thing_in_env(&glob->env, "PATH");
	if (temp && ft_comp_str(temp->value, "PATH"))
		ft_init_path(glob, temp);
	ft_executor(glob);
}
