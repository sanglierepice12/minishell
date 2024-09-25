/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:22:47 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 11:36:10 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_args(char *input, int lenght)
{
	int	i;
	int	args;
	int	quote;

	args = 0;
	quote = 0;
	i = get_length_num(input, lenght);
	while (input[i])
	{
		if (ft_isspace(input[i]) == 1)
		{
			args++;
			i += ft_strlen_quote(input, i, &quote);
			if (quote == -1)
				return (-1);
		}
		if (ft_isspace(input[i]) == 0)
			i++;
		if (input[i] == '|' && if_in_quote(input, i) == 3)
			break ;
	}
	return (args);
}

static int	handle_word(char **argv, t_input_data *data)
{
	argv[data->lenght] = parse_word(data->input, &(data->i));
	if (data->lenght == -1 || argv[data->lenght] == NULL)
	{
		free_tab(argv, data->lenght);
		return (0);
	}
	data->lenght++;
	return (1);
}

static int	process_input(char **argv, t_input_data *data)
{
	while (data->input[data->i])
	{
		if (ft_isspace(data->input[data->i]) == 1)
		{
			if (!handle_word(argv, data))
				return (0);
		}
		if (ft_isspace(data->input[data->i]) == 0)
			data->i++;
		if (data->input[data->i] == '|' \
			&& if_in_quote(data->input, data->i) == 3)
			break ;
	}
	return (1);
}

char	**set_argv(char *input, unsigned long num, t_glob *glob)
{
	char			**argv;
	t_input_data	data;

	if (!glob->cmd[num].args)
		return (NULL);
	argv = ft_cal_loc(glob->cmd[num].args + 1, sizeof(char *));
	if (argv == NULL)
		return (NULL);
	data.input = input;
	data.i = get_length_num(input, num);
	data.lenght = 0;
	if (!process_input(argv, &data))
		return (NULL);
	if (check_redir(argv, glob, num) == 0)
		return (NULL);
	if (check_env(argv, glob, num) == 0)
		return (NULL);
	return (check_apply_heredoc(argv, &glob->cmd[num]));
}
