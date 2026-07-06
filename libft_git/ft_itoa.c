/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thcotza <thcotza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:14:35 by thcotza           #+#    #+#             */
/*   Updated: 2025/10/20 18:23:59 by thcotza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbrcount(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;
	int		verif;

	verif = 0;
	count = ft_putnbrcount(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		return (0);
	if (n < 0)
	{
		++verif;
		*str = '-';
		n *= -1;
	}
	str[count--] = '\0';
	while (count >= verif)
	{
		str[count--] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
