/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_e.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:24:06 by mbartos           #+#    #+#             */
/*   Updated: 2024/04/21 20:23:07 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_e(const char *s1, const char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	if (new_str == NULL)
	{
		perror("Minishell: ");
		exit(EXIT_FAILURE);
	}
	return (new_str);
}
