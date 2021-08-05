# ccalc

A command line calculator

## Build (TODO)

Download the source code or clone the repository, and then navigate to the directory where the source code is located.

### On Windows

You should have [winflexbison](https://github.com/lexxmark/winflexbison) installed (at least 2.5.17) and developer command prompt available (it is installed with visual studio).

Open a developer command prompt, navigate to the source code and type:
```
nmake ccalc
```

### On Linux

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
Input the command `exit` or `quit` to close the session.

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
You would obtain the following output
```
$ ccalc script.txt
2
1.5
```

## Functionalities

### Basic operations

Basic operations (+, -, *, /) are supported, as well as exponentiation (^ or **) and modulo (%).

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

#### Predefined variables

note that the value for these variables can be inaccurate at a certain level of precision due to the way floating point numbers work (simple precision floating point numbers are used).

| name | value | description |
|---|---|---|
| pi | 3.141592653 | The constant π |
| e | 2.718281746 | The constant e (or Euler number) |

#### Built-in functions

| name | description |
|---|---|
| sqrt(v) | Computes the square root of v |
| abs(v) | Computes the absolute value of v |
| cos(v) | Computes the cosine of v |
| sin(v) | Computes the sine of v |
| tan(v) | Computes the tangent of v |
| min(v<sub>1</sub>, v<sub>2</sub>, ... , v<sub>n</sub>) | Returns the smallest value among v<sub>1</sub> ... v<sub>n</sub> (takes at least 2 values) |
| max(v<sub>1</sub>, v<sub>2</sub>, ... , v<sub>n</sub>) | Returns the greatest value among v<sub>1</sub> ... v<sub>n</sub> (takes at least 2 values) |

