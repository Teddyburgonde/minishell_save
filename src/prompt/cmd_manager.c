/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:10:36 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/11 09:45:14 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	execution(t_vars *vars, t_redirection **redirection,
	t_env **env, t_command_line_parsing *cmd)
{
	if (g_sig == 0)
		fork_processes(vars, redirection, env, cmd);
	else
	{
		ft_lstclear_final_redirection(redirection, vars);
		ft_free_tab_3d(vars);
	}
}

int	ft_cmd_manager(t_env **env,
	t_command_line_parsing *cmd, t_vars *vars)
{
	t_command_to_expand				*tmp;
	t_argument_to_expand			*tmp_arg;
	t_redirection					*redirection;

	tmp = cmd->commands;
	tmp_arg = tmp->arguments;
	if (*env)
	{
		vars->cmd_index = 0;
		manage_variable_path(env, vars);
		tmp->redirections = ft_expand_redirections(&cmd->commands->redirections,
				*env, vars);
		vars->redirection = &redirection;
		stock_redirection(cmd, *env, vars, &redirection);
		vars->nb_cmd = ft_lstsize_command(cmd->commands);
		vars->cmd = ft_calloc(vars->nb_cmd + 1, sizeof(char **));
		verif_fill_command_paths(vars, tmp, *env);
		cleanup_vars_path(vars);
		vars->env = env_to_char(*env);
		execution(vars, &redirection, env, cmd);
		ft_lstclear_commands(&(cmd->commands));
		free(vars->env);
	}
	return (0);
}
