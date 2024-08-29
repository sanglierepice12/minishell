/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_in_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 03:30:09 by arbenois          #+#    #+#             */
/*   Updated: 2024/08/29 20:20:45 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_length_num(char *input, int number)
{
	int	num_args;
	int	i;

	num_args = 0;
	i = 0;
	if (number == 0)
		return (0);
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (input[i - 1] == ' ' && input[i + 1] == ' ')
				num_args++;
		}
		i++;
		if (num_args == number)
			break ;
	}
	return (i);
}
/*
static char	*allocate_command(char *input, int length, int i)
{
	char	*tab;

	tab = malloc((i + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	tab[i] = 0;
	i = 0;
	while (input[i + length])
	{
		if (input[i + length] == ' ' || input[i + length] == 0)
			break ;
		tab[i] = input[i + length];
		i++;
	}
	return (tab);
}

static char	*set_command(char *input, int num_com)
{
	int		i;
	int		length;

	i = 0;
	if (num_com != 0)
		length = get_length_num(input, num_com);
	else
		length = 0;
	while (input[i + length] == ' ')
		length++;
	while (input[i + length])
	{
		if (input[i + length] == ' ' || input[i + length] == 0)
			break ;
		i++;
	}
	return (allocate_command(input, length, i));
}*/

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
			if (input[i - 1] == ' ' && input[i + 1] == ' ')
				num_args++;
		}
		i++;
	}
	return (num_args);
}

static void	initialize_command(t_input *cmd)
{
	cmd->heredoc.type_outfile = NULL;
	cmd->heredoc.file_outfile = NULL;
	cmd->heredoc.type_infile = NULL;
	cmd->heredoc.file_infile = NULL;
	cmd->heredoc.rest_heredoc = NULL;
	cmd->argv = NULL;
	cmd->command = NULL;
	cmd->args = 0;
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

int	parse_in_struct(t_glob *glob, char *input)
{
	int	num_args;
	int	i;

	i = 0;
	num_args = get_num_args(input);
	glob->count_cmd = num_args;
	glob->cmd = ft_cal_loc((num_args + 1), sizeof(t_input));
	if (!glob->cmd)
		return (0);
	while (i != num_args)
	{
		initialize_command(&glob->cmd[i]);
		glob->cmd[i].args = count_args(input, i);
		if ((ssize_t)glob->cmd[i].args == -1)
			return (0);
		glob->cmd[i].argv = set_argv(input, i, glob);
		if (glob->cmd[i].argv == NULL)
			return (ft_free_cmd(glob), 0);
			/*return (free_parse(glob, 2, i), 0);*/
		if (glob->cmd[i].args)
			glob->cmd[i].command = glob->cmd[i].argv[0];
		if (glob->cmd[i].command == NULL)
			return (free_parse(glob, 1, i), 0);
		i++;
	}
	/*glob->cmd[num_args].command = NULL;
	i = 0;
	while (i != num_args)
	{
		printf("Liste %d\n", i);
		print_command_info(&glob->cmd[i]);
		i++;
	}*/
	ft_init_exec(glob);
	ft_free_cmd(glob);
	return (1);
}
