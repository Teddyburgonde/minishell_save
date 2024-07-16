/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:37:00 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/10 09:54:14 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_vars *vars, t_redirection *redirect)
{
	char	buf[1024];

	if (vars->nb_cmd == 1)
	{
		if (getcwd(buf, sizeof(buf)) == NULL)
		{
			ft_putstr_fd("An error has been detected\n", 2);
			return (1);
		}
		ft_putstr_fd(buf, redirect->outfile_fd);
		write (redirect->outfile_fd, "\n", 1);
	}
	else
	{
		if (getcwd(buf, sizeof(buf)) == NULL)
		{
			ft_putstr_fd("An error has been detected\n", 2);
			return (1);
		}
		ft_putstr_fd(buf, 1);
		write (1, "\n", 1);
	}
	return (0);
}
