/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_expand_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:40:13 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/23 08:56:23 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	strlen_expand(char *var_name, t_env *env, int *count, int *j)
{
	t_env	*node;

	node = lst_search_env(var_name, env);
	if (node->value != NULL && node->value[*j] != 0)
	{
		while (node->value[*j])
		{
			*count += 1;
			*j += 1;
		}
	}
	*count -= ft_strlen(var_name);
}

void	strlen_exit_code(t_vars *vars, int *count)
{
	char	*exit_code;

	exit_code = ft_itoa(vars->exit_code);
	*count = ft_strlen(exit_code) - 2;
	free(exit_code);
}

int	expand_len(t_redirection_to_expand *tmp,
	t_vars *vars, t_env *env, int i)
{
	int		j;
	int		count;
	char	*var_name;

	j = 0;
	count = 0;
	var_name = get_var_name(&tmp->arg[i]);
	if (lst_search_env(var_name, env))
		strlen_expand(var_name, env, &count, &j);
	else if (var_name[0] == '$' && var_name[1] == '?')
		strlen_exit_code(vars, &count);
	free(var_name);
	return (count);
}

int	ft_strlen_ultime(t_redirection_to_expand *tmp,
	t_env *env, t_vars *vars)
{
	int		i;
	int		count;
	t_bool	in;

	if (!tmp->arg)
		return (0);
	in = FALSE;
	i = 0;
	count = 0;
	while (tmp->arg[i])
	{
		if (tmp->arg[i] == '\'' && in == FALSE)
			in = TRUE;
		else if (tmp->arg[i] == '\'' && in == TRUE)
			in = FALSE;
		else if (tmp->arg[i] == '$' && in == FALSE)
			count += expand_len(tmp, vars, env, i);
		i++;
	}
	count += i;
	return (count);
}
