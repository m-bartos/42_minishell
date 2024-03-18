/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:20:49 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/18 11:25:38 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_if_last_token_is_pipe(t_cmd *cmd)
{
	char	*line_heredoc;
	char	**arr_of_tokens;
	t_cmd	cmd_add;

	ft_init_cmd_struct(&cmd_add);
	while (is_pipe_type(cmd->last_token))
	{
		line_heredoc = readline("> ");
		arr_of_tokens = splitter(line_heredoc);
		free(line_heredoc);
		parse_from_arr_of_tokens_to_one_cmd(&cmd_add, arr_of_tokens);
		ft_cmdjoin(cmd, &cmd_add);
	}
}

void	parse_from_arr_of_tokens_to_one_cmd(t_cmd *cmd, char **arr_of_tokens)
{
	fill_cmd_tab(cmd, arr_of_tokens);
	free(arr_of_tokens);
	arr_of_tokens = NULL;
	assign_types_to_tokens(cmd);
	expand_cmd(cmd);
	remove_quotes_in_cmd_tokens(cmd);
	check_redirection_errors(cmd);
	expand_heredocs(cmd);
}

void	parser(t_cmd_tab *cmd_tab, t_cmd *cmd, char *line)
{
	char	**arr_of_tokens;

	arr_of_tokens = splitter(line);
	free(line);
	parse_from_arr_of_tokens_to_one_cmd(cmd, arr_of_tokens);
	handle_if_last_token_is_pipe(cmd);
	make_cmd_tab_from_cmd(cmd_tab, cmd);
	ft_delete_cmd(cmd);
	make_cmd_paths(cmd_tab);
	make_execve_cmds(cmd_tab);
}
