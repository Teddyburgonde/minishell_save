/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:59:07 by rgobet            #+#    #+#             */
/*   Updated: 2024/07/01 11:59:51 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_export_1(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	write (2, str, ft_strlen(str));
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	error_export_2(char *str)
{
	ft_putstr_fd(
		"minishell: syntax error near unexpected token `", 2);
	write(2, &str, 1);
	write(2, "'\n", 2);
}
