import numpy as np
from jax import grad, jacfwd
from sympy import *
from scipy.optimize import fsolve
import vtkmodules.vtkInteractionStyle
import vtkmodules.vtkRenderingOpenGL2
from vtkmodules.vtkCommonColor import vtkNamedColors
from vtkmodules.vtkInteractionStyle import vtkInteractorStyleTrackballCamera
from vtkmodules.vtkCommonCore import vtkPoints, vtkUnsignedCharArray
from vtkmodules.vtkCommonDataModel import (
    vtkCellArray,
    vtkPolyData
)
from vtkmodules.vtkRenderingCore import (
    vtkActor,
    vtkPolyDataMapper,
    vtkRenderWindow,
    vtkRenderWindowInteractor,
    vtkRenderer
)

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

    def critical_points(self):
        i = 0


crits = []
bifurcations = []
for s in np.arange(-2, 2, 0.04):
    bifurcations.append((s, -s, 0, 0))
    for t in np.arange(-2, 2, 0.04):
        if s + t > 0:
            crits.append((s, t,  sqrt(s + t), 0))
            crits.append((s, t, -sqrt(s + t), 0))

#TODO Show Points with VTK
points = vtkPoints()
vertices = vtkCellArray()
polydata = vtkPolyData()
colors = vtkUnsignedCharArray()
colors.SetNumberOfComponents(4)
colors.SetNumberOfTuples(len(crits)+len(bifurcations))

for i in range(len(crits)):
    rgba = [255, 0, 0, 255]
    colors.InsertTuple(i, rgba)
    p = [crits[i][0], crits[i][1], crits[i][2]]
    pid = points.InsertNextPoint(p)
    vertices.InsertNextCell(1)
    vertices.InsertCellPoint(pid)

for i in range(len(bifurcations)):
    rgba = [0, 255, 0, 255]
    colors.InsertTuple(i+len(crits), rgba)
    p = [crits[i][0], crits[i][1], crits[i][2]]
    pid = points.InsertNextPoint(p)
    vertices.InsertNextCell(1)
    vertices.InsertCellPoint(pid)


polydata.SetPoints(points)
polydata.SetVerts(vertices)
polydata.GetCellData().SetScalars(colors);
mapper = vtkPolyDataMapper()
mapper.SetInputData(polydata)
actor = vtkActor()
actor.SetMapper(mapper)
actor.GetProperty().SetPointSize(10)
renderer = vtkRenderer()
renderer.AddActor(actor)
renderWindow = vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderer.SetBackground([0, 0, 255])
interactor = vtkRenderWindowInteractor()
interactor.SetRenderWindow(renderWindow)
style = vtkInteractorStyleTrackballCamera()
interactor.SetInteractorStyle(style)
renderWindow.Render()
interactor.Start()


#vf = VectorField(f_3p3d_circle, 3, 3)
#print(vf.fff((0.1, 0.2, 0.3, 0.4, 0.5, 0.6)))
#m_vf = VectorField([vf.fff, f_3p3d_circle_x, f_3p3d_circle_y, f_3p3d_circle_z], 2, 4)
#print(m_vf.fff((0.1, 0.2, 0.3, 0.4, 0.5, 0.6)))
#mm_vf = VectorField([m_vf.fff, vf.fff, f_3p3d_circle_x, f_3p3d_circle_y, f_3p3d_circle_z], 1, 5)
#print(mm_vf.fff((0.1, 0.2, 0.3, 0.4, 0.5, 0.6)))

#min = -2
#max = 2
#size = 100
#s, t, x, y = symbols('s, t, x, y', real=True)
#eq1 = Eq(x**2-t-s, 0)
#eq2 = Eq(y, 0)
#eq3 = Eq(x*2, 0)

#solutions_c = solve([eq1, eq2], [x, y])
#print(solutions_c)
#for solution in solutions_c:
#    for i_s in range(100):
#        for i_t in range(100):
#            adjusted_i_s = min+((max-min)/size)*i_s
#            adjusted_i_t = min+((max-min)/size)*i_t
#            soln = tuple(v.evalf().subs({t: adjusted_i_t, s: adjusted_i_s}) for v in solution)
#            print(soln)

#solutions_b = solve([eq1, eq2, eq3], [t, x, y])
#print(solutions_b)
#for i_s in range(100):
#    adjusted_i_s = min + ((max - min) / size) * i_s
#    soln = tuple(v.evalf().subs({s: adjusted_i_s}) for v in solutions_b)
#    print(soln)
#Calculates the numerical solutions in dependence of a single parameter

#ignore imaginary solutions
#    for root in y:
#        if "I" not in str(root):
#            print("This One:" + str(root.evalf()))


#s, t, u, x, y, z = symbols('s, t, u, x, y, z')
#eq1 = Eq(x**2+s**2+t**2+u**2, 0)
#eq2 = Eq(y, 0)
#eq3 = Eq(z, 0)
#
#sol = solve([eq1, eq2, eq3], [s, t, u, x, y, z])
#print(sol)
#Maybe Differentiation with sympy too, since it supports the system of equation


#def test(vars):
#    return [vf.base_function[0](vars), vf.base_function[1](vars), vf.base_function[2](vars)]
#
#vars = fsolve(test, (0, 0, 0, 0, 0, 0))
#does not work, because it can only solve for single points, not parameter dependent lines