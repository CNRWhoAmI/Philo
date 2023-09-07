/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoptas <ctoptas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:39:34 by ctoptas           #+#    #+#             */
/*   Updated: 2023/09/06 13:01:10 by ctoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_valid(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (ft_err("Error: Number of arguments is not valid\n"));
	if (unsigned_atoi(av[1]) <= 0)
		return (ft_err("Error: Number of philosophers is not valid\n"));
	while (av[i])
	{
		if (!is_digit(av[i]))
			return (ft_err("Error: Arguments are must be digit\n"));
		i++;
	}
	return (1);
}

int	value_check(t_table *table)
{
	if (table->number_of_philo == 1)
		return (ft_err("Philo 1 died\n"));
	else if (table->time_to_die < 60 || table->time_to_sleep < 60
		|| table->time_to_eat < 60)
		return (ft_err("Time values should not be less than 60 ms\n"));
	return (1);
}

t_table	*parse(int ac, char **av)
{
	t_table	*table;

	if (!check_valid(ac, av))
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->number_of_philo = unsigned_atoi(av[1]);
	table->time_to_die = unsigned_atoi(av[2]);
	table->time_to_eat = unsigned_atoi(av[3]);
	table->time_to_sleep = unsigned_atoi(av[4]);
	table->number_of_must_eat = -1;
	if (ac == 6)
		table->number_of_must_eat = unsigned_atoi(av[5]);
	if (!value_check(table))
	{
		free(table);
		return (NULL);
	}
	table->philos = malloc(sizeof(t_philo) * table->number_of_philo);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philo);
	table->time = current_time();
	table->stop = 0;
	return (table);
}
