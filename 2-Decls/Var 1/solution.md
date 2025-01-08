## смотрим на первую строчку
Она корректна, значит `char h`

## looking at the second line
addresses s and e shifted by h - '0'
Let's note that if pointers point to the same fragment of memory and one of it is allocated on stack, then pointer allocated on stack must point before other pointer. So e must be allocated on stack. `const char e[]` and `const char *`

## looking and the third line
length of e must be not greater then 8

## going back to the first line
we have bitwise or so to make expression correct strings must me equal.

```
lest###
>>stale
=
lestale - is the answer
```

## answer
```C
char h = '3';
const char e[] = "lestale";
const char *s = e + h - '0';
```