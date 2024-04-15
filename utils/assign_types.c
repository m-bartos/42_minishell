/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:37:34 by mbartos           #+#    #+#             */
/*   Updated: 2024/04/15 10:57:17 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cmd_struct_assign_types.c
 * @brief Functions to assign types to tokens within a command structure.
 *
 * This file contains functions responsible for assigning types to tokens within
 * a command structure. These types include operator types such as pipes and
 * redirections, command types such as built-in commands or regular commands,
 * and argument types. These assigned types aid in parsing and interpreting user
 * input commands within the minishell application.
 */

#include "../minishell.h"

/**
 * @brief Assigns file types to tokens based on the preceding token type.
 *
 * This function determines the file type of tokens representing file
 * redirections within a command structure. The file type is determined based
 * on the type of the preceding token, such as input redirection, output
 * redirection, output redirection with append, or here-documents.
 *
 * @param prev_token_type The type of the preceding token.
 * @return The type of file redirection to assign to the token.
 */
t_type	assign_file_type(t_type prev_token_type, int *search_file)
{
	t_type	output;

	output = 99;
	if (prev_token_type == R_IN)
		output = R_INFILE;
	else if (prev_token_type == R_OUT)
		output = R_OUTFILE;
	else if (prev_token_type == R_OUT_APP)
		output = R_OUTFILE_APP;
	else if (prev_token_type == HERE_DOC)
		output = HERE_DOC_EOF;
	*search_file = 0;
	return (output);
}

/**
 * @brief Assigns command types to tokens based on token text.
 *
 * This function identifies specific command tokens within a command structure
 * and assigns corresponding types to these tokens. It recognizes built-in
 * commands such as 'echo', 'cd', 'pwd', 'export', 'unset', 'env', and regular
 * commands.
 *
 * @param text The text content of the token to determine its type.
 * @return The type of command to assign to the token.
 */
t_type	assign_cmd_type(char *text, int *search_cmd)
{
	t_type	output;

	output = 99;
	if (ft_strncmp(text, "echo", 5) == 0)
		output = CMD_BUILT;
	else if (ft_strncmp(text, "cd", 3) == 0)
		output = CMD_BUILT;
	else if (ft_strncmp(text, "pwd", 4) == 0)
		output = CMD_BUILT;
	else if (ft_strncmp(text, "export", 7) == 0)
		output = CMD_BUILT;
	else if (ft_strncmp(text, "unset", 6) == 0)
		output = CMD_BUILT;
	else if (ft_strncmp(text, "env", 4) == 0)
		output = CMD_BUILT;
	else if (ft_strncmp(text, "exit", 5) == 0)
		output = CMD_BUILT;
	else
		output = CMD;
	*search_cmd = 0;
	return (output);
}

/**
 * @brief Assigns operator types to tokens within a command structure.
 *
 * This function identifies specific operator tokens within a command structure
 * and assigns corresponding types to these tokens. It recognizes pipe symbols
 * ('|'), input redirection ('<'), output redirection ('>'), output redirection
 * with append ('>>'), and here-documents ('<<').
 *
 * @param cmd The command structure to assign operator types to its tokens.
 */
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

/**
 * @brief Assigns command and argument types to tokens within a command struct.
 *
 * This function determines the types of tokens representing commands and
 * arguments within a given command structure. It distinguishes between
 * built-in commands, regular commands, and arguments based on token context
 * and preceding tokens.
 *
 * @param cmd The command structure to assign command and argument types.
 */
void	assign_cmd_and_arg_types(t_token *token)
{
	int		search_cmd;
	int		search_file;

	search_cmd = 1;
	search_file = 0;
	while (token != NULL)
	{
		if (token->text[0] != '\0')
		{
			if (search_cmd == 1 && search_file == 0 && !is_operator_type(token))
				token->type = assign_cmd_type(token->text, &search_cmd);
			else if (is_redirection_type(token))
				search_file = 1;
			else if (search_file == 1 && !is_operator_type(token))
				token->type = assign_file_type(token->prev->type, &search_file);
			else if (search_cmd == 0 && !is_operator_type(token))
				token->type = ARG;
			else if (is_pipe_type(token))
				search_cmd = 1;
		}
		token = token->next;
	}
}

/**
 * @brief Assigns types to tokens within a command structure.
 *
 * This function orchestrates the assignment of types to tokens within a given
 * command structure by calling specific functions to handle operator types,
 * command types, and argument types.
 *
 * @param cmd The command structure, which holds tokens for type assignment.
 */
void	assign_types_to_tokens(t_cmd *cmd)
{
	assign_operator_types(cmd);
	assign_cmd_and_arg_types(cmd->first_token);
}
