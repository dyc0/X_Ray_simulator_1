from sympy import *

# Quadratic equation for line-ellipsoid intersection

x, y, z, rx, ry, rz, a, b, c, d, x0, y0, z0 = symbols('x y z rx ry rz a b c d x0 y0 z0')
init_printing(use_unicode=True)

# ((x + d * rx - x0)/a)**2 + ((y + d * ry - y0)/b)**2 + ((z + d * rz - z0)/c)**2 -1

expr = expand(((x + d * rx - x0)/a)**2 + ((y + d * ry - y0)/b)**2 + ((z + d * rz - z0)/c)**2 -1)
expr = collect(expr, d)
#print(expr)

expr2 = expand((x + d * rx - x0)**2 + (y + d * ry - y0)**2 - a**2)
expr2 = collect(expr2, d)
print(expr2)