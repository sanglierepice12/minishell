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

static char	*set_command(char *input)
{
	if (ft_strncmp(input, "pwd", 3) == 0)
		return ("pwd");
	else if (ft_strncmp(input, "echo", 4) == 0)
		return ("echo");
	else if (ft_strncmp(input, "cd", 2) == 0)
		return ("cd");
	else if (ft_strncmp(input, "export", 6) == 0)
		return ("export");
	else if (ft_strncmp(input, "unset", 5) == 0)
		return ("unset");
	else if (ft_strncmp(input, "env", 3) == 0)
		return ("env");
	else if (ft_strncmp(input, "exit", 4) == 0)
		return ("exit");
	else if (ft_strncmp(input, "ls", 2) == 0)
		return ("ls");
	else if (ft_strncmp(input, "clear", 5) == 0)
		return ("clear");
	return (NULL);
}

static ssize_t	count_args(char *input, int lenght)
{
	size_t	i;
	int		quote;
	int		temp;

	i = 0;
	while (input[lenght])
	{
		if (input[lenght] != ' ')
		{
			i++;
			temp = ft_strlen_quote(input, lenght, &quote);
			if (temp == -1)
				return (-1);
			lenght += temp;
		}
		if (input[lenght] == ' ')
			lenght++;
	}
	return (i);
}

static char	*copy_word(char *input, int *i)
{
	int		lenght;
	char	*tab;
	int		temp;
	int		skip;
	int		checkquote;

	temp = 0;
	lenght = ft_strlen_quote(input, *i, &temp);
	if (lenght == -1)
		return (NULL);
	if (temp >= 1)
		lenght -= temp * 2;
	tab = malloc(lenght + 1 * sizeof(char));
	if (tab == NULL)
		return (NULL);
	tab[lenght] = 0;
	temp = 0;
	skip = 0;
	checkquote = 0;
	while (temp != lenght)
	{
		if (input[*i + temp + skip] == 39 && checkquote == 0)
		{
			checkquote = 1;
			skip++;
		}
		else if (input[*i + temp + skip] == 34 && checkquote == 0)
		{
			checkquote = 2;
			skip++;
		}
		else if (input[*i + temp + skip] == 39 && checkquote == 1)
		{
			checkquote = 0;
			skip++;
		}
		else if (input[*i + temp + skip] == 34 && checkquote == 2)
		{
			checkquote = 0;
			skip++;
		}
		else
		{
			tab[temp] = input[*i + temp + skip];
			temp++;
		}
	}
	*i += ft_strlen_quote(input, *i, &temp);
	return (tab);
}

static char	**set_argv(char *input, t_input *cmd)
{
	char	**argv;
	int		i;
	int		lenght;

	argv = malloc(cmd->args * sizeof(char *) + 1);
	if (argv == NULL)
		return (0);
	lenght = 0;
	//i = ft_strlen(cmd->command);
	i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
		{
			argv[lenght] = copy_word(input, &i);
			if (argv[lenght] == NULL)
			{
				free_tab(argv, lenght - 1);
				return (0);
			}
			lenght++;
		}
		if (input[i] == ' ')
			i++;
		printf("i = %d\n", i);
	}
	return (argv);
}

void	show_struct(t_input *cmd)
{
	int	i;

	printf("ARGS = %d\n", cmd->args);
	printf("cmd = %s\n", cmd->command);
	i = 0;
	while (i != cmd->args)
	{
		printf("ARGV = %s\n", cmd->argv[i]);
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);
}

int	parse_in_struct(t_glob *glob, char *input)
{
	glob->cmd.command = set_command(input);
	glob->cmd.args = count_args(input, ft_strlen(glob->cmd.command));
	if (glob->cmd.args == -1)
		return (0);
	glob->cmd.argv = set_argv(input, &glob->cmd);
	if (glob->cmd.argv == 0)
		return (0);
	//ft_call(glob, input);
	glob->cmd.args = 1;
	ft_call(glob, &glob->cmd);
	show_struct(&glob->cmd);
	return (1);
}
