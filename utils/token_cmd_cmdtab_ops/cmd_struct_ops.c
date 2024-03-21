/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:46:28 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/21 11:33:33 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cmd_utils.c
 * @brief Utility functions for handling command structures.
 */

#include "../../minishell.h"

/**
 * @brief Initializes a command structure with default values.
 * 
 * @param cmd The command structure to initialize.
 */
void	ft_init_cmd_struct(t_cmd *cmd)
{
	cmd->execve_cmd = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->first_token = NULL;
	cmd->last_token = NULL;
	cmd->size = 0;
}

/**
 * @brief Joins the tokens from one command to another.
 * 
 * This function appends tokens from one command structure to another.
 * 
 * @param cmd The destination command structure.
 * @param cmd_add The source command structure.
 */
void	ft_cmdjoin(t_cmd *cmd, t_cmd *cmd_add)
{
	t_token	*token;
	char	*text;
	t_type	type;

	token = cmd_add->first_token;
	while (token)
	{
		text = ft_strdup_e(token->text);
		type = token->type;
		ft_append_new_token_to_cmd(cmd, text, type);
		token = token->next;
	}
	ft_delete_cmd(cmd_add);
}

/**
 * @brief Appends a new token to a command structure.
 * 
 * @param cmd The command structure.
 * @param text The text of the token.
 * @param type The type of the token.
 */
void	ft_append_new_token_to_cmd(t_cmd *cmd, char *text, t_type type)
{
	t_token	*token;

	token = ft_create_new_token(text, type);
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

/**
 * @brief Deletes a command structure and frees its memory.
 * 
 * @param cmd The command structure to delete.
 */
void	ft_delete_cmd(t_cmd *cmd)
{
	t_token	*current_token;
	t_token	*temp_token;

	current_token = cmd->first_token;
	while (current_token != NULL)
	{
		temp_token = current_token->next;
		free(current_token->text);
		free(current_token);
		current_token = temp_token;
		temp_token = NULL;
	}
	cmd->first_token = NULL;
	cmd->last_token = NULL;
	cmd->size = 0;
}

/**
 * @brief Moves a token to the end of a command structure.
 * 
 * @param cmd The command structure.
 * @param token The token to move.
 */
void	ft_move_token(t_cmd *cmd, t_token *token)
{
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
