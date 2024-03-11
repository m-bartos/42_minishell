/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:23:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/11 12:56:42 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_redirection_errors(t_cmd *ptr_cmd)
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
			ft_delete_cmd(ptr_cmd);
			exit(0);
		}
		ptr_node = ptr_node->next;
	}
	if (is_redirection_type(ptr_cmd->last_token))
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		ft_delete_cmd(ptr_cmd);
		exit(0);
	}
}