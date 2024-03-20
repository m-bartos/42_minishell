/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:46:28 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/20 15:18:12 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Initializes a command structure.
 *
 * Sets all fields of a command structure to their default values, indicating
 * an empty command.
 *
 * @param cmd Pointer to the command to initialize.
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

void	ft_init_token_struct(t_token *token)
{
	token->text = NULL;
	token->type = -1;
	token->next = NULL;
	token->prev = NULL;
}

t_token	*ft_create_new_token(char *text, t_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("minishell: ");
		exit (EXIT_FAILURE);
	}
	ft_init_token_struct(token);
	token->text = text;
	token->type = type;
	return (token);
}

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
