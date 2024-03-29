/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:20:49 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/19 11:02:35 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Handles the case when the last token in the command is a pipe.
 *
 * Reads input from the user until a non-pipe token is encountered,
 * splits the input into tokens, and adds them to a new command structure.
 * Joins the new command structure with the original command structure.
 *
 * @param cmd The command structure to handle.
 */
void	handle_if_last_token_is_pipe(t_cmd *cmd, t_mini_data *minidata)
{
	char	*line_heredoc;
	char	**tokens_arr;
	t_cmd	cmd_add;

	ft_init_cmd_struct(&cmd_add);
	while (is_pipe_type(cmd->last_token))
	{
		line_heredoc = readline("> ");
		tokens_arr = splitter(line_heredoc);
		free(line_heredoc);
		parse_to_one_cmd(&cmd_add, tokens_arr, minidata);
		ft_cmdjoin(cmd, &cmd_add);
	}
}

/**
 * @brief Parses an array of tokens into a single command structure.
 * 
 * @param cmd The command structure to fill with parsed data.
 * @param tokens_arr The array of tokens to parse.
 */
void	parse_to_one_cmd(t_cmd *cmd, char **tokens_arr, t_mini_data *minidata)
{
	fill_cmd_tab(cmd, tokens_arr);
	free(tokens_arr);
	tokens_arr = NULL;
	assign_types_to_tokens(cmd);
	expand_cmd(cmd, minidata);
	remove_quotes_in_cmd_tokens(cmd);
	check_redirection_errors(cmd);
	expand_heredocs(cmd, minidata);
}

/**
 * @brief Parses the given line and populates the command table.
 *
 * @param cmd_tab The command table to populate.
 * @param line The line to parse.
 */
void	parser(t_cmd_tab *cmd_tab, char *line, t_mini_data *minidata)
{
	char	**tokens_arr;
	t_cmd	cmd;

	ft_init_cmd_struct(&cmd);
	tokens_arr = splitter(line);
	free(line);
	parse_to_one_cmd(&cmd, tokens_arr, minidata);
	handle_if_last_token_is_pipe(&cmd, minidata);
	make_cmd_tab_from_cmd(cmd_tab, &cmd);
	ft_delete_cmd(&cmd);
	make_cmd_paths(cmd_tab, minidata);
	make_execve_cmds(cmd_tab);
}
