/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:53:00 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/11 10:02:54 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	if (!tab[0])
	{
		free(tab);
		return ;
	}
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_tab_3d(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	if (!vars->cmd)
		return ;
	while (vars->cmd[i])
	{
		j = 0;
		while (vars->cmd[i][j])
		{
			free(vars->cmd[i][j]);
			j++;
		}
		free(vars->cmd[i]);
		i++;
	}
	free(vars->cmd);
}

int	ft_isalpha(int c)
{
	if (!((c >= 97 && c <= 122) || (c >= 65 && c <= 90)))
		return (0);
	return (1);
}

int	verif_error_1(char *str)
{
	if ((ft_isdigit(str[0]) || str[0] == '='
			|| ft_isalpha(str[0]) == 0) && str[0] != '_')
	{
		error_export_1(str);
		return (1);
	}
	return (0);
}
