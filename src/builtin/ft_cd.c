/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:21:16 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/27 07:07:18 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_error_ft_cd_home(char **command)
{
	const char	*home;

	home = getenv("HOME");
	if (command[1] == NULL)
	{
		if (home == NULL)
		{
			ft_putstr_fd("The HOME environment variable is not defined.\n", 2);
			return (1);
		}
		if (home && chdir(home) != 0)
		{
			ft_putstr_fd("Error when changing directory.\n", 2);
			return (1);
		}
	}
	return (0);
}

static int	check_error_ft_cd(char **command)
{
	if (check_error_ft_cd_home(command) == 1)
		return (1);
	if (command[1] != NULL && command[2] != NULL)
	{
		write (2, " too many arguments\n", 20);
		return (1);
	}
	return (0);
}

static int	ft_chdid_and_verif(char *stock)
{
	if (stock && chdir(stock) == -1)
	{
		ft_putstr_fd(stock, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

static int	check_cd(char **command)
{
	if (check_error_ft_cd(command) == 1)
		return (1);
	if (check_error_ft_cd_home(command) == 1)
		return (1);
	return (0);
}

int	ft_cd(char **command, t_env **env)
{
	t_env	*current;

	current = *env;
	check_cd(command);
	refresh_env_path(*env, "OLDPWD");
	if (ft_chdid_and_verif(command[1]) == 1)
		return (2);
	refresh_env_path(*env, "PWD");
	return (EXIT_SUCCESS);
}
