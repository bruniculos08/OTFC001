from z3 import *
from itertools import *

tim, jane, mary = Ints('tim jane mary')
s = Solver()

s.add(And(tim >= 0, jane >= 0, mary >= 0))

x1 = Int('x1')  # <- Number of years from when Mary was nine times as old as Tim
s.add(10 + tim == 2 * (jane - x1))
s.add(mary - x1 == 9 * (tim - x1))

x21 = Int('x21')    # <- Number of years from now when Jane will be when Jane is one year...
                    # ... older than Tim will be at the time...
x22 = Int('x22')
s.add((mary - 8) * 2 == ((jane + x21)))
s.add((jane + x21) == (1 + (tim + x22)))
s.add((mary + x22) == 5 * (tim + 2))

x31 = Int('x31')
x32 = Int('x32')
x33 = Int('x33')
x34 = Int('x34')
x35 = Int('x35')
x36 = Int('x36')
s.add(tim - x31 == 1)
s.add((mary - x31) == 3 + (tim + x32))
s.add((jane + x32) == 3 * (mary - x33 - 6))
s.add((jane - x33) * 2 == tim + x34)
s.add(mary + x34 == 10 + mary - x35)
s.add((jane - x35) * 3 == tim + x36)
s.add((mary + x36) == 3 * (mary - jane))

print(s.check())
if(s.check() == sat):
    print(s.model())