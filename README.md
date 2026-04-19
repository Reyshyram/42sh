# 42sh

Small recreation of tcsh.

## Usage/Examples

```
./42sh
$> pwd
/tmp
$> cd test
$> pwd
/tmp/test
```

You can also execute a file as a script:

```bash
./42sh path/to/script.sh
```

## How to compile/run

Simply use make to compile the program:

```bash
make -j
```

And then run the resulting binary, in this case, `42sh`.
By default, the Makefile uses epiclang. To compile with something else, you can simply modify the value of CC like this:
```bash
make -j CC=gcc
```

## Running Tests

To execute the unit tests, use the tests_run rule, which will compile the tests and execute the resulting binary.

```bash
make -j tests_run
```

> [!WARNING]
> This program is left as is, without any warranty. Use at your own caution.
> Moreover, this is a school project. Epitech students, beware the -42.
