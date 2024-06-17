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

int	get_lenght_num(char *input, int number)
{
	int	num_args;
	int	i;

	num_args = 0;
	i = 0;
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

static char	*set_command(char *input, int num_com)
{
	int		i;
	int		lenght;
	char	*tab;

	i = 0;
	if (num_com != 0)
		lenght = get_lenght_num(input, num_com);
	else
		lenght = 0;
	while (input[i + lenght] == ' ')
		lenght++;
	while (input[i + lenght])
	{
		if (input[i + lenght] == ' ' || input[i + lenght] == 0)
			break ;
		i++;
	}
	tab = malloc((i + 1) * sizeof(char));
	tab[i] = 0;
	i = 0;
	while (input[i + lenght])
	{
		if (input[i + lenght] == ' ' || input[i + lenght] == 0)
			break ;
		tab[i] = input[i + lenght];
		i++;
	}
	return (tab);
}

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

int	parse_in_struct(t_glob *glob, char *input)
{
	int	num_args;
	int	i;
	int	temp;

	i = 0;
	num_args = get_num_args(input);
	printf("Num ARG = %d\n", num_args);
	glob->command = malloc(num_args * sizeof(t_input));
	while (i != num_args)
	{
		glob->command[i].heredoc.type_outfile = NULL;
		glob->command[i].heredoc.file_outfile = NULL;
		glob->command[i].heredoc.type_infile = NULL;
		glob->command[i].heredoc.file_infile = NULL;
		glob->command[i].command = set_command(input, i);
		glob->command[i].args = count_args(input, i);
		glob->command[i].argv = set_argv(input, i, glob);
		i++;
	}
	i = 0;
	while (i != num_args)
	{
		printf("Liste %d\n", i);
		printf("COMMAND = %s\n", glob->command[i].command);
		printf("ARGS = %d\n", glob->command[i].args);
		temp = 0;
		while (temp != glob->command[i].args)
		{
			printf("ARGV = %s\n", glob->command[i].argv[temp]);
			temp++;
		}
		if (glob->command[i].heredoc.type_infile != 0)
		{
			printf("Heredoc type Infile = %s\n", glob->command[i].heredoc.type_infile);
			printf("Heredoc file Infile = %s\n", glob->command[i].heredoc.file_infile);
		}
		if (glob->command[i].heredoc.type_outfile != 0)
		{
			printf("Heredoc type Outfile = %s\n", glob->command[i].heredoc.type_outfile);
			printf("Heredoc file Outfile = %s\n", glob->command[i].heredoc.file_outfile);
		}
		printf("\n");
		i++;
	}
	/*
	glob->command.command = set_command(input);
	glob->command.args = count_args(input, ft_strlen(glob->command.command));
	if (glob->command.args == -1)
		return (0);
	glob->command.argv = set_argv(input, &glob->command);
	if (glob->command.argv == 0)
		return (0);
	show_struct(&glob->command);*/
	return (1);
}
