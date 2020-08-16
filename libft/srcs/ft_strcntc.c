/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcntc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 15:31:33 by mlacombe          #+#    #+#             */
/*   Updated: 2019/02/26 19:08:44 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcntc(char *str, char c)
{
	int	n;

	n = 0;
	while (str[n])
	{
		if (str[n] == c)
			n++;
	}
	return (n);
}