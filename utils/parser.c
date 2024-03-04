/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:20:49 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/04 14:29:49 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser(t_command_table *ptr_cmd_tab, char *line)
{
	char			**array_of_tokens;

	array_of_tokens = splitter(line);
	// printf("INITIAL FILLING OF CMD TABLE: \n");
	init_and_fill_cmd_tab(ptr_cmd_tab, array_of_tokens);
	free(array_of_tokens);
	// print_cmd_tab(ptr_cmd_tab);
	// printf("TYPES ASSIGNED IN CMD TABLE: \n");
	assign_types_to_tokens(ptr_cmd_tab);
	// print_cmd_tab(ptr_cmd_tab);
	// printf("CMD TABLE EXPANDED: \n");
	expand_cmd_tab(ptr_cmd_tab);
	// print_cmd_tab(ptr_cmd_tab);
	// printf("CMD TABLE without quotes: \n"); //just for info, delete before submitting
	remove_quotes_from_cmd_tab(ptr_cmd_tab);
	// print_cmd_tab(ptr_cmd_tab); //just for info, delete before submitting
}