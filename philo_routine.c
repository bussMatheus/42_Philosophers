/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:05:15 by mely-pan          #+#    #+#             */
/*   Updated: 2025/10/07 18:57:34 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	set_forks(t_philo *philo, t_mtx **first, t_mtx **second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	else
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
}

static void	think(t_philo *philo)
{
	if (get_philos_state(philo->data))
		return ;
	print_status(philo, "is thinking");
}

static int	eat(t_philo *philo)
{
	t_mtx	*first;
	t_mtx	*second;

	set_forks(philo, &first, &second);
	if (get_philos_state(philo->data))
		return (1);
	safe_mutex_handle(first, LOCK);
	print_status(philo, "has taken a fork");
	if (philo->data->n_philos == 1)
	{
		ft_usleep(philo->data->time_to_die + 1, philo->data);
		safe_mutex_handle(first, UNLOCK);
		return (1);
	}
	safe_mutex_handle(second, LOCK);
	print_status(philo, "has taken a fork");
	safe_mutex_handle(&philo->meal_mtx, LOCK);
	philo->last_meal_u = get_time();
	philo->meals_taken++;
	safe_mutex_handle(&philo->meal_mtx, UNLOCK);
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo->data);
	safe_mutex_handle(first, UNLOCK);
	safe_mutex_handle(second, UNLOCK);
	return (0);
}

static void	sleeping(t_philo *philo)
{
	if (get_philos_state(philo->data))
		return ;
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(500);
	while (!get_philos_state(data))
	{
		think(philo);
		if (eat(philo))
			return (NULL);
		sleeping(philo);
		if (philo->data->n_philos % 2 != 0)
			ft_usleep(1, data);
	}
	return (NULL);
}
