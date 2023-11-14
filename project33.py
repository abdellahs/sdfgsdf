

#1a
import numpy as np
import matplotlib.pyplot as plt

def random_walker_1D(N):
    x = np.zeros(N + 1)  # Initialize an array to store the position at each step
    for n in range(1, N + 1):
        step = np.random.choice([-1, 0, 1])  # Randomly choose a step from {-1, 0, 1}
        x[n] = x[n - 1] + step
    return x

# Set the number of steps
N = 50

# Generate random walker data
walker_path = random_walker_1D(N)

# Plot the displacement as a function of the number of steps
plt.plot(range(N + 1), walker_path, marker='o')
plt.xlabel('Number of Steps')
plt.ylabel('Displacement')
plt.title('1D Random Walker')
plt.grid(True)
plt.show()

#1B

import numpy as np
import matplotlib.pyplot as plt

def random_walkers_1D(num_walkers, N):
    walkers = np.zeros((num_walkers, N + 1))  # Initialize an array to store positions for each walker

    for walker in range(num_walkers):
        for n in range(1, N + 1):
            step = np.random.choice([-1, 0, 1])  # Randomly choose a step from {-1, 0, 1}
            walkers[walker, n] = walkers[walker, n - 1] + step

    return walkers

# Set the number of walkers and steps
num_walkers = 1000
N = 500

# Generate random walker data
all_walkers = random_walkers_1D(num_walkers, N)

# Plot the displacement of each walker as a function of the number of steps
for i in range(num_walkers):
    plt.plot(range(N + 1), all_walkers[i], marker='o', alpha=0.7, label=f'Walker {i + 1}')

plt.xlabel('Number of Steps')
plt.ylabel('Displacement')
plt.title(f'{num_walkers} Random Walkers in 1D')
plt.grid(True)
plt.show()

#1c

# Analytical expressions
# Mean displacement at time step n: ⟨𝑥𝑛⟩=𝑛⋅⟨Δ𝑥⟩
# RMS at time step n: √⟨𝑥𝑛2⟩=√𝑛⋅⟨(Δ𝑥)2⟩
# For this random walk, ⟨Δ𝑥⟩=0 and ⟨(Δ𝑥)2⟩=2/3

# Calculate mean displacement for each time step
mean_displacement = np.arange(0, N + 1) * 0  # Since ⟨Δ𝑥⟩=0

# Calculate RMS for each time step
rms = np.sqrt(np.arange(0, N + 1) * (2 / 3))

# Print analytical properties
print(f"Mean Displacement at time step N: {mean_displacement[-1]}")
print(f"RMS at time step N: {rms[-1]}")


#d

import numpy as np
import matplotlib.pyplot as plt

# Function to generate random walker data
def random_walkers_1D(num_walkers, N):
    walkers = np.zeros((N + 1, num_walkers))
    for walker in range(num_walkers):
        for n in range(1, N + 1):
            step = np.random.choice([-1, 0, 1])
            walkers[n, walker] = walkers[n - 1, walker] + step
    return walkers

# Set the number of steps
N = 500

# Load random walker data from previous simulation
num_walkers = 1000
all_walkers = random_walkers_1D(num_walkers, N)


# Analytical expressions
mean_displacement_analytical = np.arange(0, N + 1) * 0
rms_analytical = np.sqrt(np.arange(0, N + 1) * (2 / 3))

# Index slicing for different walker populations
ten_walkers = all_walkers[:, :10]
hundred_walkers = all_walkers[:, :100]
thousand_walkers = all_walkers[:, :1000]

# Calculate mean displacement and RMS for each time step from random walks
mean_displacement_ten = np.mean(ten_walkers, axis=1)
mean_displacement_hundred = np.mean(hundred_walkers, axis=1)
mean_displacement_thousand = np.mean(thousand_walkers, axis=1)

rms_ten = np.std(ten_walkers, axis=1, ddof=1)
rms_hundred = np.sqrt(np.mean(hundred_walkers**2, axis=1))
rms_thousand = np.sqrt(np.mean(thousand_walkers**2, axis=1))

# Plotting
plt.figure(figsize=(12, 6))

# Mean Displacement plot
plt.subplot(1, 2, 1)
plt.plot(range(N + 1), mean_displacement_analytical, label='Analytical', linestyle='--', color='black')
plt.plot(range(N + 1), mean_displacement_ten, label='M = 10', marker='o', alpha=0.7)
plt.plot(range(N + 1), mean_displacement_hundred, label='M = 100', marker='o', alpha=0.7)
plt.plot(range(N + 1), mean_displacement_thousand, label='M = 1000', marker='o', alpha=0.7)
plt.xlabel('Number of Steps')
plt.ylabel('Mean Displacement')
plt.title('Mean Displacement vs. Number of Steps')
plt.legend()
plt.grid(True)

# RMS plot
plt.subplot(1, 2, 2)
plt.plot(range(N + 1), rms_analytical, label='Analytical', linestyle='--', color='black')
plt.plot(range(N + 1), rms_ten, label='M = 10', marker='o', alpha=0.7)
plt.plot(range(N + 1), rms_hundred, label='M = 100', marker='o', alpha=0.7)
plt.plot(range(N + 1), rms_thousand, label='M = 1000', marker='o', alpha=0.7)
plt.xlabel('Number of Steps')
plt.ylabel('RMS')
plt.title('RMS vs. Number of Steps')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()

import numpy as np
import matplotlib.pyplot as plt

# 2a) Random walker in two dimensions
def random_walker_2D(N):
    x = np.zeros(N + 1)
    y = np.zeros(N + 1)

    for n in range(1, N + 1):
        step_x = np.random.choice([-1, 0, 1])
        step_y = np.random.choice([-1, 0, 1])

        x[n] = x[n - 1] + step_x
        y[n] = y[n - 1] + step_y

    return x, y

# Set the number of steps for 2a)
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

import numpy as np
import matplotlib.pyplot as plt

# 2a) Random walker in two dimensions
def random_walker_2D(N):
    x = np.zeros(N + 1)
    y = np.zeros(N + 1)

    for n in range(1, N + 1):
        step_x = np.random.choice([-1, 0, 1])
        step_y = np.random.choice([-1, 0, 1])

        x[n] = x[n - 1] + step_x
        y[n] = y[n - 1] + step_y

    return x, y

# Set the number of steps for 2a)
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

def analytical_mean_displacement(n):
    # Mean displacement at time step n
    return np.array([0, 0])

def analytical_rms(n):
    # RMS at time step n
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
