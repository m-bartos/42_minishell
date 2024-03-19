/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_e.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:25:37 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/19 14:14:23 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_substr_e(const char *s1, unsigned int start, size_t len)
{
	char	*new_str;

	new_str = ft_substr(s1, start, len);
	if (new_str == NULL)
	{
		perror("Minishell: ");
		exit(EXIT_FAILURE);
	}
	return (new_str);
}
