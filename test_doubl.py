from ode import solve_ode
from double_pendulum import DoublePendulum, solve_double_pendulum
import numpy as np
import pytest


model = DoublePendulum()


def test_derivatives_at_rest_is_zero():
    u = np.array([0, 0, 0, 0])
    dudt = model(0, u)
    assert all(dudt == 0)

@pytest.mark.parametrize(
    "theta1, theta2, expected", [
    (0, 0, 0),
    (0, 0.5, 3.386187037),
    (0.5, 0, -7.678514423),
    (0.5, 0.5, -4.703164534)])

def test_domega1_dt(theta1, theta2, expected):
    model = DoublePendulum()
    t = 0
    y = (theta1, 0.25, theta2, 0.15)
    dtheta1_dt, domega1_dt, _, _ = model(t, y)

    assert np.isclose(dtheta1_dt, 0.25)
    assert np.isclose(domega1_dt, expected)

@pytest.mark.parametrize(
    "theta1, theta2, expected", [
    (0, 0, 0.0),
    (0, 0.5, -7.704787325),
    (0.5, 0, 6.768494455),
    (0.5, 0.5, 0.0)])

def test_domega2_dt(theta1, theta2, expected):
    model = DoublePendulum()
    t = 0
    y = (theta1, 0.25, theta2, 0.15)
    _, _, dtheta2_dt, domega2_dt = model(t, y)
    assert np.isclose(dtheta2_dt, 0.15)
    assert np.isclose(domega2_dt, expected)

def test_solve_pendulum_ode_with_zero_ic():
    res_l  = solve_ode(DoublePendulum(), np.array([0,0,0,0]), 10, .1)

    assert all(res_l.solution[0] == 0)
    assert all(res_l.solution[1] == 0)
    assert all(res_l.solution[2] == 0)
    assert all(res_l.solution[3] == 0)

def test_solve_double_pendulum_function_zero_ic():
    res_l = solve_double_pendulum(np.array([0, 0, 0, 0]), 10, pendulum=dp)

    assert all(res_l.theta1 == 0)
    assert all(res_l.omega1 == 0)
    assert all(res_l.theta2 == 0)
    assert all(res_l.omega2 == 0)
    
