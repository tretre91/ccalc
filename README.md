# ccalc

A command line calculator

## Build

Download the source code or clone the repository, and then navigate to the directory where the source code is located.
This program depends on some boost header only libraries (multiprecision and math), make sure that you have boost libraries available on your system (they can be downloaded [here](https://www.boost.org/users/download/)).

### On Windows

You should have [winflexbison](https://github.com/lexxmark/winflexbison) installed (at least 2.5.17) and a developer command prompt available (it is installed with visual studio).

Open a developer command prompt, navigate to the source code and type:
```bash
nmake ccalc BOOST_ROOT="path\to\boost"
# for example
nmake ccalc BOOST_ROOT="C:\Program Files\boost\boost_1_76_0"
```

### On Linux

(TODO)

## Usage

Launch without any arguments to open an interactive session:
```
$ ccalc
>> 1 + 1
2
>> a = 3
>> min(1, -2, a)
-2
```
Input the command `exit` or `quit` to close the session, you can also press `ctrl` + `z` and then `enter` on Windows.

Use the `-e` or `--eval` option to evaluate a single expression:
```
$ ccalc -e "3 ** 2"
9
```

you can also evaluate an expression from a pipe:
```
$ echo "sqrt(25)" | ccalc
5
```

Provide a filename to run commands contained in this file, let's say that the file *script.txt* contains the following expressions:
```
1 + 1
a = 2.5
a - 1
```
You would obtain the following output:
```
$ ccalc script.txt
2
1.5
```

## Functionalities

### Basic operations

Basic operations (+, -, *, /) are supported, as well as exponentiation (^ or **) and modulo (%).

### Numeric values

Valid numeric values are integers and floats (both in decimal and scientific notation):

```
>> 2
2
>> 2.53
2.53
>> 3.
3
>> .5
0.5
>> 1.3e2
130
>> 1.3E2
130
```

### Variables

You can use variables to store values, use the equal sign to assign a value to a variable:
```
>> a = 2
>> a
2
>> a = 2 ^ 3
>> a
8
```

you can then retrieve its value and use it in other expressions :
```
>> a = 2
>> a * 4
8
```

Some variables already contains mathematical constants, they are listed [here](#Predefined-variables).

### Mathematical functions

Some mathematical functions are supported (see the [list](#Built-in-functions) below), they can take numbers, expressions or variables as arguments:

```
>> abs(-9)
9
>> a = sqrt(25)
>> min(a, a^2)
5
```

### Predefined variables

These constants are from boost's [mathematical constants](https://www.boost.org/doc/libs/1_76_0/libs/math/doc/html/math_toolkit/constants.html).

| name | value (6 significant digits) | description |
|---|---|---|
| pi | 3.14159 | The constant π |
| e | 2.71828 | The constant e (or Euler number) |
| degree | 0.017453 | 1 degree, expressed in radians (π / 180) |
| radian | 57.2957 | 1 radian, expressed in degrees (180 / π) |

### Built-in functions

| name | description |
|---|---|
| **Basic functions** |
| abs(v) | Computes the absolute value of v |
| sqrt(v) | Computes the square root of v |
| min(v<sub>1</sub>, v<sub>2</sub>, ... , v<sub>n</sub>) | Returns the smallest value among v<sub>1</sub> ... v<sub>n</sub> (takes at least 2 values) |
| max(v<sub>1</sub>, v<sub>2</sub>, ... , v<sub>n</sub>) | Returns the greatest value among v<sub>1</sub> ... v<sub>n</sub> (takes at least 2 values) |
| **Trigonometric functions** |
| cos(v) | Computes the cosine of v |
| sin(v) | Computes the sine of v |
| tan(v) | Computes the tangent of v |
| **System functions** | **Note:** These functions do not return a value and therefore cannot be used in expressions |
| \_setPrecision(v) | Sets the number of significant digits used in output, must be a positive value or 0 for the maximum number of digits |
