/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:00:27 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/01 12:02:44 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_lstsize_modif(t_argument *argument)
{
	int	counter;

	counter = 0;
	while (argument != NULL)
	{
		argument = argument->next;
		counter++;
	}
	return (counter);
}

void	setup_str(t_char_list *tmp_char, char **str)
{
	int	char_list_size;

	char_list_size = 0;
	while (tmp_char != NULL)
	{
		char_list_size++;
		tmp_char = tmp_char->next;
	}
	*str = malloc((char_list_size + 1) * sizeof(char));
}

char	**ft_setup_command(t_argument *arg)
{
	char		**str;
	t_char_list	*tmp_char;
	int			i;
	int			j;

	j = 0;
	str = malloc(((ft_lstsize_modif(arg) + 1)) * sizeof(char *));
	while (arg != NULL)
	{
		i = 0;
		tmp_char = arg->chars;
		setup_str(tmp_char, &str[j]);
		while (str[j] && tmp_char != NULL)
		{
			str[j][i] = tmp_char->value;
			tmp_char = tmp_char->next;
			i++;
		}
		if (str[j])
			str[j][i] = '\0';
		arg = arg->next;
		j++;
	}
	str[j] = NULL;
	return (str);
}
