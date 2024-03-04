/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_assign_types.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:37:34 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/04 14:38:00 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_operator_types(t_command_table *ptr_cmd_tab)
{
	t_node	*ptr_node;

	ptr_node = ptr_cmd_tab->first_node;
	while (ptr_node != NULL)
	{
		if (!ft_strncmp(ptr_node->token, "|", 2))
			ptr_node->type = PIPE;
		else if (!ft_strncmp(ptr_node->token, "<<", 3))
			ptr_node->type = HERE_DOC;
		else if (!ft_strncmp(ptr_node->token, "<", 2))
			ptr_node->type = R_IN;
		else if (!ft_strncmp(ptr_node->token, ">>", 3))
			ptr_node->type = R_OUT_APPND;
		else if (!ft_strncmp(ptr_node->token, ">", 2))
			ptr_node->type = R_OUT;
		ptr_node = ptr_node->next;
	}
}

void	assign_cmds_and_args(t_command_table *ptr_cmd_tab)
{
	t_node	*ptr_node;
	int		search_cmd;
	int		redir_file;

	search_cmd = 1;
	redir_file = 0;
	ptr_node = ptr_cmd_tab->first_node;
	while (ptr_node != NULL)
	{
		if (search_cmd == 1 && redir_file == 0 && !is_operator_type(ptr_node))
		{
			ptr_node->type = COMMAND;
			search_cmd = 0;
		}
		else if (is_redirection_type(ptr_node))
			redir_file = 1;
		else if ((search_cmd == 0 && !is_operator_type(ptr_node))
			|| (search_cmd == 1 && redir_file == 1 && !is_operator_type(ptr_node)))
		{
			ptr_node->type = ARG;
			redir_file = 0;
		}
		else if (is_pipe_type(ptr_node))
			search_cmd = 1;
		ptr_node = ptr_node->next;
	}
}

void	assign_types_to_tokens(t_command_table *ptr_cmd_tab)
{
	assign_operator_types(ptr_cmd_tab);
	assign_cmds_and_args(ptr_cmd_tab);
}
