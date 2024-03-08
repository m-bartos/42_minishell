/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:23:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/08 13:40:04 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_double_redirect(t_cmd_tab *cmd_tab, char *line, char *prompt)
{
	t_node	*ptr_node;

	ptr_node = cmd_tab->first_node;
	ptr_node = ptr_node->next;
	while (ptr_node != NULL)
	{
		if ((is_operator_type(ptr_node) || is_pipe_type(ptr_node))
			&& is_redirection_type(ptr_node->prev))
		{
			printf("minishell: syntax error near unexpected token '%s'\n", 
				ptr_node->token);
			free_program(cmd_tab, line, prompt);
			exit(0);
		}
		ptr_node = ptr_node->next;
	}
}