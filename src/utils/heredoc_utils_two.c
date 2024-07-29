/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:40:40 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/23 14:40:47 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quit(int sig_num)
{
	g_sig = sig_num + 128;
	ioctl(STDIN_FILENO, TIOCSTI, EOF, '\n');
}

void	complete_heredoc(t_redirection *redirection,
	t_command_line_parsing *tmp_command, t_env *env, t_vars *vars)
{
	if (redirection->nb_heredoc && redirection->infile_fd != -1)
	{
		heredoc_setup(redirection, tmp_command, env, vars);
		close(redirection->infile_fd);
		redirection->infile_fd = -1;
		redirection->infile_fd = open(
				redirection->file_heredoc, O_RDONLY, 0644);
	}
	else
		perror("Error opening heredoc files");
}
