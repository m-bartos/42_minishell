/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:20:49 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/13 10:02:22 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_if_last_token_is_pipe(t_cmd *cmd)
{
	char	*line_heredoc;
	char	**arr_of_tokens;

	while (is_pipe_type(cmd->last_token))
	{
		line_heredoc = readline("> ");
		arr_of_tokens = splitter(line_heredoc);
		free(line_heredoc);
		parse_from_arr_of_tokens_to_one_cmd(cmd, arr_of_tokens);
	}
}

void	parse_from_arr_of_tokens_to_one_cmd(t_cmd *cmd, char **arr_of_tokens)
{
	fill_cmd_tab(cmd, arr_of_tokens);
	free(arr_of_tokens);
	// print_cmd(ptr_cmd);
	// printf("TYPES ASSIGNED IN CMD TABLE: \n");
	assign_types_to_tokens(cmd);
	// print_cmd(ptr_cmd);
	// printf("CMD TABLE EXPANDED: \n");
	expand_cmd_tab(cmd);
	// print_cmd(ptr_cmd);
	// printf("CMD TABLE without quotes: \n"); //just for info, delete before submitting
	remove_quotes_from_cmd_tab(cmd);
	check_redirection_errors(cmd);
	expand_heredocs(cmd);
	
}

void	parser(t_cmd_tab *cmd_tab, t_cmd *cmd, char **arr_of_tokens)
{
	parse_from_arr_of_tokens_to_one_cmd(cmd, arr_of_tokens);
	printf("INITIAL FILLING OF CMD TABLE: \n");
	handle_if_last_token_is_pipe(cmd);
	print_cmd(cmd);
	make_cmd_tab(cmd_tab, cmd);
	ft_delete_cmd(cmd);
	// print_cmd_tab(&cmd_tab);
	// print_cmd_tab(&cmd_tab);
	make_cmd_paths(cmd_tab);
	make_execve_cmds(cmd_tab);
	// print_cmd(ptr_cmd); //just for info, delete before submitting
}