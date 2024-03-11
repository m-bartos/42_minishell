/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:46:28 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/11 12:04:56 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// initiate command table
/*
Declare the command table to be in the stack not heap! The compiler takes care of the memmory.
Example:
t_cmd cmd;
ft_init_cmd_struct(&cmd)
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

// rotates token from top to bottom and promotes the second to be first
void	ft_rotate_token(t_cmd *cmd)
{
	t_token	*temp_first_next;
	// prevents any action if there is nothing to rotata = cmd is empty or has one token
	if (cmd->size > 1)
	{
		temp_first_next = cmd->first_token->next;
		cmd->last_token->next = cmd->first_token;
		cmd->first_token->next = NULL;
		cmd->first_token->prev = cmd->last_token;
		cmd->last_token = cmd->first_token;
		temp_first_next->prev = NULL;
		cmd->first_token = temp_first_next;
	}
}
// insert token on top of a stack
void	ft_push_token(t_cmd *cmd, char *token_text, t_type token_type)
{
	t_token	*ptr_token;

	ptr_token = malloc(sizeof(t_token));
	if (!ptr_token)
		return ;
	ptr_token->text = token_text;
	ptr_token->next = cmd->first_token;
	ptr_token->prev = NULL;
	ptr_token->type = token_type;
	if (cmd->first_token != NULL)
		cmd->first_token->prev = ptr_token;
	if (cmd->first_token == NULL)
		cmd->last_token = ptr_token;
	cmd->first_token = ptr_token;
	cmd->size++;
}

/*
Use it for actual token insertion.
Two action function:
	Inserts a node to cmd on the top = first node
	Moves the inserted node to the bottom and promotes the second to be first
When applied to a loop it will always keep the very first inserted node to be first node in the cmd
*/
void	ft_push_rotate_token(t_cmd *cmd, char *token_text, t_type token_type)
{
	ft_push_token(cmd, token_text, token_type);
	ft_rotate_token(cmd);
}

// cleanup method
void	ft_delete_cmd(t_cmd *cmd)
{
	t_token	*current;
	t_token	*temp;

	current = cmd->first_token;
	while (current != NULL)
	{
		temp = current->next;
		free(current->text);
		free(current);
		current = temp;
		temp = NULL;
	}
	cmd->first_token = NULL;
	cmd->last_token = NULL;
	cmd->size = 0;
}

void	ft_move_token(t_cmd *cmd, t_token *ptr_token)
{
	ptr_token->next = cmd->first_token;
	ptr_token->prev = NULL;
	if (cmd->first_token != NULL)
		cmd->first_token->prev = ptr_token;
	if (cmd->first_token == NULL)
		cmd->last_token = ptr_token;
	cmd->first_token = ptr_token;
	cmd->size++;
	ft_rotate_token(cmd);
}