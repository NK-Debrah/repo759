#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 1
#SBATCH -t 00:30:00
#SBATCH --mem=16G
#SBATCH -J task1_scaling
#SBATCH -o task1_scaling-%j.out
#SBATCH -e task1_scaling-%j.err

rm -f task1_results.txt

for i in {10..30}
do
    n=$((2**i))
    t=$(./task1 $n | head -n 1)
    echo "$n $t" >> task1_results.txt
done
