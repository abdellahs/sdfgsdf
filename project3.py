
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
