/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split_argument_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:01:11 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/13 18:53:45 by rgobet           ###   ########.fr       */
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

int	function_verif_quote(t_char_list **tmp_char, char **quote,
	t_bool *quote_in_var)
{
	int		i;
	char	quoted;

	i = 0;
	quoted = 0;
	while ((*quote) && (*quote)[i])
		i++;
	((*quote))[i] = (*tmp_char)->value;
	i = 0;
	while ((*quote) && (*quote)[i])
	{
		which_quote_is(quote, &quoted, quote_in_var, i);
		i++;
	}
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
	t_bool	in_quote;

	in_quote = FALSE;
	(void)quote;
	*splitted_arguments = lst_new_argument();
	if (!*splitted_arguments)
		return (0);
	*tmp = argument_to_split;
	*tmp = ft_get_last_pos(*tmp);
	if (*tmp == NULL)
		*tmp = argument_to_split;
	return (in_quote);
}
