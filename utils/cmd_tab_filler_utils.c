/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_filler_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:18:05 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/08 10:48:59 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_pipe_type(t_node *ptr_node)
{
	int	type;

	type = ptr_node->type;
	if (type == PIPE)
		return (1);
	return (0);
}

int	is_redirection_type(t_node *ptr_node)
{
	int	type;

	type = ptr_node->type;
	if (type == R_IN || type == HERE_DOC
		|| type == R_OUT || type == R_OUT_APP)
		return (1);
	return (0);
}

int	is_operator_type(t_node *ptr_node)
{
	if (is_pipe_type(ptr_node) || is_redirection_type(ptr_node))
		return (1);
	return (0);
}

int	is_in_single_quotes(t_node *ptr_node)
{
	char	*token;
	int		len;

	token = ptr_node->token;
	len = ft_strlen(token);
	if (token[0] == '\'' && token[len - 1] == '\'')
		return (1);
	return (0);
}

int	is_in_double_quotes(t_node *ptr_node)
{
	char	*token;
	int		len;

	token = ptr_node->token;
	len = ft_strlen(token);
	if (token[0] == '"' && token[len - 1] == '"')
		return (1);
	return (0);
}
