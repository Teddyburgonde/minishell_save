/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:06:13 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/13 21:08:38 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	is_not_in_quote(char *quote, t_char_list *tmp)
{
	int		i;
	t_bool	quoted;

	i = 0;
	quoted = FALSE;
	while (quote && quote[i])
	{
		if ((quote[i] == '\'' || quote[i] == '"') && quoted == TRUE)
			quoted = FALSE;
		if ((quote[i] == '\'' || quote[i] == '"') && quoted == TRUE)
			quoted = TRUE;
		i++;
	}
	if ((tmp->value == '\'' || tmp->value == '"') && quoted == TRUE)
		quoted = FALSE;
	if ((tmp->value == '\'' || tmp->value == '"') && quoted == FALSE)
		quoted = TRUE;
	return (quoted);
}

char	which_quote(char **quote)
{
	int		i;
	char	quoted;
	t_bool	quote_in_var;

	i = 0;
	quoted = 0;
	quote_in_var = FALSE;
	while (*quote && (*quote)[i])
	{
		which_quote_is(quote, &quoted, &quote_in_var, i);
		i++;
	}
	return (quoted);
}

int	ft_lstsize_arg(t_argument *argument_to_split)
{
	int			i;
	t_char_list	*chars;

	i = 0;
	while (argument_to_split)
	{
		chars = argument_to_split->chars;
		while (chars)
		{
			chars = chars->next;
			i++;
		}
		argument_to_split = argument_to_split->next;
		i++;
	}
	return (i);
}
