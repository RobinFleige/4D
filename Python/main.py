import numpy as np
from jax import grad, jacfwd


def f_2p2d_simple_x(vars):
    s, t, x, y = vars
    return x**2-s-t


def f_2p2d_simple_y(vars):
    s, t, x, y = vars
    return y+s


f_2p2d_simple = [f_2p2d_simple_x, f_2p2d_simple_y]


def f_2p2d_double_x(vars):
    s, t, x, y = vars
    return (x**2+t)*(y-1)-(x**2+s)*(y+1)


def f_2p2d_double_y(vars):
    s, t, x, y = vars
    return (y-1)*(y+1)


f_2p2d_double = [f_2p2d_double_x, f_2p2d_double_y]


def f_3p3d_circle_x(vars):
    s, t, u, x, y, z = vars
    return x**2+s**2+t**2+u**2


def f_3p3d_circle_y(vars):
    s, t, u, x, y, z = vars
    return y


def f_3p3d_circle_z(vars):
    s, t, u, x, y, z = vars
    return z


f_3p3d_circle = [f_3p3d_circle_x, f_3p3d_circle_y, f_3p3d_circle_z]


class VectorField:

    def __init__(self, base_function, parameter_dimensions, space_dimensions):
        self.base_function = base_function
        self.parameter_dimensions = parameter_dimensions
        self.space_dimensions = space_dimensions
        self.dimensions = parameter_dimensions + space_dimensions

    def jacobi(self):
        # outer = function; inner = parameter
        jac_matrix = []
        for f in self.base_function:
            derivatives = grad(f)
            jac_matrix.append(derivatives)
        return jac_matrix

    def jacobi_values(self, vars):
        # outer = function; inner = parameter
        jac = self.jacobi()
        matrix = []
        for f in range(self.space_dimensions):
            matrix.append(list(jac[f](vars)))
        return matrix

    def fff_3(self, vars):
        jac = self.jacobi()
        return jac[0](vars)[2] * jac[1](vars)[3] - jac[0](vars)[3] * jac[1](vars)[2]

    def fff_4(self, vars):
        jac = self.jacobi()
        #TODO (Either create for many dimensions as fff_3 and fff_4 or create a single one for all(harder)


vf = VectorField(f_3p3d_circle, 3, 3)
print(vf.jacobi_values((0.1, 0.2, 0.3, 0.4, 0.5, 0.6)))
artificial_vf = VectorField([f_2p2d_simple_x, f_2p2d_simple_y, vf.fff_3], 3, 1)
#print(artificial_vf.fff_4((0.0, 0.0, 0.0, 0.0)))
