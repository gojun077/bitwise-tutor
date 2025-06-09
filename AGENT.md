bitwise-tutor
========================

# Summary

Created on: Mon 09 Jun 2025
Last Updated: Mon 09 Jun 2025

`bitwise-tutor` is aimed at beginning students of the `C` programming
language who are learning about how integers are stored in binary
representation. `bitwise-tutor` is written in `C` and utilizes both
signed and unsigned types fixed width integer types from `<stdint.h>` such
as `uint8_t`, `int8_t` to avoid excessively large bit-size integers to
assist pedagogy.

`bitwise-tutor` asks the user for input on the following bitwise
operator questions:

- bitwise AND `&`
- bitwise OR `|`
- bitwise XOR `^`
- bitwise NOT `~` (aka *bitwise complement*, *one's complement*)
  - emphasize the difference between results from unsigned and signed ints
  - *bitwise NOT* of a positive signed int can be negative
    - test the concept of *two's complement* for storing negative binary
  - *bitwise NOT* of a small unsigned int can return  a much larger int
- bitwise left-shift `<<`
- bitwise right-shift `>>`

`bitwise-tutor` also quizzes students on conversion from decimal to
binary representation, and conversion from binary to decimal.

Because the `C` language does not provide a built-in human readable
representation of binary numbers with left-padding, `bitwise-tutor`
creates its own string representations of left-padded binary numbers.
Henceforth, `bitwise-tutor` will be referred to as `bwt` below.

# Steps

## 1. Proof of Concept (PoC) - Alpha

In the PoC stage, refer to `bitwise_operators.c` in the root of this
repo for examples of how to convert integers into character arrays in the
functions `uint_to_binary` and `int_to_binary`.

Also refer to the examples for each of the bitwise operators included in
`bitwise_operators.c` as a guide for what kinds bitwise operator scenarios
users should be presented with.

The first iteration of `bwt` is a command line program executed via

```sh
./bwt
```

`bwt` randomly generates mostly integers with signed and unsigned int types
`int8_t` and `uint8_t` but occasionally generates fixed width 16-bit
integers and rarely fixed width 32-bit integers.

For each generated integer, `bwt` poses questions about bitwise operators
and conversions between base-2 and base-10 (and vice versa) introduced in
the `# Summary` section above.

Here are sample questions related to *bitwise AND* in which the user is
given integer values in decimal to work with.

```markdown
The following questions are about signed 8-bit integers *a* and *b*.
Given `a=2` and `b=5`,

Q1: What is the binary representation of `2`?

>>> 2

Sorry, that is incorrect! Please try again

>>> 00000010

Correct!

Q2: What is the binary representation of `5`?

>>> 0000

Sorry, that is incorrect! Please try again

>>> 00000101

Correct!

Q3: What is the result of `a&b` in binary?

>>> 00000000

Correct!

Q4: What is the result of `a&b` in decimal?

>>> 0

Correct!
```

Here are sample questions for bitwise AND in which the student is first
provided by binary representations only.

```markdown
The following questions are about signed 8-bit integers *a* and *b*.
Given `a=00001010` and `b=00001000` in binary,

Q1: What is `a&b` in binary?

>>> a

Please enter digits only.

>>> 00001000

Correct!

Q2: What is `a` in decimal?

>>> 10

Correct!

Q3: What is `b` in decimal?

>>> 1

Sorry, that is incorrect! Please try again

>>> 8

Correct!
```

Similar questions will be posed for the other topics with special emphasis
about the difference between signed and unsigned ints when it comes to
*bitwise complement*, i.e. `~2` returns `-3` for signed 8-bit int, but `~2`
returns `253` for 8-bit unsigned int.


## 2. Polishing `bwt` - beta

The *beta* version of `bwt` builds upon the PoC / alpha version by adding
the following features:

- Allow user to determine settings for a quiz session
  + how many questions for `bwt` to ask
- Save terminal input/output from `bwt` session to a file
- Add time limit for each question

## 3. Stable version of `bwt`

The *stable* `1.0` version of `bwt` builds upon the beta version by
upgrading the user interface to use a TUI from `ncurses` or the newer
`notcurses`. `bwt` utilizes color and fonts to make the terminal
output more readable for binary representations. Statistics for a given
session are calculated including how many questions were correct and
the average time spent per question. A default settings file can be
generated and command line option flags can also be used to launch `bwt`
with particular settings.

Despite these improvements, `bwt` is still written in `C` following the
`c23` standard.
