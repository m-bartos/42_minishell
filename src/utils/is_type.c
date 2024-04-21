/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:18:05 by mbartos           #+#    #+#             */
/*   Updated: 2024/04/21 20:22:26 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_type(t_token *token)
{
	if (token == NULL)
		return (0);
	if (token->type == PIPE)
		return (1);
	return (0);
}

int	is_redirection_type(t_token *token)
{
	int	type;

	type = token->type;
	if (type == R_IN || type == HERE_DOC || type == R_OUT || type == R_OUT_APP)
		return (1);
	return (0);
}

int	is_operator_type(t_token *token)
{
	if (is_pipe_type(token) || is_redirection_type(token))
		return (1);
	return (0);
}
