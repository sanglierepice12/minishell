/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_in_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 03:30:09 by arbenois          #+#    #+#             */
/*   Updated: 2024/05/29 03:30:10 by arbenois         ###   ########.fr       */
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

static void	initialize_command(t_input *command)
{
	command->heredoc.type_outfile = NULL;
	command->heredoc.file_outfile = NULL;
	command->heredoc.type_infile = NULL;
	command->heredoc.file_infile = NULL;
	command->heredoc.rest_heredoc = NULL;
}

static void	print_command_info(t_input *command)
{
	int	temp;
	int	size;

	printf("COMMAND = %s\n", command->command);
	printf("ARGS = %d\n", command->args);
	temp = 0;
	while (temp != command->args)
	{
		printf("ARGV = %s\n", command->argv[temp]);
		temp++;
	}
	if (command->heredoc.rest_heredoc != 0)
	{
		size = 0;
		temp = ft_strlen_bis(command->heredoc.rest_heredoc);
		while (temp != size)
		{
			printf("HEREDOC INFO = %s\n", command->heredoc.rest_heredoc[size]);
			size++;
		}
	}
	if (command->heredoc.type_infile != 0)
	{
		printf("Heredoc type Infile = %s\n", command->heredoc.type_infile);
		printf("Heredoc file Infile = %s\n", command->heredoc.file_infile);
	}
	if (command->heredoc.type_outfile != 0)
	{
		printf("Heredoc type Outfile = %s\n", command->heredoc.type_outfile);
		printf("Heredoc file Outfile = %s\n", command->heredoc.file_outfile);
	}
	printf("\n");
}

int	parse_in_struct(t_glob *glob, char *input)
{
	int	num_args;
	int	i;

	i = 0;
	num_args = get_num_args(input);
	printf("Num ARG = %d\n", num_args);
	glob->command = malloc(num_args * sizeof(t_input));
	if (!glob->command)
		return (0);
	while (i != num_args)
	{
		initialize_command(&glob->command[i]);
		glob->command[i].args = count_args(input, i);
		if (glob->command[i].args == -1)
			return (free_parse(glob, 1), 0);
		glob->command[i].argv = set_argv(input, i, glob);
		if (glob->command[i].argv == NULL)
			return (free_parse(glob, 1), 0);
		glob->command[i].command = glob->command[i].argv[0];
		if (glob->command[i].command == NULL)
			return (free_parse(glob, 2), 0);
		i++;
	}
	i = 0;
	while (i != num_args)
	{
		printf("Liste %d\n", i);
		print_command_info(&glob->command[i]);
		i++;
	}
	return (1);
}
