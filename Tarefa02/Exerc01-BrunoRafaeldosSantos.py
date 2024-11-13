from z3 import *

# collection = [-1, 6, 8, 9, 10, -100, 78, 0, 1]
# collection = [1, 1, 1, 1]
# collection = []
collection = [0, 0]

a, b, c = Ints('a b c')

s = Optimize()
s.add(Or(And(0 <= a, a < len(collection)), And(a == -1, b == -1, c == -1)))
s.add(Or(And(0 <= b, b < len(collection)), And(a == -1, b == -1, c == -1)))
s.add(Or(And(0 <= c, c < len(collection)), And(a == -1, b == -1, c == -1)))

f = Function('f', IntSort(), IntSort())

s.add(f(-1) == 0)
for index, value in enumerate(collection):
    s.add(f(index) == value)
s.add(f(a) + f(b) + f(c) == 0)
s.add(Or(a != b, And(a == -1, b == -1, c == -1)))
s.add(Or(a != c, And(a == -1, b == -1, c == -1)))
s.add(Or(b != c, And(a == -1, b == -1, c == -1)))
s.maximize(a + b + c)

print(s.check())
if(s.check() == sat):
    print(s.model())