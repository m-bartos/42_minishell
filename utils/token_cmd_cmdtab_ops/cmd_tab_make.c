/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:22:34 by mbartos           #+#    #+#             */
/*   Updated: 2024/04/16 12:39:02 by mbartos          ###   ########.fr       */
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

/**
 * @brief Deletes empty tokens from a command table.
 *
 * This function iterates through each command in the command table and checks
 * for empty token text. If an empty text (NULL) is found, it deletes
 * the token from the command.
 *
 * @param cmd_tab Pointer to the command table structure.
*/
void	delete_empty_tokens_in_cmd_tab(t_cmd_tab *cmd_tab)
{
	t_cmd	*cmd;
	t_token	*token;
	t_token	*temp_next_token;

	if (!cmd_tab)
		return ;
	cmd = cmd_tab->first_cmd;
	while (cmd != NULL)
	{
		token = cmd->first_token;
		while (token != NULL)
		{
			temp_next_token = token->next;
			if (token->text == NULL)
				ft_delete_token(cmd, token);
			token = temp_next_token;
		}
		cmd = cmd->next;
	}
}

/**
 * @brief Deletes pipe tokens from a command table.
 *
 * This function iterates through each command in the command table and checks
 * for pipe tokens. If an pipe token is found, the function deletes the token
 * from the command.
 *
 * @param cmd_tab Pointer to the command table structure.
*/
void	delete_pipes_in_cmd_tab(t_cmd_tab *cmd_tab)
{
	t_cmd	*cmd;
	t_token	*token;
	t_token	*temp_next_token;

	if (!cmd_tab)
		return ;
	cmd = cmd_tab->first_cmd;
	while (cmd != NULL)
	{
		token = cmd->first_token;
		while (token != NULL)
		{
			temp_next_token = token->next;
			if (token->type == PIPE)
				ft_delete_token(cmd, token);
			token = temp_next_token;
		}
		cmd = cmd->next;
	}
}

/**
 * @brief Checks and fills empty commands with an CMD_ERR token.
 *
 * This function iterates through each command in the command table.
 * If a command has no tokens (i.e., its size is 0), it appends a new
 * CMD_ERR token to the command to indicate an error.
 *
 * @param cmd_tab Pointer to the command table structure.
*/
void	check_and_fill_empty_cmds_in_cmd_tab(t_cmd_tab *cmd_tab)
{
	t_cmd	*cmd;

	if (!cmd_tab)
		return ;
	cmd = cmd_tab->first_cmd;
	while (cmd != NULL)
	{
		if (cmd->size == 0)
			ft_append_new_token_to_cmd(cmd, NULL, CMD_ERR);
		cmd = cmd->next;
	}
}
