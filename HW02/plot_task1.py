import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

ns = []
times = []

with open("task1_results.txt") as f:
    for line in f:
        n_str, t_str = line.split()
        ns.append(int(n_str))
        times.append(float(t_str))

plt.figure()
plt.plot(ns, times, marker="o")
plt.xscale("log", base=2)
plt.xlabel("n (array size)")
plt.ylabel("Time (ms)")
plt.title("Task 1: Scan Scaling Analysis")
plt.grid(True, which="both", linestyle="--", alpha=0.6)
plt.tight_layout()
plt.savefig("task1.pdf")
