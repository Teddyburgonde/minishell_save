/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 05:44:21 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/26 14:35:08 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	hide_and_update_env_var(t_env *tmp_env, char *cmd)
{
	if (!tmp_env->value)
	{
		if (!cmd || (cmd && ft_strchr(cmd, '=') != 0))
			tmp_env->hide = FALSE;
		else
			tmp_env->hide = TRUE;
		if (tmp_env->full_path)
			free(tmp_env->full_path);
		tmp_env->full_path = copy(cmd);
		tmp_env->value = NULL;
	}
}

void	update_env_var(t_env *tmp_env, char *cmd, char *value)
{
	if (!cmd || (cmd && ft_strchr(cmd, '=') != 0))
		tmp_env->hide = FALSE;
	else
		tmp_env->hide = TRUE;
	if (tmp_env->value && (ft_strcmp(tmp_env->value, value) != 0
			&& ft_strlen(value) != 0))
	{
		free(tmp_env->value);
		tmp_env->value = copy(value);
		free(tmp_env->full_path);
		tmp_env->full_path = copy(cmd);
	}
	else if (!tmp_env->value && value)
	{
		tmp_env->value = copy(value);
		free(tmp_env->full_path);
		tmp_env->full_path = copy(cmd);
	}
}

static int	verif(int i, int len_mid, t_bool append, char *str)
{
	if (str[i] < 48
		|| (str[i] > 57 && str[i] < 65)
		|| (str[i] > 90 && str[i] < 97)
		|| str[i] > 122)
	{
		if ((i != len_mid && append == FALSE)
			|| (i != len_mid + 1 && append == TRUE)
			|| (i != len_mid && append == TRUE))
		{
			if (append == FALSE && str[i] != '_'
				&& i <= len_mid)
			{
				ft_putstr_fd(": not a valid identifier\n", 2);
				return (1);
			}
			else if (append == TRUE && str[i] != '_'
				&& i < len_mid)
			{
				error_export_1(&str[i]);
				return (1);
			}
		}
	}
	return (0);
}

t_bool	set_append(char *str, int *len_mid)
{
	if (str[*len_mid - 1] == '+')
		*len_mid -= 1;
	else
		return (FALSE);
	return (TRUE);
}

int	verif_export(char *str)
{
	int		i;
	int		len_mid;
	t_bool	append;

	i = 0;
	append = TRUE;
	if (str[0] == '_' && str[1] == '\0')
		return (0);
	if (verif_error_1(str) == 1)
		return (1);
	len_mid = ft_strcspn(str, "=");
	append = set_append(str, &len_mid);
	while (str[i])
	{
		if (verif(i, len_mid, append, str) == 1)
			return (1);
		i++;
	}
	if ((len_mid == ft_strlen(str) && append == FALSE)
		|| (len_mid + 1 == ft_strlen(str) && append == TRUE))
		return (2);
	return (0);
}
