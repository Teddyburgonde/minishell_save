/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:24:05 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/13 23:42:36 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*make_var_name(char *str)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (ft_strcspn(str, "=") + 1));
	if (!result || !str)
		return (NULL);
	if (ft_strlen(str) == ft_strcspn(str, "="))
	{
		while (str[i])
		{
			result[i] = str[i];
			i++;
		}
	}
	else
	{
		while (str[i] != '=')
		{
			result[i] = str[i];
			i++;
		}
	}
	result[i] = 0;
	return (result);
}

static void	free_full_path(t_env *tmp_env, char *cmd, char *value)
{
	if (tmp_env && tmp_env->full_path
		&& ft_strchr(tmp_env->full_path, '=') == 0)
	{
		free(tmp_env->full_path);
		tmp_env->full_path = remove_plus(cmd);
		tmp_env->hide = FALSE;
	}
	else
		tmp_env->full_path = ft_strjoin_mod(tmp_env->full_path, value);
	tmp_env->value = ft_strjoin_mod(tmp_env->value, value);
}

static void	handle_export_status_0(t_env **env, t_env *tmp_env,
	char *cmd, char *var_name)
{
	t_env	*tmp;
	char	*value;

	value = make_var(cmd);
	if (!tmp_env && var_name[ft_strlen(var_name) - 1] != '+')
	{
		if (!tmp_env)
			add_new_env_var(env, cmd, var_name, FALSE);
		else
			update_env_var(tmp_env, cmd, value);
	}
	else if (var_name[ft_strlen(var_name) - 1] == '+')
	{
		var_name[ft_strlen(var_name) - 1] = 0;
		tmp = lst_search_env(var_name, *env);
		var_name[ft_strlen(var_name)] = '+';
		if (!tmp)
			add_modified_env_var(env, cmd, var_name, value);
		else
			free_full_path(tmp, cmd, value);
	}
	else
		update_env_var(tmp_env, cmd, value);
	if (value)
		free(value);
}

static void	handle_export_status_2(t_env **env,
		t_env *tmp_env, char *cmd, char *var_name)
{
	if (!tmp_env)
	{
		add_new_env_var(env, cmd, var_name, TRUE);
		tmp_env = lst_search_env(var_name, *env);
		tmp_env->value = NULL;
		tmp_env->hide = TRUE;
	}
	else
		hide_and_update_env_var(tmp_env, cmd);
}

int	export(t_env **env, char **cmd, t_vars *vars)
{
	t_env	*tmp_env;
	char	*var_name;
	int		export_status;
	int		i;

	i = 1;
	while (cmd[i] != NULL)
	{
		var_set(&var_name, &export_status, cmd[i], vars);
		if (export_status == 1)
			i++;
		if (export_status == 1)
			continue ;
		var_name = make_var_name(cmd[i]);
		tmp_env = lst_search_env(var_name, *env);
		if (export_status == 0)
			handle_export_status_0(env, tmp_env, cmd[i], var_name);
		else if (export_status == 2)
			handle_export_status_2(env, tmp_env, cmd[i], var_name);
		free_export(var_name);
		i++;
	}
	if (vars->exit_code == 1)
		return (1);
	return (0);
}
