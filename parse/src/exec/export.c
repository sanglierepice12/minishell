/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:39:16 by gsuter            #+#    #+#             */
/*   Updated: 2024/05/31 17:39:16 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export(t_env **env, char *input)
{
	if (!input[8])
		print_env(env, 1);
	else
	{
		ft_lst_add_back(env, ft_new_node(input + 7, NULL, 1));
		/*ft_lst_add_back(env, ft_new_node(cmd.arg,cmd.arg, 1)); //arg 1 et 2*/
	}
}
