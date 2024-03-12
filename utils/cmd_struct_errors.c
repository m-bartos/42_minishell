/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:23:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/12 12:33:04 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_redirection_errors(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token->next;
	while (token != NULL)
	{
		if (((is_operator_type(token) || is_pipe_type(token))
			&& is_redirection_type(token->prev)) ||
			(is_pipe_type(token) && is_pipe_type(token->prev)))
		{
			printf("minishell: syntax error near unexpected token '%s'\n", 
				token->text);
			ft_delete_cmd(cmd);
			printf(RESET);
			exit(0);
		}
		token = token->next;
	}
	if (is_redirection_type(cmd->last_token))
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		ft_delete_cmd(cmd);
		printf(RESET);
		exit(0);
	}
}