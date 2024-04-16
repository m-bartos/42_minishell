/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:22:34 by mbartos           #+#    #+#             */
/*   Updated: 2024/04/16 12:09:02 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Constructs a command table from a command.
 * 
 * This function constructs a command table from a given command by iterating
 * through its tokens and organizing them into separate commands within the
 * command table. It ensures that each command is correctly positioned within
 * the command table, taking into account pipe operators as separators between
 * commands.
 * 
 * @param cmd_tab Pointer to the command table to populate.
 * @param cmd Pointer to the command containing tokens to be organized.
 */
void	make_cmd_tab_from_cmd(t_cmd_tab *cmd_tab, t_cmd *cmd)
{
	t_token	*token;
	t_token	*temp_token;

	token = cmd->first_token;
	ft_append_new_cmd_to_tab(cmd_tab);
	while (token != NULL)
	{
		temp_token = token->next;
		if (is_pipe_type(token->prev))
			ft_append_new_cmd_to_tab(cmd_tab);
		ft_move_token(cmd_tab->last_cmd, token);
		cmd->size--;
		token = temp_token;
	}
	ft_init_cmd_struct(cmd);
}
