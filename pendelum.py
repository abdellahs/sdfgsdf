import numpy as np
import matplotlib.pyplot as plt
from ode import ODEModel, ODEResult, solve_ode, plot_ode_solution

# Exercise 2a):

class Pendulum(ODEModel):
    def __init__(self, L: float = 1, M: float = 1, g: float = 9.81) -> None: 

        self.M = M 
        self.L = L
        self.g = g 

    def __call__(self, t: float, u: np.ndarray) -> np.ndarray:

        theta, omega = u
        dtheta = omega
        domega = (-self.g/self.L)*np.sin(theta)

        return np.array([dtheta, domega])
        
    @property
    def num_states(self) -> int:
        return 2


# Exercise 2b):
def exercise_2b(
    u0: np.ndarray,
    T: float,
    dt: float,
) -> ODEResult:

    model = Pendulum()  ###
    result = solve_ode(model, u0, T, dt) ####

    return result


# Exercise 2c)
from dataclasses import dataclass
import numpy as np


@dataclass
class PendulumResults:
    res: ODEResult  
    pendulum: Pendulum 


Exercise 2d)
    @property 
    def omega(self) -> np.ndarray:
        return self.res.solution[1]

    @property
    def theta(self) -> np.ndarray:
        return self.res.solution[0]


    @property 
    def y(self) -> np.ndarray:
        return -self.pendulum.L*np.cos(self.theta)

    @property
    def x(self) -> np.ndarray:
        return self.pendulum.L*np.sin(self.theta)

    @property 
    def potential_energy(self) -> np.ndarray:
        return self.pendulum.g*(self.y + self.pendulum.L)

    @property
    def vx(self) -> np.ndarray:
        return np.gradient(self.x, self.res.time)

    @property 
    def vy(self) -> np.ndarray:
        return np.gradient(self.y, self.res.time)
    
    @property
    def kinetic_energy(self) -> np.ndarray:
        return (1/2)*(self.vx**2 + self.vy**2)

    @property
    def total_energy(self) -> np.ndarray:
        return self.potential_energy + self.kinetic_energy

#
    
from typing import Optional
def solve_pendulum(
    u0: np.ndarray,
    T: float,
    dt: float,
    pendulum: Optional[Pendulum] = Pendulum()
) -> PendulumResults:
    

    result = solve_ode(pendulum, u0, T, dt)
    pendulum_results = PendulumResults(result, pendulum)

    return pendulum_results

# Exercise 2g): 

def plot_energy(res: PendulumResults, filename: Optional[str] = None) -> None:

    p_ = res.potential_energy
    k_ = res.kinetic_energy
    tot_ = res.total_energy
    t_ = res.res.time
    
    fig, ax = plt.subplots()
    ax.plot(t_, p_, label="potential energy")
    ax.plot(t_, k_, label="kinetic energy")
    ax.plot(t_, tot_, label="total energy")
    
    ax.set_title("Potential & kinetic energi")
    ax.set_xlabel("Time")
    ax.set_ylabel("Energy")
    ax.grid(True)
    ax.legend()
    
    if filename != None:
        fig.savefig(filename)
    else:
        plt.figure()
    

def exercise_2g() -> PendulumResults:

    u0 = np.array([np.pi/6, .35])
    T = 10
    dt = .01
    result = solve_pendulum(u0, T, dt)

    return result


# Exercise 2h):

class DampenedPendulum(Pendulum):
    def __init__(self, B: float, L: float = 1, M: float = 1, g: float = 9.81) -> None:
        super().__init__(L, M, g)
        self.B = B

    def __call__(self, t, u):
        theta, omega = u
        dtheta = omega
        domega = (-self.g/self.L) * np.sin(theta) - self.B * omega

        return np.array([dtheta, domega])


def exercise_2h():
    u0 = np.array([np.pi/6, .35])
    T = 10
    dt = .01

    result = solve_pendulum(u0, T, dt, DampenedPendulum(1))
    plot_energy(result, "energy_damped.png")

if __name__ == "__main__":

from typing import Optional
  
    result_exercise_2b = exercise_2b(np.array([np.pi/6, .35]), 10, .01)
    labels = [r"$\theta$", r"$\omega$"]
    plot_ode_solution(result_exercise_2b, labels, "exercise_2b.png")

    
    result_exercise_2g = exercise_2g()
    plot_energy(result_exercise_2g, "energy_single.png")
   
    exercise_2h()
