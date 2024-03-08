/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd_table_ops.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:57:52 by orezek            #+#    #+#             */
/*   Updated: 2024/03/09 00:15:29 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_cmd_table(t_cmd_tab *cmd_tab)
{
	cmd_tab->first_cmd = NULL;
	cmd_tab->last_cmd = NULL;
	cmd_tab->size = 0;
}

void	ft_init_cmd(t_command *cmd)
{
	cmd->execve_cmd = NULL;
	cmd->next_cmd = NULL;
	cmd->prev_cmd = NULL;
	cmd->first_token = NULL;
	cmd->last_token = NULL;
	cmd->size = 0;
}

void	ft_init_token(t_token *token)
{
	token->text = NULL;
	token->type = -1;
	token->next = NULL;
	token->prev = NULL;
}
// adds cmd to the top = push operation - FIFO
void	ft_push_cmd_to_tab(t_cmd_tab *cmd_table, t_command *cmd)
{

	if (cmd_table == NULL && cmd == NULL)
		return ;
	if (cmd_table->first_cmd == NULL)
	{
		cmd_table->first_cmd = cmd;
		cmd_table->last_cmd = cmd;
		cmd->next_cmd = NULL;
		cmd->prev_cmd = NULL;
	}
	else
	{
		cmd->prev_cmd = NULL;
		cmd->next_cmd = cmd_table->first_cmd;
		cmd_table->first_cmd->prev_cmd = cmd;
		cmd_table->first_cmd = cmd;
	}
	cmd_table->size++;
}

// adds cmd to the end = enqueue operation - FILO
void	ft_append_cmd_to_tab(t_cmd_tab *cmd_table, t_command *cmd)
{
	if (cmd_table == NULL && cmd == NULL)
		return ;
	if (cmd_table->first_cmd == NULL)
	{
		cmd_table->first_cmd = cmd;
		cmd_table->last_cmd = cmd;
		cmd->next_cmd = NULL;
		cmd->prev_cmd = NULL;
	}
	else
	{
		cmd->prev_cmd = cmd_table->last_cmd;
		cmd->next_cmd = NULL;
		cmd_table->last_cmd->next_cmd = cmd;
		cmd_table->last_cmd = cmd;
	}
	cmd_table->size++;
}
// adds token to the end = enqueue operation - FILO
void	ft_append_token_to_cmd(t_command *cmd, t_token *token)
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

t_token	*ft_create_token(char *text, t_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return NULL;
	ft_init_token(token);
	token->text = text;
	token->type = type;
	return (token);
}


// version II append token to cmd
// adds token to the end = enqueue operation - FILO
void	ft_append_token_to_cmd_v2(t_command *cmd, char *text, t_type type)
{
	t_token *token;

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
