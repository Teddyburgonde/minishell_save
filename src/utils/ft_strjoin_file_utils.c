/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_file_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:00:23 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/22 07:53:02 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*allocate_tab(const char *s1, int *len)
{
	char	*tab;
	size_t	length;

	if (s1[0] != '\'' && s1[0] != '"')
	{
		length = ft_strcspn(s1, "<>| \n\t");
		tab = malloc((1 + length) * sizeof(char));
		*len = length;
	}
	else
	{
		length = ft_strcspn(&s1[1], "<>| \n\t");
		tab = malloc((3 + length) * sizeof(char));
		*len = length;
	}
	return (tab);
}

void	copy_content(char *tab, const char *s1, int len)
{
	int	i;

	i = 0;
	while (s1 && s1[i] && i < len + 2
		&& s1[i] != SPACE && s1[i] != NEWLINE && s1[i] != TAB
		&& s1[i] != '|' && s1[i] != '>' && s1[i] != '<')
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = 0;
}
