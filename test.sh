#! /bin/bash
make re
echo "Philo 5 100 100 20"
./philo 5 100 100 20
./philo 5 100 100 20
./philo 5 100 100 20
./philo 5 100 100 20
./philo 5 100 100 20
./philo 5 100 100 20
./philo 5 100 100 20
./philo 5 100 100 20
./philo 5 100 100 20
./philo 5 100 100 20
./philo 5 100 10 100
./philo 5 100 10 100
./philo 5 100 10 100
./philo 5 100 10 100
./philo 5 100 10 100
./philo 5 100 10 100
./philo 5 100 10 100
./philo 5 100 10 100
./philo 5 100 10 100
./philo 5 100 10 100
./philo 5 100 10 100
./philo 5 100 10 10 10 | grep "Philo{1} is eating" | wc -l
./philo 5 100 10 10 10 | grep "Philo{2} is eating" | wc -l
./philo 5 100 10 10 10 | grep "Philo{3} is eating" | wc -l
./philo 5 100 10 10 10 | grep "Philo{4} is eating" | wc -l
./philo 5 100 10 10 10 | grep "Philo{5} is eating" | wc -l
./philo 5 100 10 10 30 | grep "Philo{1} is eating" | wc -l
./philo 5 100 10 10 30 | grep "Philo{2} is eating" | wc -l
./philo 5 100 10 10 30 | grep "Philo{3} is eating" | wc -l
./philo 5 100 10 10 30 | grep "Philo{4} is eating" | wc -l
./philo 5 100 10 10 30 | grep "Philo{5} is eating" | wc -l
