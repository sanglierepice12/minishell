/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostr <gostr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:52:28 by gostr             #+#    #+#             */
/*   Updated: 2024/07/16 19:52:28 by gostr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sigpipe(int sig)
{
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
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		handle_sigint(sig);
		g_error_code = 131;
	}
}

void	ft_handle_signal(t_sig SIG)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_pipe;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		ft_error(1);
		exit(EXIT_FAILURE);
	}
	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		ft_error(1);
		exit(EXIT_FAILURE);
	}
	sa_pipe.sa_handler = handle_sigpipe;
	sigemptyset(&sa_pipe.sa_mask);
	sa_pipe.sa_flags = SA_RESTART;
	if (sigaction(SIGPIPE, &sa_pipe, NULL) == -1)
	{
		ft_error(1);
		exit(EXIT_FAILURE);
	}
}
