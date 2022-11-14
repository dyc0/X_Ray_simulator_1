from sympy import *

# Quadratic equation for line-ellipsoid intersection

x, y, z, rx, ry, rz, a, b, c, d = symbols('x y z rx ry rz a b c d')
init_printing(use_unicode=True)

# ((x + d * rx)/a)**2 + ((y + d * ry)/b)**2 + ((z + d * rz)/c)**2 -1

expr = expand(((x + d * rx)/a)**2 + ((y + d * ry)/b)**2 + ((z + d * rz)/c)**2 - 1)
expr = collect(expr, d)
print(expr)