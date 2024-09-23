/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:22:47 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/23 05:43:16 by arbenois         ###   ########.fr       */
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

static char	*copy_word(char *input, int *i)
{
	char	*tab;
	int		lenght;
	int		temp;
	int		y;

	temp = 0;
	lenght = ft_strlen_quote(input, *i, &temp);
	if (lenght == -1)
		return (NULL);
	tab = ft_cal_loc(lenght + 1, sizeof(char));
	if (!tab)
		return (NULL);
	tab[lenght] = '\0';
	y = 0;
	while (lenght != y)
	{
		tab[y] = input[*i + y];
		y++;
	}
	return (tab);
}

static char	*parse_word(char *input, int *i, t_glob *glob)
{
	int		temp;
	char	*word;

	temp = 0;
	word = copy_word(input, i);
	if (!word)
		return (word);
	word = expend_env_var(word, glob);
	if (!word)
		return (word);
	*i += ft_strlen_quote(input, *i, &temp);
	return (word);
}

static int	print_redir_error(char *c)
{
	printf("minisHell: syntax error near unexpected token `%s'\n", c);
	g_error_code = 2;
	return (0);
}

static int	check_more_redir(char **argv, t_redir *redir, int i, int y)
{
	if ((redir->left >= 2 || redir->right >= 2) && argv[i][y] == '|')
		return (print_redir_error("|"));
	else if (redir->right > 3)
		return (print_redir_error(">>"));
	else if (redir->right == 3)
		return (print_redir_error(">"));
	else if (redir->right == 2 && redir->left == 1)
		return (print_redir_error("<"));
	else if (redir->right == 2 && redir->left >= 2 && argv[i][y - 1] == '<')
		return (print_redir_error("<<"));
	else if (redir->left > 3)
		return (print_redir_error("<<"));
	else if (redir->left == 3)
		return (print_redir_error("<"));
	else if (redir->left == 2 && redir->right == 1)
		return (print_redir_error(">"));
	else if (redir->left == 2 && redir->right >= 2)
		return (print_redir_error(">>"));
	redir->left = 0;
	redir->right = 0;
	return (1);
}

static int	remove_all_quote(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		argv[i] = delete_quote(argv[i], 0);
		i++;
	}
	return (1);
}

static int	handle_redir(char **argv, t_redir *redir, int i, int y)
{
	if (argv[i][y] == '>')
	{
		if (redir->right == 1 || redir->left == 1)
		{
			if (argv[i][y + 1] == '>')
				return (print_redir_error(">>"));
			return (print_redir_error(">"));
		}
		redir->right++;
	}
	else if (argv[i][y] == '<')
	{
		if (redir->right == 1 || redir->left == 1)
		{
			if (argv[i][y + 1] == '<')
				return (print_redir_error("<<"));
			return (print_redir_error("<"));
		}
		redir->left++;
	}
	return (1);
}

static int	check_redir(char **argv, t_glob *glob, unsigned long num)
{
	size_t	i;
	int		y;
	t_redir	redir;

	i = -1;
	redir.left = 0;
	redir.right = 0;
	while (++i != glob->cmd[num].args)
	{
		y = -1;
		while (argv[i][++y])
		{
			if (if_in_quote(argv[i], y) != 0)
				continue ;
			if (!handle_redir(argv, &redir, i, y))
				return (0);
			if (!check_more_redir(argv, &redir, i, y))
				return (0);
		}
	}
	if (redir.right > 0 || redir.left > 0)
		return (print_redir_error("newline"));
	return (remove_all_quote(argv));
}

static int	check_tab(char *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_isspace(tab[i]) == 1)
			return (0);
		i++;
	}
	return (1);
}

static char	**remove_tab(char **argv, int size, t_glob *glob, unsigned long num)
{
	int		i;
	int		temp;
	char	**tab;
	int		argc;

	i = 0;
	temp = 0;
	argc = ft_strlen_bis(argv);
	if (argc == 1)
		return (free_tab(argv, argc), NULL);
	tab = ft_cal_loc(argc, sizeof(char *));
	if (!tab)
		return (free_tab(argv, argc), NULL);
	while (i + temp <= argc - 1)
	{
		if (i == size)
			temp++;
		tab[i] = argv[i + temp];
		i++;
	}
	glob->cmd[num].args--;
	free_tab(argv, argc);
	return (tab);
}

static int	check_env(char **argv, t_glob *glob, unsigned long num)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (check_tab(argv[i]) == 1)
		{
			argv = remove_tab(argv, i, glob, num);
			if (!argv)
				return (0);
			if (argv[i] == NULL)
				return (1);
		}
		i++;
	}
	return (1);
}

static int	handle_word(char **argv, t_input_data *data, t_glob *glob)
{
	argv[data->lenght] = parse_word(data->input, &(data->i), glob);
	if (data->lenght == -1 || argv[data->lenght] == NULL)
	{
		free_tab(argv, data->lenght);
		return (0);
	}
	data->lenght++;
	return (1);
}

static int	process_input(char **argv, t_input_data *data, t_glob *glob)
{
	while (data->input[data->i])
	{
		if (ft_isspace(data->input[data->i]) == 1)
		{
			if (!handle_word(argv, data, glob))
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
	argv = ft_cal_loc(glob->cmd[num].args + 1, sizeof(*argv));
	if (argv == NULL)
		return (NULL);
	data.input = input;
	data.i = get_length_num(input, num);
	data.lenght = 0;
	if (!process_input(argv, &data, glob))
		return (NULL);
	if (check_redir(argv, glob, num) == 0)
		return (NULL);
	if (check_env(argv, glob, num) == 0)
		return (NULL);
	return (check_apply_heredoc(argv, &glob->cmd[num]));
}
