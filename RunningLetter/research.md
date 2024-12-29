# Basic knowledge about scopes of variables

## automatic

Variables are created on the stack and fisiable in block they are being created in. If initialization hasn't been provided, is being inited with garbage. Basic Example
```C
#include <stdio.h>

void foo(void)
{
    int var; // Have no idea what's inside
    var++;
    // n++; can't access. Variable is out of scope
    printf("%d", var);
}

int main(void)
{
    int n = 0;
    n++;
    // var++; can't access. Variable is out of scope
    return 0;
}
```

## global

Global vars are accessable by all scopes. Are created in data segment. Value in inited with zero if programmer hasn't done so. Local variable with same name replaces global vars.

Example:
```C
#include <stdio.h>

int n; // initied with 0

void foo(void)
{
    int n = 1; // local variable replaces global
    n++;
    printf("%d", n); // 2
}

int main(void)
{
    n++; // global var
    printf("%d", n); // 1
}
```

## static vars

static vars are only accessable by function it's created in by created only ones. Inited with zero if init hasn't been provided. Stores in datasegment.

Example:
```C
#include <stdio.h>

void foo(void)
{
    static int n = 10;
    n++;
    printf("%d", n);
}

int main(void)
{
    foo(); // 11
    // n++; can't access
    foo(); // 12
}
```
GeekForGeeks about **global static variables**:
> A **global static variable** in C++ is a static variable declared outside of any class or function. Unlike regular global variables, a global static variable has internal linkage, meaning it is accessible only within the file where it is defined. This ensures that its scope is limited to the current translation unit, preventing conflicts with variables in other files that may have the same name.

global static var example:
```C
#include <iostream>
using namespace std;

// Global static variable
static int count = 0;

void increment() {
    count++;
    cout << count << " ";
}

int main() {
    increment(); // 1
    increment(); // 2
    return 0;
}
```

## resource 

1. [metanit.com/области видимости переменных](https://metanit.com/c/tutorial/4.5.php)

2. [www.geekforgeeks.org/memory-layout-of-c-program/](https://www.geeksforgeeks.org/memory-layout-of-c-program/)

3. [geekforgeeks.org/global-static-var](https://www.geeksforgeeks.org/static-keyword-cpp/#global-static-variable)


# Static functions
Unlike global functions in C, access to static functions is restricted to the file where they are declared. Therefore, when we want to restrict access to functions, we make them static. Another reason for making functions static can be the reuse of the same function name in other files.

For example, if we store the following program in one file file1.c
```C
/* Inside file1.c */
static void fun1(void) {
    puts("fun1 called"); 
}
```

And store the following program in another file file2.c
```C
/* Inside file2.c  */ 
int main(void)
{
    fun1(); 
    getchar();
    return 0;  
}
```

Now, if we compile the above code with the command “gcc file2.c file1.c”, we get the error “undefined reference to `fun1’”. This is because fun1() is declared static in file1.c and cannot be used in file2.c.

## resources
1. [geekforgeeks.org/static functions](https://www.geeksforgeeks.org/what-are-static-functions-in-c/)


# extern keyword
## resources
1. [geekforgeeks/understanding-extern](https://www.geeksforgeeks.org/understanding-extern-keyword-in-c/)
2. https://jameshfisher.com/2017/08/28/c-extern-function/