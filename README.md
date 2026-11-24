# Arithmetic Expression Evaluator using Expression Tree (C)

A C program that reads an arithmetic expression, builds an expression tree
from it, and evaluates it.

## Features
- Operators: `+  -  *  /  ^` (power)
- Brackets `( )`
- Multi-digit and decimal numbers (e.g. `12 + 3.5`)
- Inorder, preorder and postorder traversals of the tree
- Error handling: division by zero, brackets mismatch,
  invalid character, incomplete expression

## How to run
```
gcc main.c -o expr
expr
```
Then type an expression and press Enter.

## Examples
| Input | Output |
|---|---|
| `(3+4)*2-5` | `RESULT = 9` |
| `12+3.5` | `RESULT = 15.5` |
| `2^3^2` | `RESULT = 512` |
| `8/0` | `Error: division by zero` |
| `(3+4` | `Error: brackets mismatch` |

## How it works
1. Infix to postfix: The expression is read left to right. Numbers go
   directly to the output. Operators wait in a stack, and when a new
   operator comes, operators on top with higher or equal precedence are
   moved to the output first. Brackets are handled the same way: `(` is
   pushed and `)` pops operators until `(`.
2. Postfix to tree: The postfix is read left to right. A number becomes a
   node and is pushed on a stack. For an operator, two nodes are popped
   (the first becomes the right child, the second the left child) and the
   new operator node is pushed back. The last node left is the root.
3. Evaluate: Recursion. A number node returns its value. An operator node
   first evaluates its left and right subtrees, then applies its operator
   to the two results.
4. Traversals: Inorder prints left, root, right. Preorder prints root,
   left, right. Postorder prints left, right, root.

## Limitations
- Negative numbers (e.g. `-5 + 3`) are not supported.
- Handles one expression per run.

## Concepts used
Stack, binary tree, recursion, operator precedence.
