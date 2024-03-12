/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:20:49 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/12 12:59:02 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser(t_cmd *cmd, char **arr_of_tokens)
{
	// printf("INITIAL FILLING OF CMD TABLE: \n");
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
	// print_cmd(ptr_cmd); //just for info, delete before submitting
}