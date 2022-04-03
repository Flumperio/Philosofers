#! /bin/bash
make re
echo "Philo 5 100 10 20 50"
./philo 5 100 20 20 50 | grep "Philo{1} is eating."
./philo 5 100 20 20 50 | grep "Philo{2} is eating."
./philo 5 100 20 20 50 | grep "Philo{3} is eating."
./philo 5 100 20 20 50 | grep "Philo{4} is eating."
./philo 5 100 20 20 50 | grep "Philo{5} is eating."
