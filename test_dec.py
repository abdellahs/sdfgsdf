from exp_decay import ExponentialDecay
from ode import ODEModel, solve_ode, plot_ode_solution, ODEResult
import numpy as np
import pytest


model = ExponentialDecay(0.4)
def test_ExponentialDecay():

    t = 0.0
    u = np.array([3.2])
    du_dt = model(t, u)
    assert np.isclose(du_dt[0], -1.28)

def test_negative_decay_raises_ValueError_a():
    with pytest.raises(ValueError):
        model = ExponentialDecay(-3)


def test_negative_decay_raises_ValueError_b():
    with pytest.raises(ValueError):
        model.decay = -1.0  
              
def test_num_states():
    assert model.num_states == 1


from exception import InvalidInitialConditionError
def test_solve_with_different_number_of_initial_states():
    with pytest.raises(InvalidInitialConditionError):
        solve_ode(model, u0 = [0,1], T = 10.0, dt = 0.2)

@pytest.mark.parametrize("a, u0, T, dt", [
    (0.4, np.array([4]), 10, 0.01),
    (0, np.array([6]), 15, .2)])

def test_solve_time(a, u0, T, dt):
    model = ExponentialDecay(a)
    res = solve_ode(model, u0, T, dt)

    res_computed = res.time
    res_expected = np.arange(0, T, dt)

    assert res_expected.all() == res_computed.all()
