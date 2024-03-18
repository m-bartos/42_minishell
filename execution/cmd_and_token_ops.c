/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_token_ops.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:57:52 by orezek            #+#    #+#             */
/*   Updated: 2024/03/18 19:01:27 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Adds a command to the top of the command table.
 *
 * Performs a push operation on the command table, adding a command to the top.
 * This modifies the command table to follow a FIFO ordering.
 *
 * @param cmd_table Pointer to the command table.
 * @param cmd Pointer to the command to add.
 */

void	ft_push_cmd_to_tab(t_cmd_tab *cmd_table, t_cmd *cmd)
{
	if (cmd_table == NULL && cmd == NULL)
		return ;
	if (cmd_table->first_cmd == NULL)
	{
		cmd_table->first_cmd = cmd;
		cmd_table->last_cmd = cmd;
		cmd->next = NULL;
		cmd->prev = NULL;
	}
	else
	{
		cmd->prev = NULL;
		cmd->next = cmd_table->first_cmd;
		cmd_table->first_cmd->prev = cmd;
		cmd_table->first_cmd = cmd;
	}
	cmd_table->size++;
}

/**
 * @brief Adds a command to the end of the command table.
 *
 * Performs an enqueue operation on the command table,
 * adding a command to the end.
 * This ensures commands are executed in a FILO order.
 *
 * @param cmd_table Pointer to the command table.
 * @param cmd Pointer to the command to add.
 */

void	ft_append_cmd_to_tab(t_cmd_tab *cmd_table, t_cmd *cmd)
{
	if (cmd_table == NULL && cmd == NULL)
		return ;
	if (cmd_table->first_cmd == NULL)
	{
		cmd_table->first_cmd = cmd;
		cmd_table->last_cmd = cmd;
		cmd->next = NULL;
		cmd->prev = NULL;
	}
	else
	{
		cmd->prev = cmd_table->last_cmd;
		cmd->next = NULL;
		cmd_table->last_cmd->next = cmd;
		cmd_table->last_cmd = cmd;
	}
	cmd_table->size++;
}

/**
 * @brief Creates a new token with specified text and type.
 *
 * Allocates and initializes a new token with the given text and type.
 *
 * @param text Text for the token.
 * @param type Type of the token.
 * @return Pointer to the newly created token, or NULL on failure.
 */

t_token	*ft_create_token(char *text, t_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ft_init_token(token);
	token->text = text;
	token->type = type;
	return (token);
}

/**
 * @brief Appends a token to a command with text and type.
 *
 * Adds a token to a command's token list. It creates a new token
 * with the given text and type, then appends it to the command.
 *
 * @param cmd Pointer to the command.
 * @param text Text for the new token.
 * @param type Type of the new token.
 */

void	ft_append_token_to_cmd(t_cmd *cmd, char *text, t_type type)
{
	t_token	*token;

	token = ft_create_token(text, type);
	if (!cmd || !token)
		return ;
	if (cmd->first_token == NULL)
	{
		cmd->first_token = token;
		cmd->last_token = token;
		token->next = NULL;
		token->prev = NULL;
	}
	else
	{
		token->prev = cmd->last_token;
		token->next = NULL;
		cmd->last_token->next = token;
		cmd->last_token = token;
	}
	cmd->size++;
}
