
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp

#
import abc
class ODEModel(abc.ABC):

    @abc.abstractmethod
    def __call__(self, t: float, u: np.ndarray) -> np.ndarray:
        raise NotImplementedError

    @property
    def num_states(self) -> int:
        raise NotImplementedError

from typing import NamedTuple
class ODEResult(NamedTuple):
    time: np.ndarray
    solution: np.ndarray

    @property
    def num_states(self) -> float:
        return self.solution.shape[0]

  
    @property
    def num_timepoints(self) -> float:
        return self.time.shape[0]


def solve_ode(
    model: ODEModel,
    c,
    T: float,
    dt : float 
) -> ODEResult:
    
class InvalidInitialConditionError(RuntimeError):
    def __init__(self, message):            
        super().__init__(message)

    if len(u0) != model.num_states:
        raise InvalidInitialConditionError(f"u0 needs to match the number of state variables of {type(model).__name__}. Len(u0) = {len(u0)}, and num_states = {model.num_states}.")

    t = np.arange(0, T, dt)
    sol = solve_ivp(fun=model, t_span=(0,T), y0=u0, t_eval=t, method="Radau")
    res = ODEResult(time=sol["t"], solution=sol["y"])

    return res

#

from typing import Optional, List
def plot_ode_solution(
    results: ODEResult,
    state_labels: Optional[List[str]] = None,
    filename: Optional[str] = None,
) -> None:


    sol = results.solution
    t = results.time
 
    if state_labels == None:
        state_labels = [("State " + str(i)) for i in range(results.num_states)]
    
    for i in range(len(sol)):
        if t.shape == sol[i].shape:
            plt.plot(t, sol[i], label=state_labels[i])

    plt.title("ODE Results")
    plt.xlabel("Time")
    plt.ylabel("ODE solution")
    plt.grid(True)
    plt.legend()

    if filename != None:
        plt.savefig(filename)
    else:
        plt.show()
