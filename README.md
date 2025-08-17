# Skibidilang Interpreter

Skibidilang Interpreter is a simple stack-based programming language implemented in C++. It supports pushing values, basic arithmetic, stack operations, input/output, and simple conditional execution.

![plot](./res/skibidiicon.png)

## Features

- Stack-based execution model
- Integer arithmetic: `+`, `-`, `*`, `/`
- Input and output: `hearmeout`, `tickle`, `yap`
- Stack operations: `dupe`, `swap`, `drop`
- Conditional execution: `eq`, `if_true ... endif`

## Instructions

- `tickle "value"` — push a string or number onto the stack  
- `yap` — print the top of the stack  
- `hearmeout` — read input from the user and push it onto the stack  
- `+` — add the top two numbers  
- `-` — subtract the top two numbers  
- `*` — multiply the top two numbers  
- `/` — divide the top two numbers  
- `dupe` — duplicate the top value on the stack  
- `swap` — swap the top two values  
- `drop` — remove the top value from the stack  
- `eq` — compare the top two values for equality  
- `if_true ... endif` — executes the instructions inside if the top of the stack is 1

 ## Note
 I was a bit lazy so i didn't add comments 15 stars and i'm going to add comments!

## Example: Calculator

```text
tickle "Arg 1:"
yap
hearmeout
tickle "Arg 2:"
yap
hearmeout
tickle "Choose operation (1:Add 2:Sub 3:Mul 4:Div):"
yap
hearmeout

dupe
tickle 1
eq
if_true
    swap
    swap
    +
endif

dupe
tickle 2
eq
if_true
    swap
    swap
    -
endif

dupe
tickle 3
eq
if_true
    swap
    swap
    *
endif

dupe
tickle 4
eq
if_true
    swap
    swap
    /
endif

tickle "Smth didn't work"
yap
drop
drop
drop
drop
