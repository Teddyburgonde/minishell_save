/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:07:22 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/10 11:09:19 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_sigint(int signal)
{
	(void)signal;
	printf("\n");
}

static void	ft_sigquit(int signal)
{
	(void)signal;
	g_sig = 131;
	printf("Quit\n");
}

void	ft_ctrl_c(int signal)
{
	(void)signal;
	g_sig = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_interactive_mode(int set)
{
	if (set == 1)
	{
		signal(SIGINT, &ft_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		return ;
	}
	if (set == 2)
	{
		signal(SIGINT, &ft_sigint);
		signal(SIGQUIT, &ft_sigquit);
		return ;
	}
	if (set == 3)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		return ;
	}
}

void	run_signals(void)
{
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
