/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_filler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:04:25 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/15 08:22:25 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_cmd_tab(t_cmd *cmd, char **arr_of_tokens)
{
	size_t	i;

	i = 0;
	while (arr_of_tokens[i] != NULL)
	{
		ft_push_rotate_token(cmd, arr_of_tokens[i], NOT_ASSIGNED);
		i++;
	}
}
