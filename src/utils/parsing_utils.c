/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:28:15 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/11 09:53:36 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin_arg(char *s1, const char *s2)
{
	char	*tab;

	if (!s1 && !s2)
		return (0);
	tab = allocate_and_prepare_tab(s1, s2);
	if (!tab)
		return (NULL);
	copy_and_concatenante(tab, s1, s2);
	if (s1)
		free(s1);
	return (tab);
}

char	*ft_strjoin_file(char *s1)
{
	char	*tab;
	int		len;

	if (!s1)
		return (0);
	tab = allocate_tab(s1, &len);
	if (!tab)
		return (NULL);
	copy_content(tab, s1, len);
	return (tab);
}

char	*ft_strjoin_until(char *s1, const char *s2, char *reject)
{
	char	*tab;

	if (!s1 && !s2)
		return (0);
	tab = ft_allocate_tab(s1, s2, reject);
	if (!tab)
		return (NULL);
	copy_tab(tab, s1, s2, reject);
	if (s1)
		free(s1);
	return (tab);
}

char	*ft_strjoin_quoted_arg(char *s1, const char *s2, char *reject)
{
	char	*tab;

	if (!s1 && !s2)
		return (NULL);
	tab = allocate_tab_quoted(s1, s2, reject);
	if (!tab)
		return (NULL);
	copy_and_concatenate_quoted_arg(tab, s1, s2, reject);
	if (s1)
		free(s1);
	return (tab);
}

void	error_message_pipe(t_redirection_parsing *redirection_result,
	char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	write(2, str, 1);
	ft_putstr_fd("'\n", 2);
	redirection_result->did_succeed = FALSE;
}
