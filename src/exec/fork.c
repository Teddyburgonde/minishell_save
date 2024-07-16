/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:03:38 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/11 09:29:55 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

int	process(t_vars *vars, t_redirection *redirect,
	t_env **env, t_command_line_parsing *tmp)
{
	vars->child = fork();
	if (vars->child == 0)
		child_process(vars, redirect, env, tmp);
	else if (vars->child < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	handle_pipe_closing(vars);
	if (vars->cmd_index == vars->nb_cmd)
		vars->last_child = vars->child;
	return (0);
}

int	fork_processes(t_vars *vars, t_redirection **redirect,
	t_env **envp, t_command_line_parsing *tmp)
{
	initialize_vars(vars);
	if (vars->nb_cmd > 0)
		process_commands(vars, redirect, envp, tmp);
	if (vars->nb_cmd > 1 || (vars->nb_cmd == 1
			&& is_builtins_parsing(vars->cmd[0]) == FALSE))
		vars->exit_code = wait_process(vars);
	ft_close_fd(vars);
	ft_lstclear_final_redirection(redirect, vars);
	ft_free_tab_3d(vars);
	return (0);
}
