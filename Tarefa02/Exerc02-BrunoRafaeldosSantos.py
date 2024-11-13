from z3 import *

a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p = Ints('a b c d e f g h i j k l m n o p')

s = Solver()
s.add(And(a >= 1, b >= 1, c >= 1, d >= 1, e >= 1, f >= 1, g >= 1, h >= 1, 
          i >= 1, j >= 1, k >= 1, l >= 1, m >= 1, n >= 1, o >= 1, p >= 1))
s.add(And(a <= 16, b <= 16, c <= 16, d <= 16, e <= 16, f <= 16, g <= 16, h <= 16, 
          i <= 16, j <= 16, k <= 16, l <= 16, m <= 16, n <= 16, o <= 16, p <= 16))
s.add(a + (b / c) == d) # Linha 1
s.add((e / f) + g == h) # Linha 2
s.add(i + j + k == l) # Linha 3
s.add(m - (n / o) == p) # Linha 4
s.add(a + (e * i) == m) # Coluna 1
s.add(b - (f * j) == n) # Coluna 2
s.add(c - (g / k) == o) # Coluna 3
s.add(d + (h / l) == p) # Coluna 4

print(s.check())
if(s.check() == sat):
    print(s.model())