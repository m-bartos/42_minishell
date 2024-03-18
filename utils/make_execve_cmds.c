/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_execve_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:26:48 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/18 09:13:28 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	count_cmd_length(t_cmd *cmd)
{
	t_token	*token;
	int		length;

	token = cmd->first_token;
	length = 0;
	while(token != NULL)
	{
		if (token->type == CMD || token->type == ARG)
			length++;
		else if (token->type == CMD_ERR || token->type == CMD_BUILT)
			return (-1);
		token = token->next;
	}
	return (length);
}

void	make_one_execve_cmd(t_cmd *cmd)
{
	t_token	*token;
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
	while(i < length)
	{
		if (token->type == CMD || token->type == ARG)
			execve_cmd[i++] = token->text;
		token = token->next;
	}
	cmd->execve_cmd = execve_cmd;
}

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
