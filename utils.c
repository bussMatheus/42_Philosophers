/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:05:29 by mely-pan          #+#    #+#             */
/*   Updated: 2025/09/25 17:16:22 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	get_digit_size(char *num)
{
	int	i;
	int	len;

	i = 0;
	len = 1;
	if (num[i] == '+' || num[i] == '-')
		i++;
	while (num[i] == '0')
		i++;
	while (num[i] >= '0' && num[i] <= '9')
	{
		i++;
		len++;
	}
	return (len);
}

int	ft_is_invalid_n(char *number)
{
	int	i;
	int	digit;

	i = 0;
	digit = get_digit_size(number);
	if (digit > 12)
		return (1);
	if (number[i] == '+' || number[i] == '-')
		i++;
	if (!number[i])
		return (1);
	while (number[i])
	{
		if (number[i] < '0' || number[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	long	result;
	int		sign;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -sign;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == 1)
			result = result * 10 + (str[i] - '0');
		else
			result = result * 10 - (str[i] - '0');
		i++;
	}
	return (result);
}

long	get_time(void)
{
	struct timeval	time;
	long			ms;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

void	ft_usleep(long ms, t_data *data)
{
	long	start;

	start = get_time();
	while (!get_philos_state(data) && (get_time() - start) < ms)
		usleep(10);
}
