/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:15:39 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/22 08:58:06 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_sig = 0;

static int	run_readline(t_env *env, t_vars *vars)
{
	int	exit;

	exit = ft_readline(&env, vars);
	if (exit == 1)
		return (1);
	return (exit);
}

static void	init_vars(t_vars *vars)
{
	vars->env = NULL;
	vars->exit = FALSE;
	vars->exit_code = 0;
	vars->exit_code_signal = 0;
}

int	main(int ac, char **av, char *envp[])
{
	int		exit;
	t_env	*env;
	t_vars	*vars;

	(void)av;
	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (1);
	env = NULL;
	init_vars(vars);
	if (ac != 1)
	{
		ft_putstr_fd("Error: Too much arguments\n", 2);
		free(vars);
		return (1);
	}
	init_env(&env, envp);
	if (env == NULL)
		return (1);
	run_signals();
	exit = run_readline(env, vars);
	ft_lstclear_env(&env);
	free(vars);
	return (exit);
}
