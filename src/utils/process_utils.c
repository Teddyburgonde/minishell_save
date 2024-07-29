/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:22:31 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/23 14:02:13 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_child_process(t_vars *vars, t_redirection *redirect,
	t_env **env, t_command_line_parsing *tmp)
{
	ft_lstclear_commands(&tmp->commands);
	free(tmp);
	if (vars->env)
		free(vars->env);
	if (env)
		ft_lstclear_env(env);
	if (redirect)
		ft_lstclear_final_redirection(vars->redirection, vars);
	if (vars->cmd)
		ft_free_tab_3d(vars);
	if (vars)
		free(vars);
}

static void	is_dir(t_vars *vars, t_redirection *redirect
	, t_env **env, t_command_line_parsing *tmp)
{
	DIR		*dir;
	char	**actual_cmd;

	actual_cmd = vars->cmd[vars->cmd_index - 1];
	if (access(actual_cmd[0], X_OK) == -1)
	{
		free_child_process(vars, redirect, env, tmp);
		exit(127);
	}
	if (actual_cmd[0][0] == '.' && actual_cmd[0][1] == '/')
	{
		dir = opendir(&actual_cmd[0][2]);
		if (dir)
		{
			free_child_process(vars, redirect, env, tmp);
			closedir(dir);
			exit(126);
		}
	}
}

static void	verif_or_builtins(t_vars *vars, t_redirection *redirect
	, t_env **env, t_command_line_parsing *tmp)
{
	char	**actual_cmd;
	int		exit_code;

	exit_code = vars->exit_code;
	actual_cmd = vars->cmd[vars->cmd_index - 1];
	if (actual_cmd != NULL && is_builtins_exec(vars) == 1)
	{
		cmd_selector(env, vars->cmd[vars->cmd_index - 1], vars, redirect);
		free_child_process(vars, redirect, env, tmp);
		exit(exit_code);
	}
	if (!vars->cmd || !actual_cmd || !actual_cmd[0] || !actual_cmd[0][0])
	{
		free_child_process(vars, redirect, env, tmp);
		exit (0);
	}
	is_dir(vars, redirect, env, tmp);
}

int	child_process(t_vars *vars, t_redirection *redirect
	, t_env **env, t_command_line_parsing *tmp)
{
	char	**actual_cmd;

	actual_cmd = vars->cmd[vars->cmd_index - 1];
	if (check_error_redirect_infifle_fd(redirect) == 1
		|| check_error_redirect_outfile_fd(redirect) == 1
		|| redirect->ambiguous == TRUE)
	{
		ft_close_fd(vars);
		free_child_process(vars, redirect, env, tmp);
		exit (1);
	}
	ft_flow_redirection(vars, redirect);
	ft_close_fd(vars);
	verif_or_builtins(vars, redirect, env, tmp);
	ft_lstclear_final_redirection(vars->redirection, vars);
	execve(actual_cmd[0], actual_cmd, vars->env);
	ft_close_fd(vars);
	free_child_process(vars, redirect, env, tmp);
	exit(1);
}

void	handle_pipe_closing(t_vars *vars)
{
	if ((vars->cmd_index - 1) % 2 == 1 && vars->nb_cmd > 1)
		close_pipe_odd(vars);
	if ((vars->cmd_index - 1) % 2 == 0 && vars->nb_cmd > 1)
		close_pipe_even(vars);
}
