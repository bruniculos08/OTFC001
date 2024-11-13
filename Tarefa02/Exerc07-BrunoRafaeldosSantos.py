from z3 import *
from itertools import *

# First names:
keith, libby, margo, nora, otto = Ints('keith libby margo nora otto')
names = [keith, libby, margo, nora, otto]
# Surnames:
fell, gant, hall, ivey, jule = Ints('fell gant hall ivey jule')
surnames = [fell, gant, hall, ivey, jule]

s = Solver()

s.add(And([x >= 2 for x in names]))
s.add(And([x <= 6 for x in names]))
s.add(And([x >= 2 for x in surnames]))
s.add(And([x <= 6 for x in surnames]))

perm = permutations(names, 2)
s.add(And([(x != y) for x,y in perm]))
perm = permutations(surnames, 2)
s.add(And([(x != y) for x,y in perm]))

for x in names:
    s.add(Or([x == y for y in surnames]))

s.add(libby == jule)
s.add(keith == 1 + ivey)
s.add(ivey == 1 + nora)
s.add(fell == 3 + margo)
s.add(otto == 2 * hall)

print(s.check())
if(s.check() == sat):
    print(s.model())