/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:09:21 by lisimony          #+#    #+#             */
/*   Updated: 2024/10/15 15:09:25 by lisimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int		i;
	long	value;

	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"), 0);
	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (printf("Error: Invalid argument: %s\n", argv[i]), 0);
		value = ft_atol(argv[i]);
		if (value <= 0 || value > LONG_MAX)
			return (printf("Error: Invalid argument value: %s\n", argv[i]), 0);
		i++;
	}
	if (ft_atol(argv[1]) > 200)
		return (printf("Error: Invalid number of philosophers (max 200)\n"), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];

	if (!check_args(argc, argv))
		return (1);
	data_init(&data, philos);
	fork_init(forks, ft_atol(argv[1]));
	philo_init(philos, &data, forks, argv);
	thread_create(&data, forks);
	full_cleanup(NULL, &data, forks);
	return (0);
}