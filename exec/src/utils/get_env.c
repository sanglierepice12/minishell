/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostr <gostr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:20:08 by gostr             #+#    #+#             */
/*   Updated: 2024/07/17 18:20:08 by gostr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_main_get_env(t_glob *glob)
{
	ft_lst_add_back(&glob->env, ft_new_node("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 0));
	/*ft_lst_add_back(&glob->env, ft_new_node("PWD", getcwd(NULL, 0), 0));*/
	if (!glob->env)
	{
		dprintf(2, "Failed to initialize environment\n");
		exit(g_error_code = 1);
	}
}