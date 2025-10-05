/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:04:49 by mely-pan          #+#    #+#             */
/*   Updated: 2025/09/25 17:04:50 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_valid_input(argc, argv))
		return (1);
	if (init_data(argc, argv, &data))
		return (1);
	if (run(&data))
		return (destroy_data(&data), 1);
	if (DEBUG)
		show_meals_taken(&data);
	destroy_data(&data);
	return (0);
}
