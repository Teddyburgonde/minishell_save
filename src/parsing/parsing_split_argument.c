/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split_argument.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:56:30 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/13 21:08:20 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	fill_in_quote_arg(t_char_list **tmp_char,
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
	else if (*tmp_char && (*tmp_char)->value == quote)
		*tmp_char = (*tmp_char)->next;
}

static void	fill_arg(t_char_list **tmp_char,
	t_char_list **splitted_chars)
{
	t_char_list	*arg;

	arg = NULL;
	if (*tmp_char)
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

void	fill_expanded_arg(t_char_list **tmp_char,
	t_char_list **splitted_chars, char *quote)
{
	while (*tmp_char && (*tmp_char)->was_in_a_variable == TRUE)
	{
		if ((*tmp_char)->value == SPACE
			|| (*tmp_char)->value == NEWLINE
			|| (*tmp_char)->value == TAB)
			break ;
		if (*quote && *quote == (*tmp_char)->value)
			break ;
		fill_arg(tmp_char, splitted_chars);
	}
	if (*tmp_char && *quote && *quote != (*tmp_char)->value
		&& (*tmp_char)->value != SPACE
		&& (*tmp_char)->value != NEWLINE
		&& (*tmp_char)->value != TAB)
		fill_arg(tmp_char, splitted_chars);
}

void	fill_not_expand_arg(t_char_list **tmp_char,
	t_char_list **splitted_chars, t_bool *in_quote, char **quote)
{
	int	i;

	while (*tmp_char && !(((*tmp_char)->value == SPACE
				|| (*tmp_char)->value == TAB
				|| (*tmp_char)->value == NEWLINE)
			&& is_not_in_quote(*quote, *tmp_char) == FALSE))
	{
		i = 0;
		while (*tmp_char && *in_quote == FALSE)
		{
			i++;
			if (function_verif_quote(tmp_char, quote, in_quote) == 1)
				continue ;
			fill_no_quote_arg(tmp_char, splitted_chars, which_quote(quote));
		}
		while (*tmp_char && *in_quote == TRUE)
		{
			if (!i && function_verif_quote(tmp_char, quote, in_quote) == 0)
				continue ;
			fill_in_quote_arg(tmp_char, splitted_chars, which_quote(quote));
		}
	}
}

int	ft_split_argument(t_argument *argument_to_split,
	t_argument **args)
{
	char		*quote;
	t_char_list	*tmp_char;
	t_argument	*tmp;
	t_argument	*splitted_arguments;
	t_bool		in_quote;

	in_quote = init_function(&quote, &tmp, &splitted_arguments,
			argument_to_split);
	quote = ft_calloc(sizeof(char),
			ft_lstsize_arg(argument_to_split) + 1);
	if (!quote)
		return (1);
	set_var(tmp, &tmp_char);
	while (tmp_char && !((tmp_char->value == SPACE
				|| tmp_char->value == TAB || tmp_char->value == NEWLINE)
			&& is_not_in_quote(quote, tmp_char) == FALSE))
	{
		fill_not_expand_arg(&tmp_char, &splitted_arguments->chars,
			&in_quote, &quote);
	}
	ft_lstadd_back_argument(args, splitted_arguments);
	free(quote);
	if (set_last_point(&tmp, &tmp_char) == 0)
		return (0);
	return (1);
}
