import matplotlib.pyplot as plt
import csv

cycles = []
avgPayoffs = []

with open("avgPayoff.csv") as f:
    reader = csv.DictReader(f)
    for row in reader:
        cycles.append(int(row["cycle"]))
        avgPayoffs.append(float(row["avgPayoff"]))

plt.plot(cycles, avgPayoffs, marker='o')
plt.xlabel("Cycle")
plt.ylabel("Average Population Payoff")
plt.title("Evolution of Average Payoff Over Time")
plt.grid(True)
plt.ylim(0, 4)
plt.show()
