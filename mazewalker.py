#MazeWalker er en klasse som representerer 
#vandrere i en labyrint, med metoder for å initialisere, bevege seg og håndtere kollisjoner med vegger.
# Klasse for en labyrintvandrer
class MazeWalker:
    def __init__(self, M, maze, rng, r0=(1, 1)):
        # Initialiserer MazeWalker-objektet med gitt antall vandrere (M), labyrinten, RNG (Random Number Generator), og startposisjon (r0)
        self._M = M
        self._maze = maze
        self._rng = rng
        self._r0 = r0
        self._positions = np.zeros((M, 2), dtype=int)  # Lager en matrise for å lagre posisjonene til vandrerne
        self.initialize_walkers(r0)  # Initialiserer startposisjonene for vandrerne

    @property
    def M(self):
        # Getter-metode for å få antall vandrere
        return self._M

    @property
    def maze(self):
        # Getter-metode for å få labyrinten
        return self._maze



# 3b) Initialiserer vandrere
def initialize_walkers(self, r0: tuple[int, int]) -> None:
    # Sjekk om startpunktet er inni en vegg eller utenfor labyrinten
    if not self._maze[r0]:
        raise InvalidSquareError("Ugyldig startpunkt: inni en vegg eller utenfor labyrinten.")
    
    # Sett startposisjonen til vandrerne
    self._positions[:, 0] = r0[0]
    self._positions[:, 1] = r0[1]

@property
def x(self):
    # Hent x-koordinatene til vandrerposisjonene
    return self._positions[:, 0]

@property
def y(self):
    # Hent y-koordinatene til vandrerposisjonene
    return self._positions[:, 1]

# 3d) Bevegelse

#Funksjon: move simulerer bevegelsen av vandrerne i labyrinten.

def move(self) -> None:
    # Generer tilfeldige steg i x- og y-retning for hver vandrer
    dx = self._rng.integers(low=-1, high=2, size=self._M)
    dy = self._rng.integers(low=-1, high=2, size=self._M)
    
    # Lag en matrise av stegene
    steps = np.column_stack((dx, dy))
    
    # Fjern ulovlige steg basert på labyrinten
    legal_steps = self._remove_illegal(steps)
    
    # Oppdater x- og y-posisjonene med lovlige steg
    self._positions[:, 0] += legal_steps[:, 0]
    self._positions[:, 1] += legal_steps[:, 1]

# 3f) Walls

def _remove_illegal(self, dr: np.ndarray) -> np.ndarray:
    # Kopier de foreslåtte stegene for å sikre at originalmatrisen ikke endres
    legal_steps = np.copy(dr)
    
    # Gå gjennom hver vandrer for å sjekke om stegene er lovlige i henhold til labyrinten
    for i in range(self._M):
        x, y = self._positions[i]
        
        # Sjekk om posisjonen i labyrinten er en vegg, hvis det er tilfelle, sett stegene til [0, 0]
        if not self._maze[x, y]:
            legal_steps[i] = [0, 0]
    
    # Returner de lovlige stegene, der ulovlige steg er satt til [0, 0]
    return legal_steps

"""
Beskrivelse: Denne metoden, _remove_illegal, brukes av move-metoden for å filtrere ut steg som ville føre vandrerne gjennom vegger i labyrinten.

Variabler:

dr: En matrise som inneholder de foreslåtte stegene for hver vandrer.
legal_steps: En kopi av dr som vil bli endret for å fjerne steg gjennom vegger.
Løkke:

Løkken går gjennom hver vandrer og sjekker om den tilsvarende posisjonen i labyrinten er en vegg (not self._maze[x, y]).
Hvis vandren prøver å gå gjennom en vegg, blir stegene satt til [0, 0], som betyr at vandren ikke beveger seg.
Returnerer: Matrisen med lovlige steg, hvor steg gjennom vegger er satt til [0, 0].

"""
