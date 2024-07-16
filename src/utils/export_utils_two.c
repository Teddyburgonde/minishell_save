/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:15:56 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/11 09:39:01 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_export(char *var_name)
{
	if (var_name)
		free(var_name);
}

void	var_set(char **var_name,
	int *export_status, char *cmd, t_vars *vars)
{
	*var_name = NULL;
	*export_status = 0;
	*export_status = verif_export(cmd);
	if (*export_status == 1)
		vars->exit_code = 1;
}
