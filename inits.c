#include "./philo.h"

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_mtx) * data->n_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->n_philos)
	{
		if (safe_mutex_handle(&data->forks[i], INIT))
		{
			while (--i >= 0)
				safe_mutex_handle(&data->forks[i], DESTROY);
			free(data->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		return (error_msg("Malloc Failed."), 1);
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meals_taken = 0;
		data->philos[i].last_meal_u = data->start_time;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->n_philos];
		if (safe_mutex_handle(data->philos[i].meal_mtx, INIT))
			return (1);
		i++;
	}
	return (0);
}

static int	program_info(int ac, char **av, t_data *data)
{
	data->n_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		data->num_meals = ft_atol(av[5]);
	else
		data->num_meals = -1;
	data->someone_died = false;
	if (data->time_to_die < 60 || data->time_to_sleep < 60 || data->time_to_eat < 60)
		return (error_msg("Timestamp too short, try 60ms or above"), 1);
	data->start_time = get_time();
	if (data->start_time == -1)
		return (error_msg("Error getting the actual time"), 1);
	return (0);
}

int	init_data(int ac, char **av, t_data *data)
{
	if (program_info(ac, av, data))
		return (1);
	if (safe_mutex_handle(&data->print_mutex, INIT))
		return (1);
	if (init_forks(data))
	{
		safe_mutex_handle(&data->print_mutex, DESTROY);
		return (error_msg("Error initializing forks"), 1);
	}
	if (init_philos(data))
		return (destroy_data(data), 1);
	return (0);
}
