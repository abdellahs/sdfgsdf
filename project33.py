import numpy as np
import matplotlib.pyplot as plt

# Function to simulate random walkers in 2D
def simulate_walkers_2D(num_walkers, num_steps):
    walkers = np.zeros((num_walkers, 2, num_steps + 1))

    for step in range(1, num_steps + 1):
        steps_x = np.random.choice([-1, 0, 1], size=num_walkers)
        steps_y = np.random.choice([-1, 0, 1], size=num_walkers)

        walkers[:, 0, step] = walkers[:, 0, step - 1] + steps_x
        walkers[:, 1, step] = walkers[:, 1, step - 1] + steps_y

    return walkers

# Simulation parameters
num_walkers = 1000
num_steps = 500

# Run the simulation
all_walkers_2D = simulate_walkers_2D(num_walkers, num_steps)

# Plot the positions of all walkers at time n = 500
plt.figure(figsize=(8, 8))
plt.scatter(all_walkers_2D[:, 0, -1], all_walkers_2D[:, 1, -1], marker='o', alpha=0.5)
plt.title('Positions of Walkers at Time Step 500')
plt.xlabel('X Position')
plt.ylabel('Y Position')
plt.grid(True)
plt.show()

# Calculate RMS for each time step analytically
rms_analytical = np.sqrt(np.arange(0, num_steps + 1))

# Calculate RMS for each time step from the simulation
rms_simulated = np.std(all_walkers_2D, axis=0)

# Slice the results from the random walks for different walker populations
ten_walkers = all_walkers_2D[:10]
hundred_walkers = all_walkers_2D[:100]
thousand_walkers = all_walkers_2D

# Calculate mean displacement and RMS for each time step from random walks
mean_displacement_ten = np.mean(ten_walkers, axis=0)
mean_displacement_hundred = np.mean(hundred_walkers, axis=0)
mean_displacement_thousand = np.mean(thousand_walkers, axis=0)

rms_ten = np.std(ten_walkers, axis=0)
rms_hundred = np.std(hundred_walkers, axis=0)
rms_thousand = np.std(thousand_walkers, axis=0)

# Plotting RMS
plt.figure(figsize=(12, 6))
plt.plot(range(num_steps + 1), rms_analytical, label='Analytical', linestyle='--', color='black')
plt.plot(range(num_steps + 1), rms_ten, label='M = 10', marker='o', alpha=0.7)
plt.plot(range(num_steps + 1), rms_hundred, label='M = 100', marker='o', alpha=0.7)
plt.plot(range(num_steps + 1), rms_thousand, label='M = 1000', marker='o', alpha=0.7)
plt.xlabel('Number of Steps')
plt.ylabel('RMS')
plt.title('RMS vs. Number of Steps')
plt.legend()
plt.grid(True)
plt.show()
