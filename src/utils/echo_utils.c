/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:37:59 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/13 18:45:24 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_value_exit_status(char **command)
{
	if (command[1][0] && command[1][0] == '$' && command[1][1] == '?')
		return (0);
	return (1);
}

void	echo_in_fd(char **command, int fd, int i)
{
	while (command[i])
	{
		ft_putstr_fd(command[i], fd);
		if (command[i + 1] != NULL)
			write(fd, " ", 1);
		i++;
	}
}

void	echo_not_fd(char **command, int i)
{
	while (command[i])
	{
		ft_putstr_fd(command[i], 1);
		if (command[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

int	ft_count_char(char *str, char to_find)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == to_find)
			count++;
		i++;
	}
	return (count);
}

t_env	*find_env_by_var_name(t_env *env, const char *var_name)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (strcmp(current->var_name, var_name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
