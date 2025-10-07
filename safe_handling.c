/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:05:24 by mely-pan          #+#    #+#             */
/*   Updated: 2025/09/25 17:15:45 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	handle_mtx_error(int status, t_opc opcode)
{
	if (!status)
		return (0);
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		error_msg("The value specified by the mutex is invalid.");
	else if (EINVAL == status && INIT == opcode)
		error_msg("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		error_msg("A deadlock would occur if the thread blocked waiting \
			for mutex.");
	else if (EPERM == status)
		error_msg("The current thread does not hold a lock on a mutex.");
	else if (ENOMEM == status)
		error_msg("The proccess can't allocate enough memory to create \
			another mutex.");
	else if (EBUSY == status)
		error_msg("Mutex is Locked");
	return (1);
}

int	safe_mutex_handle(t_mtx *mtx, t_opc opcode)
{
	int	status;

	status = 0;
	if (INIT == opcode)
		status = pthread_mutex_init(mtx, NULL);
	else if (LOCK == opcode)
		status = pthread_mutex_lock(mtx);
	else if (UNLOCK == opcode)
		status = pthread_mutex_unlock(mtx);
	else if (DESTROY == opcode)
		status = pthread_mutex_destroy(mtx);
	return (handle_mtx_error(status, opcode));
}

void	print_status(t_philo *philo, const char *msg)
{
	t_data	*data;

	data = philo->data;
	safe_mutex_handle(&data->print_mutex, LOCK);
	if (!philo->data->someone_died)
		printf("%ld %d %s\n", get_time() - data->start_time, philo->id, msg);
	safe_mutex_handle(&data->print_mutex, UNLOCK);
}

bool	get_philos_state(t_data *data)
{
	bool	value;

	safe_mutex_handle(&data->print_mutex, LOCK);
	value = data->someone_died;
	safe_mutex_handle(&data->print_mutex, UNLOCK);
	return (value);
}

void	show_meals_taken(t_data *data)
{
	int	i;

	printf("\n=== DEBUG: Meals taken ===\n");
	i = 0;
	while (i < data->n_philos)
	{
		printf("Philo %d -> meals_taken: %d\n",
			data->philos[i].id, data->philos[i].meals_taken);
		i++;
	}
	printf("==========================\n\n");
}
