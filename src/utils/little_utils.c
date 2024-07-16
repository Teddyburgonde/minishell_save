/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:27:46 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/12 13:00:41 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*new_char(const char *argument, int *i, t_char_list **chars)
{
	t_char_list	*tmp;

	tmp = NULL;
	tmp = lst_new_char_list();
	if (!tmp)
		return (NULL);
	tmp->value = argument[*i];
	ft_lstadd_back_char_list(chars, tmp);
	*i += 1;
	return ((void *)1);
}

t_bool	need_to_be_expand_hd(char *str, t_env *env)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			var_name = get_var_name(&str[i]);
			if (lst_search_env(var_name, env) || ft_strcmp(var_name, "$?") == 0
				|| (var_name[0] == '$' && var_name[1] == '?'))
			{
				free (var_name);
				return (TRUE);
			}
			else
			{
				free (var_name);
				return (2);
			}
		}
		i++;
	}
	return (FALSE);
}

void	refresh_index(char *str, int *i, int *count, int j)
{
	if (str[*i] && str[*i] != '$')
	{
		*i += 1;
		*count += 1;
		if (*i > 0 && str[*i - 2] == '$')
			*count += 1;
	}
	*count += j;
}

void	init_expand(int *i, int *j, int *t, char **var_name)
{
	*i = 0;
	*j = 0;
	*t = 0;
	*var_name = NULL;
}

void	increment_index(int *i, int *t, char *tmp)
{
	if ((tmp[*t] && tmp[*t] != '$') || *t == 0)
		*t += 1;
	*i += 1;
}
