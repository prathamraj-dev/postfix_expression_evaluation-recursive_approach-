# postfix_expression_evaluation-recursive_approach-

A recursive evaluator for postfix (Reverse Polish Notation) expressions, written in C, with an interactive browser visualizer that shows the recursion tree and call stack step by step.

Instead of using an explicit stack, the program reads the expression **from right to left** and lets the **call stack** do the work: each operator recursively evaluates its right operand first, then its left operand, then applies itself to the two results.

## Contents

| File | Description |
|------|-------------|
| `activity1.c` | C implementation with a trace of every recursive call |
| `index.html` | Single-file interactive visualizer (no dependencies, no build step) |

## How it works

For a postfix expression stored as an array of tokens, `evaluate()` consumes tokens starting at the last index:

1. **Base case:** if the token is a number, return its value.
2. **Recursive case:** if the token is an operator, call `evaluate()` for the **right operand (b)**, then again for the **left operand (a)**, and return `a op b`.

The right operand is solved first because, scanning postfix right to left, the token immediately before an operator belongs to its right operand.

```c
double evaluate(char *tokens[], int *pos, int depth);
```

- `tokens`: the array of tokens
- `pos`: pointer to the current index, shared across calls and decremented as tokens are consumed
- `depth`: recursion depth, used only to indent the trace output

### Error handling

- Missing operand (tokens run out early) → `Invalid postfix expression`
- Leftover tokens after evaluation (missing operator) → `Invalid postfix expression`
- Division by zero → `Division by zero`

## Building and running the C program

Requires any C compiler (GCC or Clang).

```bash
gcc activity1.c -o activity1
./activity1
```

The expression is hard-coded in `main()`:

```c
char *tokens[] = {"5", "6", "2", "+", "*", "12", "4", "/", "-"};
```

This is `5 6 2 + * 12 4 / -`, i.e. `5 * (6 + 2) - 12 / 4`. To evaluate something else, edit this array.

### Sample output

```
operator '-' -> evaluate right operand
  operator '/' -> evaluate right operand
    operand 4 -> return 4
  operator '/' -> evaluate left operand
    operand 12 -> return 12
  12 / 4 = 3
operator '-' -> evaluate left operand
  operator '*' -> evaluate right operand
    operator '+' -> evaluate right operand
      operand 2 -> return 2
    operator '+' -> evaluate left operand
      operand 6 -> return 6
    6 + 2 = 8
  operator '*' -> evaluate left operand
    operand 5 -> return 5
  5 * 8 = 40
40 - 3 = 37

Result = 37
```

Indentation shows recursion depth.

## Interactive visualizer

Open `index.html` in any modern browser. Or host it with GitHub Pages (Settings → Pages → deploy from branch).

Features:

- **Token tape:** shows which token is being read, moving right to left
- **Recursion tree:** nodes light up as they are called and show their value when they return; `a` and `b` branches are colour coded
- **Call stack:** live view of each frame and its `a` / `b` slots filling in
- **Step log:** a running explanation of every step
- **Controls:** Play/Pause, Next, Back, Reset, a step slider and speed selector; the left and right arrow keys also step backward and forward
- **Presets:** the activity example, best-case and worst-case stack depth, a power example and a division-by-zero example
- **Custom input:** type your own expression (tokens separated by spaces) and press Load or Enter
- Clear error messages for invalid tokens, missing operands or operators, and division by zero
- Light and dark mode follow your system setting

Supported operators in the visualizer: `+  -  *  /  ^`

> **Note:** the C program supports `+ - * /`. The `^` (power) operator is available in the visualizer only.

## Complexity

For an expression with *n* tokens:

- **Time:** O(n), since each token is visited exactly once
- **Space:** O(d), where *d* is the maximum recursion depth. This ranges from about log n for a balanced expression to about n/2 for a worst-case right-leaning one such as `1 2 3 4 5 + + + +`

## Example expressions

| Postfix | Infix equivalent | Result |
|---------|------------------|--------|
| `3 4 +` | `3 + 4` | 7 |
| `5 6 2 + * 12 4 / -` | `5 * (6 + 2) - 12 / 4` | 37 |
| `1 2 + 3 + 4 +` | `((1 + 2) + 3) + 4` | 10 |
| `1 2 3 4 5 + + + +` | `1 + (2 + (3 + (4 + 5)))` | 15 |
| `8 0 /` | `8 / 0` | error: division by zero |

