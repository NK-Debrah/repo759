#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 1
#SBATCH -J task1
#SBATCH -o task1-%j.out
#SBATCH -e task1-%j.err

./task1 1024
