from z3 import *
from itertools import *

item_ecru, item_flats, item_pumps, item_sandals = Ints('item_ecru item_flats item_pumps item_sandals')
store_foot, store_heels, store_shoe, store_tootsies = Ints('store_foot store_heels store_shoe store_tootsies')

s = Solver()

s.add(And(item_ecru >= 1, item_ecru <= 4))
s.add(And(item_flats >= 1, item_flats <= 4))
s.add(And(item_pumps >= 1, item_pumps <= 4))
s.add(And(item_sandals >= 1, item_sandals <= 4))

s.add(And(store_foot >= 1, store_foot <= 4))
s.add(And(store_heels >= 1, store_heels <= 4))
s.add(And(store_shoe >= 1, store_shoe <= 4))
s.add(And(store_tootsies >= 1, store_tootsies <= 4))

s.add(item_flats == store_heels)
s.add(item_pumps + 1 != store_tootsies)
s.add(store_foot == 2)
s.add(store_shoe + 2 == item_sandals)

perm = [(list(l)) for l in permutations([item_ecru, item_flats, item_pumps, item_sandals], 2)]
s.add(And([x != y for (x,y) in perm]))
perm = [(list(l)) for l in permutations([store_foot, store_heels, store_shoe, store_tootsies], 2)]
s.add(And([x != y for (x,y) in perm]))

print(s.check())
if(s.check() == sat):
    print(s.model())