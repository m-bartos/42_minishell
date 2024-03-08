/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_assign_types.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:37:34 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/08 16:14:58 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_operator_types(t_cmd *ptr_cmd_tab)
{
	t_token	*ptr_node;

	ptr_node = ptr_cmd_tab->first_token;
	while (ptr_node != NULL)
	{
		if (!ft_strncmp(ptr_node->token, "|", 2))
			ptr_node->type = PIPE;
		else if (!ft_strncmp(ptr_node->token, "<<", 3))
			ptr_node->type = HERE_DOC;
		else if (!ft_strncmp(ptr_node->token, "<", 2))
			ptr_node->type = R_IN;
		else if (!ft_strncmp(ptr_node->token, ">>", 3))
			ptr_node->type = R_OUT_APP;
		else if (!ft_strncmp(ptr_node->token, ">", 2))
			ptr_node->type = R_OUT;
		ptr_node = ptr_node->next;
	}
}

int	assign_file_type(int type)
{
	if (type == R_IN)
		return (R_INFILE);
	else if (type == R_OUT)
		return (R_OUTFILE);
	else if (type == R_OUT_APP)
		return (R_OUTFILE_APP);
	else if (type == HERE_DOC)
		return (HERE_DOC_EOF);
	return (99);
}

void	assign_cmds_and_args(t_cmd *ptr_cmd_tab)
{
	t_token	*ptr_node;
	int		search_cmd;
	int		redir_file;

	search_cmd = 1;
	redir_file = 0;
	ptr_node = ptr_cmd_tab->first_token;
	while (ptr_node != NULL)
	{
		if (search_cmd == 1 && redir_file == 0 && !is_operator_type(ptr_node))
		{
			ptr_node->type = CMD;
			search_cmd = 0;
		}
		else if (is_redirection_type(ptr_node))
			redir_file = 1;
		else if (redir_file == 1 && !is_operator_type(ptr_node))
		{
			ptr_node->type = assign_file_type(ptr_node->prev->type);
			redir_file = 0;
		}
		else if (search_cmd == 0 && !is_operator_type(ptr_node))
			ptr_node->type = ARG;
		else if (is_pipe_type(ptr_node))
			search_cmd = 1;
		ptr_node = ptr_node->next;
	}
}

void	assign_types_to_tokens(t_cmd *ptr_cmd_tab)
{
	assign_operator_types(ptr_cmd_tab);
	assign_cmds_and_args(ptr_cmd_tab);
}
