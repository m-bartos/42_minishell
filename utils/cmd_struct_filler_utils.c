/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_filler_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:18:05 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/12 12:37:20 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	is_in_single_quotes(t_token *token)
{
	char	*text;
	int		length;

	text = token->text;
	length = ft_strlen(text);
	if (text[0] == '\'' && text[length - 1] == '\'')
		return (1);
	return (0);
}

int	is_in_double_quotes(t_token *token)
{
	char	*text;
	int		length;

	text = token->text;
	length = ft_strlen(text);
	if (text[0] == '\"' && text[length - 1] == '\"')
		return (1);
	return (0);
}
