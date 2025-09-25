#include "./philo.h"

int	run(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (data->n_philos > i)
	{
		data->philos[i].last_meal_u = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]) != 0)
			return (error_msg("Thread Creation Failed."), 1);
		if (pthread_detach(data->philos[i].thread) != 0)
			return (error_msg("Thread Detach Failed."), 1);
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitor_routine, data) != 0)
		return (error_msg("Monitor Thread creation Failed."), 1);
	if (pthread_join(monitor, NULL) != 0)
		return (error_msg("Monitor Thread join Failed."), 1);
	return (0);
}

static bool	check_death(t_data *data, t_philo *philo)
{
	if (get_time() - philo->last_meal_u > data->time_to_die)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d died\n", get_time() - data->start_time, philo->id);
		data->someone_died = true;
		pthread_mutex_unlock(&data->print_mutex);
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
		if (data->philos[i].meals_taken < data->num_meals)
			return (false);
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
		data->someone_died = true;
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!data->someone_died)
	{
		if (check_philos(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}
