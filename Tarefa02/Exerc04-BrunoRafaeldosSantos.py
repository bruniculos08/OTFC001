from z3 import *
from itertools import *

husb_age, age = Ints('husb_age age')

s = Solver()
f1 = lambda x : x + 2
f2 = lambda x : x / 8.0
f3 = lambda x : x - 3
f4 = lambda x : x * 7

perm_idx_husb, perm_idx = Ints('perm_idx_husb, perm_idx')

f = lambda t,x : t[3](t[2](t[1](t[0](x))))
functions = [f1, f2, f3, f4]
perm = [(list(l)) for l in permutations(functions)]

s.add(Or([And(f(order, age) == husb_age, perm_idx_husb == index) for index, order in enumerate(perm)]))
s.add(Or([And(f(order, husb_age) == age, perm_idx == index) for index, order in enumerate(perm)]))
s.add(perm_idx != perm_idx_husb)
s.add(And(husb_age >= 0, age >= 0))

print(s.check())
if(s.check() == sat):
    print(s.model())