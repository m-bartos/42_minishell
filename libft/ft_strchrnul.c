/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrnul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:14:18 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/14 12:14:55 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchrnul(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *) s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char) c)
			return (&str[i]);
		i++;
	}
	return (&str[i]);
}