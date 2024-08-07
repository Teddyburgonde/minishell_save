/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:11:08 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/11 09:32:02 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**error_command_for_find_path(char **command_line, t_vars *vars)
{
	if (command_line == NULL || command_line[0] == NULL
		|| command_line[0][0] == '\0')
	{
		ft_putstr_fd(command_line[0], 2);
		ft_putstr_fd(": command not found.\n", 2);
		vars->exit_code = 127;
		return (command_line);
	}
	return (NULL);
}

int	access_dir(char **command_line, DIR *dir, t_vars *vars)
{
	if (dir)
	{
		if (command_line[0][0] == '.' && command_line[0][1] == '/')
		{
			ft_putstr_fd(command_line[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			vars->exit_code = 126;
		}
		else if (ft_strcspn(command_line[0], "/") == ft_strlen(command_line[0]))
		{
			ft_putstr_fd(command_line[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			vars->exit_code = 127;
		}
		else if (strncmp(command_line[0], "/nfs", 4) == 0)
		{
			ft_putstr_fd(command_line[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			vars->exit_code = 126;
		}
	}
	return (vars->exit_code);
}

void	dir_error(char **command_line, t_vars *vars)
{
	DIR		*dir;

	dir = opendir(command_line[0]);
	if (dir)
	{
		vars->exit_code = access_dir(command_line, dir, vars);
		closedir(dir);
	}
}

char	**find_the_accessible_path(char **path,
	t_vars *vars, char **command_line)
{
	int		i;
	char	*bin_path;
	char	*is_valid_cmd;
	char	**check_error;

	i = 0;
	check_error = error_command_for_find_path(command_line, vars);
	if (check_error != NULL)
		return (check_error);
	if (command_line[0][0] == '.' && command_line[0][1] == 0
		&& !command_line[1])
	{
		vars->exit_code = 2;
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		return (command_line);
	}
	if (access(command_line[0], X_OK) == 0)
	{
		dir_error(command_line, vars);
		return (command_line);
	}
	vars->exit_code = build_path(path, &bin_path, &is_valid_cmd, command_line);
	return (command_line);
}
