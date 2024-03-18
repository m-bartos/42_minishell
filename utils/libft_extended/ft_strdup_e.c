/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_e.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:25:05 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/18 10:33:14 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdup_e(const char *s1)
{
	char	*new_str;

	new_str = ft_strdup(s1);
	if(new_str == NULL)
	{
		perror("Minishell: ");
		exit(EXIT_FAILURE);
	}
	return (new_str);
}
