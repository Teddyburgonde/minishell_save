/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:23:44 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/11 09:56:47 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_redirection_parsing	*unclose_quote(char *str,
	t_redirection_parsing *result)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	if (str && (str[i] == '\'' || str[i] == '"'))
	{
		quote = str[i];
		if (str[i])
			i++;
	}
	while (str && str[i] && str[i] != quote)
	{
		i++;
		if (str[i] == quote)
			result->did_succeed = TRUE;
		else
			result->did_succeed = FALSE;
	}
	if (result->did_succeed == FALSE)
		ft_putstr_fd("Error: quotes are not closed !\n", 2);
	return (result);
}

t_redirection_parsing	*parse_redirection(char *str)
{
	t_redirection_parsing	*redirection_result;

	redirection_result = initialize_redirection_parsing_result();
	if (!redirection_result)
		return (NULL);
	str = skip_spaces(str);
	redirection_result = ft_verif_redirection(str, redirection_result);
	if (redirection_result->did_succeed == FALSE)
		return (redirection_result);
	str = set_remaining_line(str);
	if (str && str[0] == '|')
	{
		error_message_pipe(redirection_result, str);
		return (redirection_result);
	}
	redirection_result = unclose_quote(str, redirection_result);
	if (redirection_result->did_succeed == FALSE)
		return (redirection_result);
	redirection_result->redirection->arg = ft_strjoin_file(
			str);
	str = ft_skip_arg(str, " \n\t|><");
	redirection_result->remaining_line = str;
	return (redirection_result);
}

t_redirection_parsing	*ft_verif_redirection(char *str,
	t_redirection_parsing *redirection_result)
{
	if (str[0] == '>' && str[1] == '>')
	{
		if (double_redirection(str))
			redirection_result->did_succeed = FALSE;
		redirection_result->redirection->e_type = REDIRECTION_APPEND;
	}
	else if (str[0] == '<' && str[1] == '<')
	{
		if (double_redirection(str))
			redirection_result->did_succeed = FALSE;
		redirection_result->redirection->e_type = REDIRECTION_HEREDOC;
	}
	else if (str[0] == '<')
	{
		if (single_redirection(str))
			redirection_result->did_succeed = FALSE;
		redirection_result->redirection->e_type = REDIRECTION_INFILE;
	}
	else if (str[0] == '>')
	{
		if (single_redirection(str))
			redirection_result->did_succeed = FALSE;
		redirection_result->redirection->e_type = REDIRECTION_OUTFILE;
	}
	return (redirection_result);
}

t_argument_parsing	*parse_quote(const char *remaining_line,
	t_argument_parsing *result)
{
	if (remaining_line[0] == '\'')
	{
		result->argument->content = ft_strjoin_quoted_arg(
				result->argument->content, remaining_line, "\'");
		remaining_line = skip_quote(remaining_line, '\'', result);
		result->remaining_line = remaining_line;
		if (result->did_succeed == FALSE)
			return (result);
	}
	else if (remaining_line[0] == '"')
	{
		result->argument->content = ft_strjoin_quoted_arg(
				result->argument->content, remaining_line, "\"");
		remaining_line = skip_quote(remaining_line, '"', result);
		result->remaining_line = remaining_line;
		if (result->did_succeed == FALSE)
			return (result);
	}
	result->remaining_line = remaining_line;
	return (result);
}

t_command_parsing_result	*ft_redirections_arguments(char **remaining_line,
	t_command_parsing_result *result,
	t_redirection_parsing *redirection_result,
	t_argument_parsing *argument_result)
{
	if ((*remaining_line)[0] == '>' || (*remaining_line)[0] == '<')
	{
		result = redirections(result, *remaining_line, redirection_result);
		*remaining_line = (char *)result->remaining_line;
		*remaining_line = skip_spaces(*remaining_line);
	}
	else
	{
		result = arguments(result, argument_result, *remaining_line);
		*remaining_line = (char *)result->remaining_line;
		*remaining_line = skip_spaces(*remaining_line);
	}
	return (result);
}
