/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   em_and_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:05:01 by mely-pan          #+#    #+#             */
/*   Updated: 2025/09/25 17:05:02 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

//File to secure error managment, sendind necessary messages
// and freeing when necessary

void	error_msg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
}

void	destroy_data(t_data *data)
{
	int	i;

	if (!data || !data->forks)
		return ;
	i = 0;
	while (i < data->n_philos)
	{
		if (data->philos)
			safe_mutex_handle(&data->philos[i].meal_mtx, DESTROY);
		safe_mutex_handle(&data->forks[i++], DESTROY);
	}
	safe_mutex_handle(&data->print_mutex, DESTROY);
	free(data->forks);
	data->forks = NULL;
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}
