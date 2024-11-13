from z3 import *
from itertools import *

x1, x2, x3, x4, x5 = Ints('x1 x2 x3 x4 x5')
bales = [x1, x2, x3, x4, x5]

weights = [80, 82, 83, 84, 85, 86, 87, 88, 90, 91]

s = Solver()
s.add(And([x >= 0 for x in bales]))

perm = permutations(bales, 2)
print(list(perm))
for w in weights:
    s.add(Or([(x + y == w) for x, y in perm]))

print(s.check())
if(s.check() == sat):
    print(s.model())