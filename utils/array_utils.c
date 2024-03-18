/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:17:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/18 10:48:10 by mbartos          ###   ########.fr       */
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
		str = ft_strjoin_e(str, arr_of_strs[i]);
		free(temp_str);
		i++;
	}
	return (str);
}

char	**ft_init_array(int size)
{
	char	**array;

	array = (char **) malloc(sizeof(char *) * (size + 1));
	if (array == NULL)
	{
		perror("Minishell: ");
		exit(EXIT_FAILURE);
	}
	array[size] = NULL;
	return (array);
}

void	ft_free_array(char **arr_of_str)
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

void	ft_print_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_putstr_fd(arr[i], 1);
		write(1, "\n", 1);
		i++;
	}
}
