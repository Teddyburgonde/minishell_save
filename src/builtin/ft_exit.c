/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:36:51 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/13 22:09:06 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static long	ft_atol(const char *nptr)
{
	int			i;
	long long	minus;
	long long	nb;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	minus = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus *= -1;
		i++;
	}
	nb = 0;
	while (ft_isdigit(nptr[i]) == 1)
	{
		nb = nb * 10 + (nptr[i] - 48);
		if (nb < 0)
			return (0);
		if (nb * minus < LONG_MIN)
			return (0);
		i++;
	}
	return (minus * nb);
}

static int	check_numeric_argument(char **command_line, t_vars *vars)
{
	if (command_line && command_line[0] && command_line[1]
		&& ft_strncmp(command_line[1], "0", 2) != 0
		&& ft_strncmp(command_line[1], "-9223372036854775808", 21) != 0
		&& ft_atol(command_line[1]) == 0)
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		rl_clear_history();
		vars->exit_code = 2;
		return (0);
	}
	return (1);
}

static int	has_invalid_argument(char **command_line, t_vars *vars)
{
	int	i;

	i = 0;
	if (!check_numeric_argument(command_line, vars))
		return (0);
	while (command_line && command_line[0]
		&& command_line[1] && command_line[1][i])
	{
		if (i == 0 && (command_line[1][i] == '-'
			|| command_line[1][i] == '+'))
			i++;
		if (!ft_isdigit(command_line[1][i])
			|| ft_atol(command_line[1]) > 9223372036854775807)
		{
			ft_putstr_fd(": numeric argument required\n", 2);
			rl_clear_history();
			vars->exit_code = 2;
			return (0);
		}
		i++;
	}
	return (1);
}

static void	handle_exit_arguments(char **command_line, int i, t_vars *vars)
{
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		vars->exit_code = 1;
	}
	else if (i > 1 && ft_atol(command_line[1]) >= 0)
		vars->exit_code = ft_atol(command_line[1]) % 256;
	else if (i > 1)
		vars->exit_code = 256 - (-1 * ft_atol(command_line[1]) % 256);
}

int	ft_exit(char **command_line, t_vars *vars)
{
	int	i;

	if (!command_line || !command_line[0] || !command_line[0][0])
		return (1);
	if (ft_strcmp(command_line[0], "exit") != 0
		&& ft_strlen(command_line[0]) != 0)
		return (1);
	ft_putstr_fd("exit\n", 2);
	if (!has_invalid_argument(command_line, vars))
	{
		vars->exit = TRUE;
		return (0);
	}
	i = 0;
	while (command_line[i])
		i++;
	handle_exit_arguments(command_line, i, vars);
	if (i > 2)
		return (0);
	vars->exit = TRUE;
	return (0);
}
