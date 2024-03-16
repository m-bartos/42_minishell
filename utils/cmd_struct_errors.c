/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:23:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/16 20:41:36 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_redirection_error(t_cmd *cmd, char *text)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(text, STDERR);
	ft_putstr_fd("'\n", STDERR);
	ft_delete_cmd(cmd);
	printf(RESET);
	exit(2);
}

void	check_redirection_errors(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token->next;
	while (token != NULL)
	{
		if (((is_operator_type(token) || is_pipe_type(token))
				&& is_redirection_type(token->prev))
			|| (is_pipe_type(token) && is_pipe_type(token->prev)))
		{
			exit_redirection_error(cmd, token->text);
		}
		token = token->next;
	}
	if (is_redirection_type(cmd->last_token))
		exit_redirection_error(cmd, "newline");
}
