/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:06:26 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/12 11:39:21 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wait_pids(t_vars *vars)
{
	int		i;
	int		status;
	pid_t	pid;

	if (vars->pids)
	{
		i = 0;
		set_interactive_mode(2);
		while (vars->pids[i] != -1)
		{
			pid = vars->pids[i];
			waitpid(vars->pids[i], &status, 0);
			i++;
			vars->exit_code = WEXITSTATUS(status);
			if (vars->exit_code == 130)
				g_sig = SIGINT + 128;
			i++;
		}
		if (vars->exit_code == 131)
			write(2, "Quit (core dumped)\n", 19);
	}
}
