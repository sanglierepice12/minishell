/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:04:32 by arbenois          #+#    #+#             */
/*   Updated: 2024/09/25 06:06:24 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../../include/minishell.h"

void	handle_sigpipe(int sig)
{
	printf("%ssa_p = %d\n%s", YELLOW, sig, RESET);
	if (sig == SIGPIPE)
	{
		g_error_code = 141;
		write(STDERR_FILENO, "Broken pipe\n", 12);
	}
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_error_code = 130;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigchild(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		g_error_code = 130;
		exit(g_error_code);
	}
	if (sig == SIGQUIT)
	{
		g_error_code = 131;
		write(2, "Quit (core dumped)\n", 19);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handle_sighere(int sig)
{
	if (sig == SIGINT)
	{
		g_error_code = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
*/
