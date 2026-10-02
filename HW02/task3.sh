#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 1
#SBATCH -J task3
#SBATCH -o task3-%j.out
#SBATCH -e task3-%j.err

./task3
