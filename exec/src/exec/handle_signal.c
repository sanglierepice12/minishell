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

void handle_sigint(int sig) {
	(void)sig;
	g_error_code = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_sigquit(int sig) {
	(void)sig;
	g_error_code = 131;
}

void ft_handle_signal()
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;

	if (sigaction(SIGINT, &sa_int, NULL) == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;

	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}