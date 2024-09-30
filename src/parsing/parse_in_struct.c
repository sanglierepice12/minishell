/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_in_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 03:30:09 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 17:19:42 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_num_args(char *input)
{
	int	num_args;
	int	i;

	num_args = 1;
	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && if_in_quote(input, i) == 3)
		{
			if (input[i + 1] == '|')
			{
				printf("minisHell: syntax error near unexpected token `|'\n");
				free(input);
				return (-1);
			}
			num_args++;
		}
		i++;
	}
	return (num_args);
}

static void	initialize_command(t_input *cmd, t_glob *glob)
{
	cmd->heredoc.type_outfile = NULL;
	cmd->heredoc.type_infile = NULL;
	cmd->heredoc.file_infile = NULL;
	cmd->heredoc.rest_heredoc = NULL;
	cmd->argv = NULL;
	cmd->command = NULL;
	cmd->args = 0;
	cmd->check_m = &glob->check_mes;
}

/*
static void	print_command_info(t_input *cmd)
{
	size_t	temp;
	size_t	size;

	printf("COMMAND = %s\n", cmd->command);
	printf("ARGS = %zu\n", cmd->args);
	temp = 0;
	while (temp != cmd->args)
	{
		printf("ARGV = %s\n", cmd->argv[temp]);
		temp++;
	}
	if (cmd->heredoc.rest_heredoc != 0)
	{
		size = 0;
		temp = ft_strlen_bis(cmd->heredoc.rest_heredoc);
		while (temp != size)
		{
			printf("HEREDOC INFO = %s\n", cmd->heredoc.rest_heredoc[size]);
			size++;
		}
	}
	if (cmd->heredoc.type_infile != 0)
	{
		printf("Heredoc type Infile = %s\n", cmd->heredoc.type_infile);
		size = 0;
		while (cmd->heredoc.file_infile[size] != 0)
		{
			printf("Heredoc file Infile = %s\n", cmd->heredoc.file_infile[size]);
			size++;
		}
	}
	if (cmd->heredoc.type_outfile != 0)
	{
		printf("Heredoc type Outfile = %s\n", cmd->heredoc.type_outfile);
		printf("Heredoc file Outfile = %s\n", cmd->heredoc.file_outfile);
	}
	printf("\n");
}*/

static int	setup_command(t_glob *glob, char *input, int i)
{
	initialize_command(&glob->cmd[i], glob);
	if (!input)
		return (0);
	glob->cmd[i].args = count_args(input, i);
	if ((ssize_t)glob->cmd[i].args == -1)
		return (0);
	glob->cmd[i].initargs = glob->cmd[i].args;
	glob->cmd[i].argv = set_argv(input, i, glob);
	if (glob->cmd[i].argv == NULL)
		return (0);
	if (glob->cmd[i].args)
		glob->cmd[i].command = glob->cmd[i].argv[0];
	return (1);
}

static int	initialize_glob(t_glob *glob, char *tab)
{
	ssize_t		num_args;

	num_args = get_num_args(tab);
	if (num_args == -1)
		return (0);
	glob->count_cmd = num_args;
	glob->cmd = ft_cal_loc((num_args + 1), sizeof(t_input));
	if (!glob->cmd)
		return (0);
	return (1);
}

int	parse_in_struct(t_glob *glob, char *input)
{
	size_t		i;
	char		*tab;

	tab = ft_dup(input);
	tab = expend_env_var(tab, glob);
	if (!initialize_glob(glob, tab))
		return (0);
	i = 0;
	while (i != glob->count_cmd)
	{
		if (!setup_command(glob, tab, i))
			return (ft_free_cmd(glob), free(tab), 0);
		i++;
	}
	//print_command_info(glob->cmd);
	if (check_command_null(glob, glob->count_cmd) == 0)
		return (ft_free_cmd(glob), free(tab), 0);
	free(tab);
	ft_init_exec(glob);
	ft_free_cmd(glob);
	glob->cmd = NULL;
	return (1);
}
