/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split_argument_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:01:11 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/23 09:14:15 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_no_quote_arg(t_char_list **tmp_char,
	t_char_list **splitted_chars, char quote)
{
	t_char_list	*arg;

	arg = NULL;
	if (*tmp_char && (*tmp_char)->value != quote)
	{
		arg = lst_new_char_list();
		if (!arg)
			return ;
		arg->value = (*tmp_char)->value;
		arg->was_in_a_variable = (*tmp_char)->was_in_a_variable;
		ft_lstadd_back_char_list(splitted_chars, arg);
		(*tmp_char)->last_pos = FALSE;
		*tmp_char = (*tmp_char)->next;
	}
}

int	skip_useless_quote(t_char_list **tmp)
{
	char		quote;
	t_char_list	*tmp_char;

	quote = 0;
	tmp_char = *tmp;
	if (tmp_char && (tmp_char->value == '"'
			|| tmp_char->value == '\''))
	{
		quote = tmp_char->value;
		if (tmp_char->next && quote == tmp_char->next->value)
		{
			*tmp = (*tmp)->next->next;
			return (1);
		}
	}
	return (0);
}

int	function_verif_quote(t_char_list **tmp_char, char **quote,
	t_bool *quote_in_var)
{
	int		i;
	char	quoted;
	t_bool	state;

	i = 0;
	quoted = 0;
	state = *quote_in_var;
	while (state == FALSE && skip_useless_quote(tmp_char) == 1)
		continue ;
	if (!(*tmp_char))
		return (*quote_in_var);
	while ((*quote) && (*quote)[i])
		i++;
	((*quote))[i] = (*tmp_char)->value;
	i = 0;
	*quote_in_var = FALSE;
	while ((*quote) && (*quote)[i])
	{
		if ((*tmp_char)->was_in_a_variable == FALSE)
			which_quote_is(quote, &quoted, quote_in_var, i);
		i++;
	}
	verif_multi_quote(tmp_char, quote, quote_in_var, state);
	return (*quote_in_var);
}

static t_argument	*ft_get_last_pos(t_argument *lst)
{
	t_char_list	*tmp;

	while (lst)
	{
		tmp = lst->chars;
		while (tmp)
		{
			if (tmp->last_pos == TRUE)
				return (lst);
			tmp = tmp->next;
		}
		lst = lst->next;
	}
	return (NULL);
}

t_bool	init_function(char **quote, t_argument **tmp,
	t_argument	**splitted_arguments, t_argument *argument_to_split)
{
	(void)quote;
	*splitted_arguments = lst_new_argument();
	if (!*splitted_arguments)
		return (0);
	*tmp = argument_to_split;
	*tmp = ft_get_last_pos(*tmp);
	if (*tmp == NULL)
		*tmp = argument_to_split;
	return (FALSE);
}
