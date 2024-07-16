/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_manager_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 06:02:12 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/13 21:14:23 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cleanup_vars_path(t_vars *vars)
{
	if (vars && vars->path)
	{
		ft_free(vars->path);
		vars->path = NULL;
	}
}

void	manage_variable_path(t_env **env, t_vars *vars)
{
	if (lst_search_env("$PATH", *env) != NULL)
		vars->path = ft_split((lst_search_env("$PATH", *env))->value, ':');
	else
		vars->path = NULL;
}
