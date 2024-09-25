/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbenois <arbenois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:34:11 by gostr             #+#    #+#             */
/*   Updated: 2024/09/23 05:38:48 by arbenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error(int code)
{
	g_error_code = code;
	perror("minisHell");
}

void	ft_error_dir(char *cmd)
{
	g_error_code = 127;
	dprintf(2, "minisHell : %s: No such file or directory\n", cmd);
}

void	ft_derror(char *cmd, char *variable, char *followed, int code)
{
	g_error_code = code;
	dprintf(2, "minisHell : %s: %s: %s\n", cmd, variable, followed);
}

void	ft_err_printf(char *msg, int code)
{
	g_error_code = code;
	dprintf(2, "%s\n", msg);
}

void	ft_not_found(char *cmd, char *msg, int code)
{
	g_error_code = code;
	dprintf(2, "%s%s\n", cmd, msg);
}

void	ft_env_derror(char *cmd, char *variable, char *followed, int code)
{
	g_error_code = code;
	dprintf(2, "minisHell : %s: `%s': %s\n", cmd, variable, followed);
}
