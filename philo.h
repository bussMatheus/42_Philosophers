#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647

typedef struct s_data
{
	int				n_philos;
	int				num_meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			start_time;
	bool			someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_taken;
	int				last_meal_u;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;


/*					PARSE && Inits					*/
int		check_valid_input(int ac, char **av);
int		init_data(int ac, char **av, t_data *data);

/*					ERROR AND FREES					*/
void	error_msg(char *str);
void	destroy_data(t_data *data);

/*						UTILS						*/
long	get_time(void);
long	ft_atol(const char *str);
int		ft_is_invalid_n(char *number);


#endif