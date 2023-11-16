import numpy as np
import matplotlib.pyplot as plt

# 2a) Random walker in two dimensions
def random_walker_2D(N):
    x = np.zeros(N + 1)
    y = np.zeros(N + 1)

    # Simulate the random walker in 2D
    for n in range(1, N + 1):
        step_x = np.random.choice([-1, 0, 1])
        step_y = np.random.choice([-1, 0, 1])

        x[n] = x[n - 1] + step_x
        y[n] = y[n - 1] + step_y

    return x, y

# Set the number of steps for 2
N_2a = 50

# Generate random walker data in 2D for 2a)
x_2a, y_2a = random_walker_2D(N_2a)

# Plotting for 2a)
plt.plot(x_2a, y_2a, marker='o')
plt.xlabel('X')
plt.ylabel('Y')
plt.title('2a) 2D Random Walker')
plt.grid(True)
plt.show()

# 2b) Many walkers in two dimensions
def random_walkers_2D(num_walkers, N):
    walkers_x = np.zeros((num_walkers, N + 1))
    walkers_y = np.zeros((num_walkers, N + 1))

    # Simulate multiple random walkers in 2D
    for walker in range(num_walkers):
        for n in range(1, N + 1):
            step_x = np.random.choice([-1, 0, 1])
            step_y = np.random.choice([-1, 0, 1])

            walkers_x[walker, n] = walkers_x[walker, n - 1] + step_x
            walkers_y[walker, n] = walkers_y[walker, n - 1] + step_y

    return walkers_x, walkers_y

# Set the number of walkers and steps for 2b)
num_walkers_2b = 5
N_2b = 500

# Generate random walker data in 2D for 2b)
all_walkers_x, all_walkers_y = random_walkers_2D(num_walkers_2b, N_2b)

# Plotting for 2b)
plt.figure(figsize=(10, 6))
for i in range(num_walkers_2b):
    plt.plot(all_walkers_x[i], all_walkers_y[i], marker='o', alpha=0.7, label=f'Walker {i + 1}')

plt.xlabel('X')
plt.ylabel('Y')
plt.title(f'2b) {num_walkers_2b} Random Walkers in 2D')
plt.legend()
plt.grid(True)
plt.show()

#2c):
import numpy as np

# Analytical functions for mean displacement and RMS
def analytical_mean_displacement(n):
    return np.array([0, 0])

def analytical_rms(n):
    return np.sqrt(n)

# Example usage for N = 50 (you can replace 50 with your desired number of steps)
N = 50

mean_displacement_at_N = analytical_mean_displacement(N)
rms_at_N = analytical_rms(N)

print(f"Mean Displacement at time step N: {mean_displacement_at_N}")
print(f"RMS at time step N: {rms_at_N}")

#2d)
import numpy as np
import matplotlib.pyplot as plt

# Function to simulate random walkers in 2D
def simulate_walkers_2D(num_walkers, num_steps):
    walkers = np.zeros((num_walkers, 2, num_steps + 1))

    # Simulate the random walkers in 2D
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

# Calculate mean RMS for each time step from random walks
rms_mean_ten = np.mean(np.std(ten_walkers, axis=1), axis=0)
rms_mean_hundred = np.mean(np.std(hundred_walkers, axis=1), axis=0)
rms_mean_thousand = np.mean(np.std(thousand_walkers, axis=1), axis=0)

plt.plot(range(num_steps + 1), rms_mean_ten, label='M = 10', marker='o', alpha=0.7)
plt.plot(range(num_steps + 1), rms_mean_hundred, label='M = 100', marker='o', alpha=0.7)
plt.plot(range(num_steps + 1), rms_mean_thousand, label='M = 1000', marker='o', alpha=0.7)
plt.xlabel('Number of Steps')
plt.ylabel('RMS')
plt.title('RMS vs. Number of Steps')
plt.legend()
plt.grid(True)
plt.show()
