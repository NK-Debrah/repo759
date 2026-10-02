#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 1
#SBATCH -J task2
#SBATCH -o task2-%j.out
#SBATCH -e task2-%j.err

./task2 100 3
