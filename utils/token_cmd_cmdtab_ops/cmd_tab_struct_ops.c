/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_struct_ops.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:42:04 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/21 11:33:42 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Initializes a command table.
 *
 * Sets up an empty command table by setting first and last command pointers
 * to NULL and size to 0.
 *
 * @param cmd_tab Pointer to the command table to initialize.
 */
void	ft_init_cmd_tab(t_cmd_tab *cmd_tab)
{
	cmd_tab->first_cmd = NULL;
	cmd_tab->last_cmd = NULL;
	cmd_tab->size = 0;
}

t_cmd	*ft_create_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("minishell: ");
		exit (EXIT_FAILURE);
	}
	ft_init_cmd_struct(cmd);
	return (cmd);
}

void	ft_append_new_cmd_to_tab(t_cmd_tab *cmd_tab)
{
	t_cmd	*cmd;

	cmd = ft_create_cmd();
	if (cmd_tab == NULL && cmd == NULL)
		return ;
	if (cmd_tab->first_cmd == NULL)
	{
		cmd_tab->first_cmd = cmd;
		cmd_tab->last_cmd = cmd;
		cmd->next = NULL;
		cmd->prev = NULL;
	}
	else
	{
		cmd->prev = cmd_tab->last_cmd;
		cmd->next = NULL;
		cmd_tab->last_cmd->next = cmd;
		cmd_tab->last_cmd = cmd;
	}
	cmd_tab->size++;
}

void	ft_delete_cmds_in_cmd_tab(t_cmd_tab *cmd_tab)
{
	t_cmd	*current_cmd;
	t_cmd	*temp_cmd;
	t_token	*current_token;
	t_token	*temp_token;

	current_cmd = cmd_tab->first_cmd;
	while (current_cmd != NULL)
	{
		temp_cmd = current_cmd->next;
		current_token = current_cmd->first_token;
		while (current_token != NULL)
		{
			temp_token = current_token->next;
			free(current_token->text);
			free(current_token);
			current_token = temp_token;
		}
		free(current_cmd->execve_cmd);
		free(current_cmd);
		current_cmd = temp_cmd;
		temp_cmd = NULL;
	}
	cmd_tab->first_cmd = NULL;
	cmd_tab->last_cmd = NULL;
	cmd_tab->size = 0;
}
