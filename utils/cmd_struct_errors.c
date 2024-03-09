/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:23:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/09 10:25:15 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_double_redirect(t_cmd *ptr_cmd, char *line, char *prompt)
{
	t_token	*ptr_node;

	ptr_node = ptr_cmd->first_token;
	ptr_node = ptr_node->next;
	while (ptr_node != NULL)
	{
		if (((is_operator_type(ptr_node) || is_pipe_type(ptr_node))
			&& is_redirection_type(ptr_node->prev)) ||
			(is_pipe_type(ptr_node) && is_pipe_type(ptr_node->prev)))
		{
			printf("minishell: syntax error near unexpected token '%s'\n", 
				ptr_node->text);
			free_program(ptr_cmd, line, prompt);
			exit(0);
		}
		ptr_node = ptr_node->next;
	}
	if (is_redirection_type(ptr_cmd->last_token))
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		free_program(ptr_cmd, line, prompt);
		exit(0);
	}
}