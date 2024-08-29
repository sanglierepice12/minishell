/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:22:47 by arbenois          #+#    #+#             */
/*   Updated: 2024/08/29 19:43:20 by arbenois         ###   ########.fr       */
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
	if (lenght != 0)
		i = get_length_num(input, lenght);
	else
		i = 0;
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
		if (input[i] == '|' && input[i - 1] == ' ' && input[i + 1] == ' ')
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
	word = delete_quote(word, 0);
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

static int	check_redir(char **argv, t_glob *glob, unsigned long num)
{
	int	size;
	int	i;
	int	y;
	int	redir_right;
	int	redir_left;

	size = glob->cmd[num].args;
	i = 0;
	redir_right = 0;
	redir_left = 0;
	while (i != size)
	{
		y = 0;
		while (argv[i][y] != 0)
		{
			if (if_in_quote(argv[i], y) == 1 || if_in_quote(argv[i], y) == 2)
				y++;
			else if (argv[i][y] == '>')
			{
				if (redir_right == 1 && y == 0)
				{
					if (argv[i][y + 1] == '>')
						return (print_redir_error(">>"));
					else
						return (print_redir_error(">"));
				}
				if (redir_left == 1 && y == 0)
				{
					if (argv[i][y + 1] == '>')
						return (print_redir_error(">>"));
					else
						return (print_redir_error(">"));
				}
				redir_right++;
			}
			else if (argv[i][y] == '<')
			{
				if (redir_right == 1 && y == 0)
				{
					if (argv[i][y + 1] == '<')
						return (print_redir_error("<<"));
					else
						return (print_redir_error("<"));
				}
				if (redir_left == 1 && y == 0)
				{
					if (argv[i][y + 1] == '<')
						return (print_redir_error("<<"));
					else
						return (print_redir_error("<"));
				}
				redir_left++;
			}
			else
			{
				if ((redir_left >= 2 || redir_right >= 2) && argv[i][y] == '|')
					return (print_redir_error("|"));
				else if (redir_right > 3)
					return (print_redir_error(">>"));
				else if (redir_right == 3)
					return (print_redir_error(">"));
				else if (redir_right == 2 && redir_left == 1)
					return (print_redir_error("<"));
				else if (redir_right == 2 && redir_left >= 2 && argv[i][y - 1] == '<')
					return (print_redir_error("<<"));
				else if (redir_left > 3)
					return (print_redir_error("<<"));
				else if (redir_left == 3)
					return (print_redir_error("<"));
				else if (redir_left == 2 && redir_right == 1)
					return (print_redir_error(">"));
				else if (redir_left == 2 && redir_right >= 2)
					return (print_redir_error(">>"));
				redir_left = 0;
				redir_right = 0;
			}
			y++;
		}
		if ((redir_left >= 2 || redir_right >= 2) && argv[i][y] == '|')
			return (print_redir_error("|"));
		else if (redir_right > 3)
			return (print_redir_error(">>"));
		else if (redir_right == 3)
			return (print_redir_error(">"));
		else if (redir_right == 2 && redir_left == 1)
			return (print_redir_error("<"));
		else if (redir_right == 2 && redir_left >= 2 && argv[i][y - 1] == '<')
			return (print_redir_error("<<"));
		else if (redir_left > 3)
			return (print_redir_error("<<"));
		else if (redir_left == 3)
			return (print_redir_error("<"));
		else if (redir_left == 2 && redir_right == 1)
			return (print_redir_error(">"));
		else if (redir_left == 2 && redir_right >= 2)
			return (print_redir_error(">>"));
		i++;
	}
	if (redir_right == 2 || redir_left == 2 \
		|| redir_right == 1 || redir_left == 1)
		return (print_redir_error("newline"));
	/*i = 0;
	while (argv[i])
	{
		argv[i] = delete_quote(argv[i], 0);
		i++;
	}*/
	return (1);
}

char	**set_argv(char *input, unsigned long num, t_glob *glob)
{
	char	**argv;
	int		i;
	int		lenght;

////////////////////////////////////
	if (!glob->cmd[num].args)
		return (NULL);
	///////////////////////////////args + 1
	argv = ft_cal_loc(glob->cmd[num].args + 1, sizeof(*argv));
	if (argv == NULL)
		return (NULL);
	lenght = 0;
	i = get_length_num(input, num);
	while (input[i])
	{
		if (ft_isspace(input[i]) == 1)
			argv[lenght++] = parse_word(input, &i, glob);
		if (lenght == -1 || (lenght && (argv[lenght - 1] == NULL)))
		{
			free_tab(argv, lenght);
			return (0);
		}
		if (ft_isspace(input[i]) == 0)
			i++;
		if (input[i] == '|' && (input[i - 1] == ' ' && input[i + 1] == ' '))
			break ;
	}
	if (check_redir(argv, glob, num) == 0)
		return (NULL);
	return (check_apply_heredoc(argv, &glob->cmd[num]));
}
