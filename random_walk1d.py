import numpy as np  # Importer NumPy-biblioteket og gi det aliaset np
import matplotlib.pyplot as plt  # Importer matplotlib-biblioteket og gi det aliaset plt

def random_walker_1D(N):
    x = np.zeros(N + 1)  # Initialiser en array for å lagre posisjonen ved hver steg
### Dette er en for-løkke som itererer gjennom verdier av n. range(1, N + 1) genererer tallene fra 1 til N (inkludert),
 og for hver iterasjon i løkken blir n satt til en av disse verdiene.
    for n in range(1, N + 1): 
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
