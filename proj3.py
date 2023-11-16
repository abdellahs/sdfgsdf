# maze_walker.py

from __future__ import annotations
import matplotlib.pyplot as plt
import numpy as np
from typing import Protocol
from matplotlib.animation import FuncAnimation
import matplotlib.axes
import matplotlib.image

class InvalidSquareError(LookupError):
    pass

def get_legal_line(maze: np.ndarray, y: int) -> list[tuple[int, int]]:
    if not isinstance(y, (int, np.integer)):
        raise TypeError("line number y must be an int.")
    return [(x[0], y) for x in np.argwhere(maze[:, y])]

def plot(maze: np.ndarray, ax: matplotlib.axes.Axes | None = None) -> matplotlib.image.AxesImage:
    _ax = ax or plt.gca()
    im = _ax.imshow(maze.T, origin="lower", cmap="gray")
    im.set_clim(vmax=1)
    _ax.set_axis_off()
    return im

def circular(R: int = 100, padding: int = 2) -> np.ndarray:
    N = int(2 * (R + padding) + 1)
    c = (N - 1) // 2
    x = np.arange(N)
    xx, yy = np.meshgrid(x, x)
    return (xx - c) ** 2 + (yy - c) ** 2 <= R**2

def example() -> np.ndarray:
    arr = np.zeros((7, 7), dtype=bool)
    indices = np.array([1, 3, 5])
    arr[1:-1, indices] = True
    arr[indices, 1:-1] = True
    return arr

def layered_labyrinth(layers: int = 2, width: int = 3, height: int = 5) -> np.ndarray:
    bars = 3 ** (layers + 1)
    Mx = 2 + width * bars + bars - 1
    My = 2 + height * (layers + 2) + width * (layers + 1)
    arr = np.zeros((Mx, My), dtype=bool)
    jump = 4
    for n in range(layers + 2):
        start0 = 2 * 3**n - 1
        start1 = n * (height + width) + 1
        end1 = start1 + height
        for j in range(width):
            arr[start0 + j :: jump, start1:end1] = True
        if n != layers + 1:
            arr[start0:-start0, end1 : end1 + width] = True
        jump *= 3
    return arr

class MazeWalker(Protocol):
    x: np.ndarray
    y: np.ndarray
    maze: np.ndarray

    def move(self) -> None:
        ...

class Animation:
    def __init__(self, mw: MazeWalker, color: str = "springgreen"):
        self._mw = mw
        self.color = color

    def plot(self, size: int, show: bool = True) -> matplotlib.figure.Figure:
        fig, ax = plt.subplots()
        plot(self._mw.maze)
        self._pos = ax.scatter(
            self._mw.x,
            self._mw.y,
            c=self.color,
            s=size,
            alpha=0.4,
        )
        ax.set_title("Frame 0")
        if show:
            plt.show()
        return fig

    def _update_frame(self, i: int) -> tuple[matplotlib.collections.PathCollection]:
        self._mw.move()
        self._pos.set_offsets(np.array([self._mw.x, self._mw.y]).T)
        self._pos.axes.title.set_text(f"Frame {i}")
        return (self._pos,)

    def animate(
        self,
        N: int,
        size: int = 10,
        interval: int = 1,
        filename: str = "",
        show: bool = True,
    ) -> FuncAnimation:
        fig = self.plot(size, show=False)
        animation = FuncAnimation(
            fig,
            self._update_frame,
            interval=interval,
            repeat=False,
            frames=N,
        )
        if filename != "":
            animation.save(filename)
        if show:
            plt.show()
        return animation

# In maze_walker.py

import numpy as np

class MazeWalker:
    def __init__(self, M, maze, rng, r0=(1, 1)):
        self._M = M
        self._maze = maze
        self._rng = rng
        self._r0 = r0
        self._positions = np.zeros((M, 2), dtype=int)
        self.initialize_walkers(r0)

    @property
    def M(self):
        return self._M

    @property
    def maze(self):
        return self._maze

    def initialize_walkers(self, r0: tuple[int, int]) -> None:
        if not self._maze[r0]:
            raise InvalidSquareError("Invalid starting point: inside a wall or outside the maze.")
        
        self._positions[:, 0] = r0[0]
        self._positions[:, 1] = r0[1]

    @property
    def x(self):
        return self._positions[:, 0]

    @property
    def y(self):
        return self._positions[:, 1]

    def move(self) -> None:
        dx = self._rng.integers(low=-1, high=2, size=self._M)
        dy = self._rng.integers(low=-1, high=2, size=self._M)
        steps = np.column_stack((dx, dy))
        legal_steps = self._remove_illegal(steps)
        self._positions[:, 0] += legal_steps[:, 0]
        self._positions[:, 1] += legal_steps[:, 1]

    def _remove_illegal(self, dr: np.ndarray) -> np.ndarray:
        legal_steps = np.copy(dr)
        for i in range(self._M):
            x, y = self._positions[i]
            if not self._maze[x, y]:
                legal_steps[i] = [0, 0]
        return legal_steps

if __name__ == "__main__":
    circular_maze = circular()

    try:
        rng = np.random.default_rng()
        walker = MazeWalker(M=500, maze=circular_maze, rng=rng, r0=(100, 100))
        animation = Animation(walker)
        anim = animation.animate(N=200)
        
        # Keep the plot open until the animation is shown or saved
        plt.show()

        # Explicitly close the figure after showing the animation
        plt.close()

    except InvalidSquareError as e:
        print(f"Error: {e}")



plt.close()
