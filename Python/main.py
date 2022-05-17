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

    def fff(self, vars):
        jac = self.jacobi()

        matrix = []
        for x in range(self.space_dimensions):
            line = []
            values = jac[x](vars)
            for y in range(self.space_dimensions):
                line.append(values[self.parameter_dimensions+y])
            matrix.append(line)

        return self.determinant(matrix)

    def determinant(self, matrix):
        if len(matrix) == 1:
            return matrix[0][0]
        else:
            value = 0
            for i in range(len(matrix)):
                next_matrix = []
                for x in range(1, len(matrix)):
                    next_line = []
                    for y in range(len(matrix)):
                        if y != i:
                            next_line.append(matrix[x][y])
                    next_matrix.append(next_line)
                value += matrix[0][i] * pow(-1, i) * self.determinant(next_matrix)
        return value


vf = VectorField(f_3p3d_circle, 3, 3)
print(vf.fff((0.1, 0.2, 0.3, 0.4, 0.5, 0.6)))
m_vf = VectorField([vf.fff, f_3p3d_circle_x, f_3p3d_circle_y, f_3p3d_circle_z], 2, 4)
print(m_vf.fff((0.1, 0.2, 0.3, 0.4, 0.5, 0.6)))
mm_vf = VectorField([m_vf.fff, vf.fff, f_3p3d_circle_x, f_3p3d_circle_y, f_3p3d_circle_z], 1, 5)
print(mm_vf.fff((0.1, 0.2, 0.3, 0.4, 0.5, 0.6)))
