/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:05:07 by mely-pan          #+#    #+#             */
/*   Updated: 2025/10/06 20:54:35 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	run(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (data->n_philos > i)
	{
		data->philos[i].last_meal_u = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				&data->philos[i]) != 0)
			return (error_msg("Thread Creation Failed."), 1);
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitor_routine, data) != 0)
		return (error_msg("Monitor Thread creation Failed."), 1);
	if (pthread_join(monitor, NULL) != 0)
		return (error_msg("Monitor Thread join Failed."), 1);
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_join(data->philos[i++].thread, NULL) != 0)
			return (error_msg("Philo Thread join Failed."), 1);
	}
	return (0);
}

static bool	check_death(t_data *data, t_philo *philo)
{
	long	time_after_meal;

	safe_mutex_handle(&philo->meal_mtx, LOCK);
	time_after_meal = get_time() - philo->last_meal_u;
	safe_mutex_handle(&philo->meal_mtx, UNLOCK);
	if (time_after_meal >= data->time_to_die)
	{
		safe_mutex_handle(&data->all_alive_mtx, LOCK);
		data->someone_died = true;
		safe_mutex_handle(&data->print_mutex, LOCK);
		printf("%ld %d died\n", get_time() - data->start_time, philo->id);
		safe_mutex_handle(&data->print_mutex, UNLOCK);
		safe_mutex_handle(&data->all_alive_mtx, UNLOCK);
		return (true);
	}
	return (false);
}

static bool	all_philos_done(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_meals == -1)
		return (false);
	while (i < data->n_philos)
	{
		safe_mutex_handle(&data->philos[i].meal_mtx, LOCK);
		if (data->philos[i].meals_taken < data->num_meals)
		{
			safe_mutex_handle(&data->philos[i].meal_mtx, UNLOCK);
			return (false);
		}
		safe_mutex_handle(&data->philos[i].meal_mtx, UNLOCK);
		i++;
	}
	return (true);
}

static bool	check_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (check_death(data, &data->philos[i]))
			return (true);
		i++;
	}
	if (all_philos_done(data))
	{
		safe_mutex_handle(&data->all_alive_mtx, LOCK);
		data->someone_died = true;
		safe_mutex_handle(&data->all_alive_mtx, UNLOCK);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!get_philos_state(data))
	{
		if (check_philos(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}
