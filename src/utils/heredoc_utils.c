/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:59:39 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/26 08:58:18 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redirection_to_expand	*is_last(t_redirection_to_expand *tmp)
{
	t_redirection_to_expand	*result;

	result = NULL;
	while (tmp)
	{
		if (tmp->e_type == REDIRECTION_HEREDOC)
			result = tmp;
		tmp = tmp->next;
	}
	return (result);
}

void	where_are_heredoc(t_redirection **list, t_bool exist)
{
	t_redirection	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (exist == FALSE && tmp)
			tmp->e_position = NONE;
		else if (exist == TRUE && tmp && tmp->e_position != HERE)
			tmp->e_position = COMING;
		tmp = tmp->next;
	}
}

void	prepare_heredoc(t_redirection *redirection,
	t_redirection_to_expand *tmp_redirection)
{
	redirection->nb_heredoc++;
	redirection->e_position = HERE;
	redirection->limiter = copy(tmp_redirection->arg);
	redirection->file_heredoc = ft_itoa(
			redirection->nb_heredoc);
	redirection->file_heredoc = ft_strjoin_free_s2(
			".heredoc", redirection->file_heredoc);
	if (access(redirection->file_heredoc, F_OK) == 0)
		unlink(redirection->file_heredoc);
	redirection->infile_fd = open(redirection->file_heredoc,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
}

static void	free_heredoc_child(t_env *env, t_vars *vars,
	t_command_line_parsing *tmp_command, t_redirection *redirection)
{
	ft_lstclear_env(&env);
	ft_lstclear_arguments(&tmp_command->commands->arguments);
	ft_lstclear_redirections(&tmp_command->commands->redirections);
	ft_lstclear_commands(&tmp_command->commands);
	free(tmp_command);
	ft_lstclear_final_redirection(vars->redirection, vars);
	ft_lstclear_final_redirection(&redirection, vars);
	ft_free(vars->path);
	free(vars);
	if (g_sig != 0)
		exit(g_sig);
	exit(0);
}

void	heredoc_setup(t_redirection *redirection,
	t_command_line_parsing *tmp_command, t_env *env, t_vars *vars)
{
	pid_t	child;
	int		wstatus;

	signal(SIGQUIT, SIG_IGN);
	child = fork();
	if (child == 0)
	{
		signal(SIGINT, quit);
		ft_heredoc(redirection,
			tmp_command->commands->redirections, env, vars);
		free_heredoc_child(env, vars, tmp_command, redirection);
	}
	else
	{
		wait(&wstatus);
		if (WIFSIGNALED(wstatus))
			vars->exit_code = WTERMSIG(wstatus) + 128;
		else
			vars->exit_code = WEXITSTATUS(wstatus);
		if (vars->exit_code == 130)
			g_sig = SIGINT + 128;
	}
	signal(SIGQUIT, &ft_sigquit);
}
