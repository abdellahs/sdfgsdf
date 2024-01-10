import numpy as np  # Importer NumPy-biblioteket og gi det aliaset np
import matplotlib.pyplot as plt  # Importer matplotlib-biblioteket og gi det aliaset plt

def random_walker_1D(N):
    x = np.zeros(N + 1)  # Initialiser en array for å lagre posisjonen ved hver steg
### Dette er en for-løkke som itererer gjennom verdier av n. range(1, N + 1) genererer tallene fra 1 til N (inkludert),
 og for hver iterasjon i løkken blir n satt til en av disse verdiene.
    for n in range(1, N + 1): 
        # # Oppdaterer posisjonen ved det nåværende steg ved å legge til det tilfeldige steget
        step = np.random.choice([-1, 0, 1])  # Velg tilfeldig steg fra {-1, 0, 1}
        x[n] = x[n - 1] + step
    return x

# Sett antall steg
N = 50

# Generer data for tilfeldig vandrer
walker_path = random_walker_1D(N)

# Plot forskyvning som en funksjon av antall steg
plt.plot(range(N + 1), walker_path, marker='o')  # Plot vandrerens sti med markører ved hvert steg
plt.xlabel('Antall steg')  # Sett etikett for x-aksen
plt.ylabel('Forskyvning')  # Sett etikett for y-aksen
plt.title('1D Tilfeldig Vandrer')  # Sett tittel på plottet
plt.grid(True)  # Legg til rutenett i plottet
plt.show()  # Vis plottet


import numpy as np  # Import the NumPy library and alias it as np
import matplotlib.pyplot as plt  # Import the matplotlib library and alias it as plt

# 2a) Tilfeldig vandrer i to dimensjoner
def random_walker_2D(N):
    x = np.zeros(N + 1)  # Initialiser en array for x-koordinatene
    y = np.zeros(N + 1)  # Initialiser en array for y-koordinatene

    for n in range(1, N + 1):
        step_x = np.random.choice([-1, 0, 1])  # Velg tilfeldig steg for x fra {-1, 0, 1}
        step_y = np.random.choice([-1, 0, 1])  # Velg tilfeldig steg for y fra {-1, 0, 1}

        x[n] = x[n - 1] + step_x  # Oppdater x-koordinaten basert på det tilfeldige steget
        y[n] = y[n - 1] + step_y  # Oppdater y-koordinaten basert på det tilfeldige steget

    return x, y

# Sett antall steg for 2a)
N_2a = 50

# Generer data for tilfeldig vandrer i 2D for 2a)
x_2a, y_2a = random_walker_2D(N_2a)

# Plott for 2a)
plt.plot(x_2a, y_2a, marker='o')  # Plott vandrerens sti med markører
plt.xlabel('X')  # Sett etikett for x-aksen
plt.ylabel('Y')  # Sett etikett for y-aksen
plt.title('2a) 2D Tilfeldig Vandrer')  # Sett tittel på plottet
plt.grid(True)  # Legg til rutenett i plottet
plt.show()  # Vis plottet
