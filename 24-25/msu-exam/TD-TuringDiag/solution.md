# Решение

Подбор ответа происходил с помощью подобного алгоритма:

```python
word = "abccaaabbc"

def f(s):
    return word.find(s) != -1

def r(find, rerplace):
    global word
    word = word.replace(find, replace, 1)

while True:
    print(word)
    
    if f("aB*"): r("aB*", "B*a"); continue
    if f("#B*"): r("#B*", "B*#"); continue
    if f("cB*"): r("cB*", "B*c"); continue
    if f("B*"): r("B*", "c*"); continue

    if f("*a"): r("*a", "a*"); continue
    if f("*b"): r("*b", "B*#"); continue
    if f("*c"): r("*c", "c*"); continue
    if f("*#"): r("*#", "#*"); continue

    if f("*"): r("*", "$"); continue

    if f("a$"): r("a$", "$a"); continue
    if f("#$"): r("#$", "$b"); continue
    if f("c$"): r("c$", "$c"); continue

    if f("$"): r("$", ""); break
    r("", "*")

print(word)
```

## Ответ

```text
aB* -> B*a
#B* -> B*#
cB* -> B*c
B*  -> c*
*a  -> a*
*b  -> B*#
*c  -> c*
*   -> $
a$  -> $a
#$  -> $b
c$  -> $c
$  |-> 
    -> *
```