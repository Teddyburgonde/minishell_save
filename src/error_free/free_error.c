/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:53:00 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/26 10:47:06 by tebandam         ###   ########.fr       */
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
	int	len_mid;

	len_mid = ft_strcspn(str, "=");
	if (((ft_isdigit(str[0]) || str[0] == '='
				|| ft_isalpha(str[0]) == 0) && str[0] != '_')
		|| (set_append(str, &len_mid) == TRUE
			&& str[ft_strlen(str) - 1] == '+'))
	{
		error_export_1(str);
		return (1);
	}
	return (0);
}
