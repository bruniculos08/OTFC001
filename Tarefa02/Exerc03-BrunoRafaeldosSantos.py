from z3 import *

man, woman, child = Ints("man woman child")

s = Solver()
s.add((3.0 * ToReal(man)) + (2.0 * ToReal(woman)) + (0.5 * ToReal(child)) == 100.0)
s.add(woman == 5 * man)

s.add(man >= 0)
s.add(woman >= 0)
s.add(child >= 0)

number_of_solutions = 0

while(s.check() == sat):
    m = s.model()
    s.add(Not(And([(x() == m[x]) for x in m])))
    number_of_solutions += 1
print("number of solutions = ", number_of_solutions)
