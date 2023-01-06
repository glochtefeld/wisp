# Wisp - An interpreted Lisp-like language
*Please note: there are several other lisps that are called "wisp". This is just a learning exercise.*

Wisp is an interpreted language, taking its syntax from Common Lisp. At this point it doesn't exist, but when it does I'd like for it to have a focus on quick iteration (through hot reloading, easy REPL integration, etc.) 

Again, this is just a learning exercise/fun project. Wisp isn't short for anything.

## Examples

The mighty Hello World:
```lisp
(print "Hello, world!")
```

The classic factorial example, two ways:
```lisp
(defun fib1 (x)
    (cond ((= x 1) 1)
        (T (* x (fib1 (- x 1))))))

(defun fib2 (x)
    ;; Takes advantage of tail-call optimization.
    (defun tco (acc current)
        (cond ((= current 1) current)
            (T (tco (* acc current) (- current 1)))))
    (tco 1 x))
```

## Building & Forking
Wisp requires CMake >= 3.16. You can create build files with:
```bash
cmake -S . -B build
```
and
```bash
cmake --build build
```
substituting the directory where you would like the project to be built for `build`.

Feel free to fork this and use it for whatever you like, provided that you comply with the terms in the license agreement (see LICENSE).