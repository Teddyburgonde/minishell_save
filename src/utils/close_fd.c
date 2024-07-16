/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:30:05 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/08 12:02:38 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_close_fd(t_vars *vars)
{
	if (vars->pipe_1[0] != -1)
	{
		close(vars->pipe_1[0]);
		vars->pipe_1[0] = -1;
	}
	if (vars->pipe_1[1] != -1)
	{
		close(vars->pipe_1[1]);
		vars->pipe_1[1] = -1;
	}
	if (vars->pipe_2[0] != -1)
	{
		close(vars->pipe_2[0]);
		vars->pipe_2[0] = -1;
	}
	if (vars->pipe_2[1] != -1)
	{
		close(vars->pipe_2[1]);
		vars->pipe_2[1] = -1;
	}
}

int	check_error_redirect_infifle_fd(t_redirection *redirect)
{
	if (redirect->infile_fd == -1)
	{
		write (2, "minishell: ", 11);
		ft_putstr_fd(redirect->name_infile, 2);
		write (2, ": ", 2);
		perror("");
		return (1);
	}
	return (0);
}

int	check_error_redirect_outfile_fd(t_redirection *redirect)
{
	if (redirect->outfile_fd == -1)
	{
		ft_putstr_fd(redirect->name_outfile, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (1);
	}
	return (0);
}

void	error_close_files(t_redirection *redirect)
{
	if (redirect && redirect->infile_fd != -1)
	{
		close(redirect->infile_fd);
		redirect->infile_fd = -1;
	}
	if (redirect && redirect->outfile_fd != -1)
	{
		close(redirect->outfile_fd);
		redirect->outfile_fd = -1;
	}
}
