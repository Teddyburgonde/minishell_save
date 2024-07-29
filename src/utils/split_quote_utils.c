/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:08:50 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/23 14:41:46 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	special_case_quote(t_char_list **tmp_char, char **quote,
	int i)
{
	if (*tmp_char)
		(*tmp_char) = (*tmp_char)->next;
	if (*tmp_char)
		(*quote)[i] = (*tmp_char)->value;
}

void	verif_multi_quote(t_char_list **tmp_char, char **quote,
	t_bool *quote_in_var, t_bool state)
{
	int	i;

	i = ft_strlen(*quote);
	if (*tmp_char && (*tmp_char)->was_in_a_variable == TRUE
		&& *quote_in_var == FALSE)
		*quote_in_var = state;
	if (state != *quote_in_var)
	{
		special_case_quote(tmp_char, quote, i);
		if (*quote_in_var == FALSE)
			*quote_in_var = is_not_in_quote(*quote, *tmp_char);
	}
	if (*tmp_char && (*tmp_char)->next
		&& state == TRUE && *quote_in_var == FALSE
		&& ((*tmp_char)->next->value == '"'
			|| (*tmp_char)->next->value == '\''))
	{
		*quote_in_var = TRUE;
		special_case_quote(tmp_char, quote, i + 1);
	}
	if (state != *quote_in_var && *tmp_char && (*tmp_char)->next
		&& state == TRUE && ((*tmp_char)->next->value != '"'
			|| (*tmp_char)->next->value != '\'')
		&& ((*tmp_char)->value == '"' || (*tmp_char)->value == '\''))
		special_case_quote(tmp_char, quote, i);
}

void	which_quote_is(char **quote, char *quoted,
	t_bool *quote_in_var, int i)
{
	if ((*quote)[i] == '"' && (*quoted == (*quote)[i]
		|| *quoted == 0) && *quote_in_var == TRUE)
	{
		*quoted = 0;
		*quote_in_var = FALSE;
	}
	else if ((*quote)[i] == '"' && (*quoted == (*quote)[i]
		|| *quoted == 0) && *quote_in_var == FALSE)
	{
		*quoted = (*quote)[i];
		*quote_in_var = TRUE;
	}
	if ((*quote)[i] == '\'' && (*quoted == (*quote)[i]
		|| *quoted == 0) && *quote_in_var == TRUE)
	{
		*quoted = 0;
		*quote_in_var = FALSE;
	}
	else if ((*quote)[i] == '\'' && (*quoted == (*quote)[i]
		|| *quoted == 0) && *quote_in_var == FALSE)
	{
		*quoted = (*quote)[i];
		*quote_in_var = TRUE;
	}
}

int	white_space(t_char_list **tmp_char)
{
	if ((*tmp_char) && ((*tmp_char)->value == SPACE
			|| (*tmp_char)->value == TAB
			|| (*tmp_char)->value == NEWLINE))
		return (1);
	return (0);
}
