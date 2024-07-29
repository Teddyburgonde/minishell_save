/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:01:08 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/13 22:22:15 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstclear_env(t_env **lst)
{
	t_env	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		if (tmp->full_path)
			free(tmp->full_path);
		tmp->full_path = NULL;
		if (tmp->var_name)
			free(tmp->var_name);
		tmp->var_name = NULL;
		if (tmp->value)
			free(tmp->value);
		tmp->value = NULL;
		if (tmp)
			free(tmp);
		tmp = NULL;
	}
}

t_env	*lst_search_env(char *s, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (s[0] == '$')
		{
			if (ft_strcmp(tmp->var_name, &s[1]) == 0)
				return (tmp);
		}
		else
		{
			if (ft_strcmp(tmp->var_name, s) == 0)
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
