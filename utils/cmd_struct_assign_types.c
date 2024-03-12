/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_assign_types.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:37:34 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/12 11:44:08 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_operator_types(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token != NULL)
	{
		if (ft_strncmp(token->text, "|", 2) == 0)
			token->type = PIPE;
		else if (ft_strncmp(token->text, "<<", 3) == 0)
			token->type = HERE_DOC;
		else if (ft_strncmp(token->text, "<", 2) == 0)
			token->type = R_IN;
		else if (ft_strncmp(token->text, ">>", 3) == 0)
			token->type = R_OUT_APP;
		else if (ft_strncmp(token->text, ">", 2) == 0)
			token->type = R_OUT;
		token = token->next;
	}
}

int	assign_file_type(int prev_token_type)
{
	if (prev_token_type == R_IN)
		return (R_INFILE);
	else if (prev_token_type == R_OUT)
		return (R_OUTFILE);
	else if (prev_token_type == R_OUT_APP)
		return (R_OUTFILE_APP);
	else if (prev_token_type == HERE_DOC)
		return (HERE_DOC_EOF);
	return (99);
}

int	assign_cmd_type(char *text)
{
	if (ft_strncmp(text, "echo", 5) == 0)
		return (CMD_BUILT);
	else if (ft_strncmp(text, "cd", 3) == 0)
		return (CMD_BUILT);
	else if (ft_strncmp(text, "pwd", 4) == 0)
		return (CMD_BUILT);
	else if (ft_strncmp(text, "export", 7) == 0)
		return (CMD_BUILT);
	else if (ft_strncmp(text, "unset", 6) == 0)
		return (CMD_BUILT);
	else if (ft_strncmp(text, "env", 4) == 0)
		return (CMD_BUILT);
	else
		return (CMD);
}

void	assign_cmds_and_args(t_cmd *cmd)
{
	t_token	*token;
	int		search_cmd;
	int		search_r_file;

	search_cmd = 1;
	search_r_file = 0;
	token = cmd->first_token;
	while (token != NULL)
	{
		if (search_cmd == 1 && search_r_file == 0 && !is_operator_type(token))
		{
			token->type = assign_cmd_type(token->text);
			search_cmd = 0;
		}
		else if (is_redirection_type(token))
			search_r_file = 1;
		else if (search_r_file == 1 && !is_operator_type(token))
		{
			token->type = assign_file_type(token->prev->type);
			search_r_file = 0;
		}
		else if (search_cmd == 0 && !is_operator_type(token))
			token->type = ARG;
		else if (is_pipe_type(token))
			search_cmd = 1;
		token = token->next;
	}
}

void	assign_types_to_tokens(t_cmd *cmd)
{
	assign_operator_types(cmd);
	assign_cmds_and_args(cmd);
}
