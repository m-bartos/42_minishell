/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:20:49 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/11 10:12:43 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser(t_cmd *ptr_cmd, char **arr_of_tokens)
{
	// printf("INITIAL FILLING OF CMD TABLE: \n");
	fill_cmd_tab(ptr_cmd, arr_of_tokens);
	free(arr_of_tokens);
	// print_cmd(ptr_cmd);
	// printf("TYPES ASSIGNED IN CMD TABLE: \n");
	assign_types_to_tokens(ptr_cmd);
	// print_cmd(ptr_cmd);
	// printf("CMD TABLE EXPANDED: \n");
	expand_cmd_tab(ptr_cmd);
	// print_cmd(ptr_cmd);
	// printf("CMD TABLE without quotes: \n"); //just for info, delete before submitting
	remove_quotes_from_cmd_tab(ptr_cmd);
	check_redirection_errors(ptr_cmd);
	expand_heredocs(ptr_cmd);
	// print_cmd(ptr_cmd); //just for info, delete before submitting
}