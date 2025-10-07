/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:05:20 by mely-pan          #+#    #+#             */
/*   Updated: 2025/10/06 20:53:45 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

# define INT_MAX 2147483647
# ifndef DEBUG
#  define DEBUG 0
# endif

typedef pthread_mutex_t	t_mtx;
typedef struct s_philo	t_philo;

typedef enum e_opcode
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
	CREATE,
	DETACH,
}		t_opc;

typedef struct s_data
{
	int			n_philos;
	int			num_meals;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	long		start_time;
	bool		someone_died;
	t_mtx		*forks;
	t_mtx		print_mutex;
	t_mtx		all_alive_mtx;
	t_philo		*philos;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			meals_taken;
	long		last_meal_u;
	bool		just_ate;
	t_mtx		*left_fork;
	t_mtx		*right_fork;
	t_mtx		meal_mtx;
	t_data		*data;
	pthread_t	thread;
}	t_philo;

/*				PARSE & INITS & RUN					*/
int		check_valid_input(int ac, char **av);
int		init_philos(t_data *data);
int		init_data(int ac, char **av, t_data *data);
int		run(t_data *data);
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);

/*					ERROR AND FREES					*/
void	error_msg(char *str);
void	destroy_data(t_data *data);
int		safe_mutex_handle(t_mtx *mtx, t_opc opcode);

/*						UTILS						*/
long	get_time(void);
long	ft_atol(const char *str);
int		ft_is_invalid_n(char *number);
void	ft_usleep(long ms, t_data *data);
void	print_status(t_philo *philo, const char *msg);
bool	get_philos_state(t_data *data);
void	show_meals_taken(t_data *data);

#endif
