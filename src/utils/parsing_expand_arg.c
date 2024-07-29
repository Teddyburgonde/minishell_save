/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:21:36 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/26 14:26:38 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	rest_argument(t_char_list **tmp_char,
	t_char_list **splitted_chars, char *quote)
{
	t_bool		in_quote;
	t_char_list	*arg;

	arg = NULL;
	in_quote = FALSE;
	while (*tmp_char && (*tmp_char)->value != ' '
		&& (*tmp_char)->value != '\t' && (*tmp_char)->value != '\n'
		&& in_quote == FALSE)
	{
		fill_not_expand_arg(tmp_char, splitted_chars, &in_quote, &quote);
		fill_expanded_arg(tmp_char, splitted_chars, quote);
	}
}

int	set_last_point(t_argument **tmp, t_char_list **tmp_char)
{
	while (*tmp_char && ((*tmp_char)->value == SPACE
			|| (*tmp_char)->value == TAB || (*tmp_char)->value == NEWLINE))
		*tmp_char = (*tmp_char)->next;
	if (*tmp_char == NULL)
	{
		*tmp = (*tmp)->next;
		if (*tmp != NULL)
			*tmp_char = (*tmp)->chars;
	}
	if (*tmp == NULL)
		return (0);
	(*tmp_char)->last_pos = TRUE;
	return (1);
}

void	set_var(t_argument *tmp, t_char_list **tmp_char)
{
	*tmp_char = tmp->chars;
	while (*tmp_char && (*tmp_char)->last_pos == FALSE)
		*tmp_char = (*tmp_char)->next;
	(*tmp_char)->last_pos = FALSE;
}

t_bool	is_not_in_double_quote(char *str, int x)
{
	int		i;
	t_bool	in_db_quote;

	i = 0;
	in_db_quote = FALSE;
	while (str && str[i])
	{
		if (str[i] == '"' && in_db_quote == FALSE)
			in_db_quote = TRUE;
		else if (str[i] == '"' && in_db_quote == TRUE)
			in_db_quote = FALSE;
		if (i == x)
			return (in_db_quote);
		i++;
	}
	return (in_db_quote);
}

void	*close_quote(const char *argument, int *i,
	t_bool in_quote, t_char_list **chars)
{
	t_char_list	*tmp;

	tmp = lst_new_char_list();
	if (!tmp)
		return (NULL);
	in_quote = FALSE;
	tmp->value = argument[*i];
	ft_lstadd_back_char_list(chars, tmp);
	*i += 1;
	return ((void *)1);
}
