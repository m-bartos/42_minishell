/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:17:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/14 15:18:39 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_len_of_arr(char **arr)
{
	int	size;

	size = 0;
	if (arr == NULL)
		return (0);
	while (arr[size])
		size++;
	return (size);
}

char	*ft_arr_to_str(char **arr_of_strs)
{
	char	*str;
	char	*temp_str;
	int		i;

	i = 0;
	str = NULL;
	while(arr_of_strs[i])
	{
		temp_str = str;
		str = ft_strjoin(str, arr_of_strs[i]);
		free(temp_str);
		i++;
	}
	return (str);
}

void	free_array(char **arr_of_str)
{
	int	index;

	index = 0;
	while (arr_of_str[index] != NULL)
	{
		free(arr_of_str[index]);
		index++;
	}
	free(arr_of_str);
}
