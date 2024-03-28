/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_execve_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:26:48 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/28 11:35:50 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Count the number of command and argument tokens in a command struct.
 *
 * @param cmd Pointer to the command structure.
 * @return The number of command and argument tokens, or -1 if there are errors.
 */
int	count_cmd_length(t_cmd *cmd)
{
	t_token	*token;
	t_type	type;
	int		length;

	token = cmd->first_token;
	length = 0;
	while (token != NULL)
	{
		type = token->type;
		if (type == CMD || type == CMD_BUILT || type == CMD_ERR || (type == ARG && token->text != NULL))
			length++;
		token = token->next;
	}
	return (length);
}

/**
 * @brief Create the command string array for a single command structure.
 *
 * @param cmd Pointer to the command structure.
 */
void	make_one_execve_cmd(t_cmd *cmd)
{
	t_token	*token;
	t_type	type;
	char	**execve_cmd;
	int		length;
	int		i;

	length = count_cmd_length(cmd);
	if (length == -1)
		return ;
	execve_cmd = ft_init_array(length);
	if (execve_cmd == NULL)
		return ;
	token = cmd->first_token;
	i = 0;
	while (i < length)
	{
		type = token->type;
		if (type == CMD || type == CMD_BUILT || type == CMD_ERR || (type == ARG && token->text != NULL))
			execve_cmd[i++] = token->text;
		token = token->next;
	}
	cmd->execve_cmd = execve_cmd;
}

/**
 * Create the command string arrays for all commands in the command table.
 * 
 * @param cmd_tab Pointer to the command table structure.
 */
void	make_execve_cmds(t_cmd_tab *cmd_tab)
{
	t_cmd	*cmd;

	cmd = cmd_tab->first_cmd;
	while (cmd != NULL)
	{
		make_one_execve_cmd(cmd);
		cmd = cmd->next;
	}
}
