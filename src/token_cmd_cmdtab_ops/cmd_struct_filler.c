/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_filler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:04:25 by mbartos           #+#    #+#             */
/*   Updated: 2024/04/21 20:23:49 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Fills a command structure with tokens from an array of strings.
 *
 * This function populates the specified command structure with tokens obtained
 * from the provided array of strings. It iterates through the array of tokens,
 * adding each token to the command structure.
 *
 * @param cmd The command structure to fill with tokens.
 * @param tokens_arr The array of strings (tokens) to add to the command.
 */
void	fill_cmd_tab(t_cmd *cmd, char **tokens_arr)
{
	size_t	i;

	i = 0;
	while (tokens_arr[i] != NULL)
	{
		ft_append_new_token_to_cmd(cmd, tokens_arr[i], NOT_ASSIGNED);
		i++;
	}
}
