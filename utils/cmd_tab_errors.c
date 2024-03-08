/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:23:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/08 12:43:23 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_double_redirect(t_cmd_tab *ptr_cmd_tab)
{
	t_node	*ptr_node;

	ptr_node = ptr_cmd_tab->first_node;
	ptr_node = ptr_node->next;
	while (ptr_node != NULL)
	{
		if ((is_operator_type(ptr_node) || is_pipe_type(ptr_node))
			&& is_redirection_type(ptr_node->prev))
		{
			printf("minishell: syntax error near unexpected token '%s'\n", 
				ptr_node->token);
			return (1);
		}
		ptr_node = ptr_node->next;
	}
	return (0);
}