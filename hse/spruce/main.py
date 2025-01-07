a = 618527444
t = ""
while a > 0:
    t = str(a % 3) + t
    a //= 3

print(t)

print(int(t[-1:], 3), t[-1:])
t = t[:-1]

print(int(t[-1:], 3), t[-1:])
t = t[:-1]

print(int(t[-2:], 3), t[-2:])
t = t[:-2]

print(int(t[-3:], 3), t[-3:])
t = t[:-3]

print(int(t[-5:], 3), t[-5:])
t = t[:-5]

print(int(t, 3), t)
