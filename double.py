from ode import ODEModel, ODEResult, solve_ode
import numpy as np
import matplotlib.pyplot as plt

#Exercise 3a):

class DoublePendulum(ODEModel):
    def __init__(self, L1: float = 1, L2: float = 1, M1: float = 1, M2: float = 1, g: float = 9.81) -> None:
        self.g = g
        self.L1 = L1
        self.L2 = L2
        self.M1 = M1
        self.M2 = M2
    
    def __call__(self, t: float, u: np.ndarray):
        theta1, omega1, theta2, omega2 = u
        dtheta1_dt = omega1
        dtheta2_dt = omega2
        dtheta = theta2 - theta1

        domega1_dt = (self.L1*(omega1**2)*np.sin(dtheta)*np.cos(dtheta) + self.g*np.sin(theta2)*np.cos(dtheta) + self.L2*(omega2**2)*np.sin(dtheta) - 2*self.g*np.sin(theta1))/(2*self.L1 - self.L1*(np.cos(dtheta))**2)
        domega2_dt = (-self.L2*(omega2)**2*np.sin(dtheta)*np.cos(dtheta) + 2*self.g*np.sin(theta1)*np.cos(dtheta) - 2*self.L1*(omega1**2)*np.sin(dtheta) - 2*self.g*np.sin(theta2))/(2*self.L2 - self.L2*(np.cos(dtheta))**2)

        return np.array([dtheta1_dt, domega1_dt, dtheta2_dt, domega2_dt])


#Exercise 3c):

    @property 
    def num_states(self) -> int:
        return 4

from dataclasses import dataclass

@dataclass
class DoublePendulumResults:
    results: ODEResult
    pendulum: DoublePendulum

    @property
    def theta1(self) -> np.ndarray:
        return self.results.solution[0]

    @property 
    def omega1(self) -> np.ndarray:
        return self.results.solution[1]

    @property
    def theta2(self) -> np.ndarray:
        return self.results.solution[2]

    @property 
    def omega2(self) -> np.ndarray:
        return self.results.solution[3]

    @property
    def x1(self) -> np.ndarray:
        return self.pendulum.L1*np.sin(self.theta1)

    @property 
    def y1(self) -> np.ndarray:
        return -self.pendulum.L1*np.cos(self.theta1)

    @property
    def x2(self) -> np.ndarray:
        return self.x1 + self.pendulum.L2*np.sin(self.theta2)

    @property
    def y2(self) -> np.ndarray:
        return self.y1 - self.pendulum.L2*np.cos(self.theta2)

    @property
    def potential_energy(self) -> np.ndarray:
        P_1 = self.pendulum.M1*self.pendulum.g*(self.y1 + self.pendulum.L1)
        P_2 = self.pendulum.M2*self.pendulum.g*(self.y2 + self.pendulum.L1 + self.pendulum.L2)
        
        return P_1 + P_2

    @property
    def vx1(self) -> np.ndarray:
        return np.gradient(self.x1, self.results.time)
      
    @property
    def vx2(self) -> np.ndarray:
        return np.gradient(self.x2, self.results.time)
      
    @property 
    def vy1(self) -> np.ndarray:
        return np.gradient(self.y1, self.results.time)

    @property 
    def vy2(self) -> np.ndarray:
        return np.gradient(self.y2, self.results.time)


    
    # Exercise 3d):
    @property
    def kinetic_energy(self) -> np.ndarray:
        K_1 = (1/2)*self.pendulum.M1*(self.vx1**2 + self.vy1**2)
        K_2 = (1/2)*self.pendulum.M1*(self.vx2**2 + self.vy2**2)

        return K_1 + K_2

    @property
    def total_energy(self) -> np.ndarray:
        return self.potential_energy + self.kinetic_energy

from typing import Optional
def solve_double_pendulum(
    u0: np.ndarray,
    T: float,
    dt: float = .01,
    pendulum: Optional[DoublePendulum] = DoublePendulum()
) -> DoublePendulumResults:
    
    result__ = solve_ode(pendulum, u0, T, dt)
    pendulum_results = DoublePendulumResults(result__, pendulum)

  
    return pendulum_results


from pendulum import plot_energy
def exercise_3d():
    
    u0 = np.array([np.pi/6, 0.35, 0, 0])
    T = 10
    dt = 0.01
    resul = solve_double_pendulum(u0, T, dt)
    plot_energy(resul, "energy_double.png")
