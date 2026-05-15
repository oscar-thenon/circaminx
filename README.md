_Circaminx - game designed by Oscar & Arthur Thenon._

![Alt text](/rsc/screenshots/shuffled.png?raw=true "Shuffled Circaminx")

![Alt text](/rsc/screenshots/solved.png?raw=true "Shuffled Circaminx")

---


# Compilation & execution

You need to install C++ and the SFML library, then compile the game with the following command on Debian systems:

```bash
sudo apt-get install build-essential gcc libsfml-dev
make
```

Execution (once the game is launched, press `[Esc]` to quit):

```bash
./circaminx.out
```

Requires a `C++17`-compatible compiler.

_Tested with `g++ 13.3.0 ` and `SFML 2.6.1`_.


# Goal

The Circaminx is a set of two circles, each with 6 symbols, two of which are shared. The initial configuration is as follows (displayed when launching the game):

```
  1    |1
2     ^    |2
3     v    |3
  4    |4
```
   

_N.B.: the bar before a number means it is displayed upside down in the game._


The goal is to shuffle the puzzle by pressing `[*]`, then rotate the circles to return to the initial configuration: the Circaminx is then solved.


# Moves

A move is a rotation of one of the two circles. Only one move can be performed at a time. When moving, all symbols of the chosen circle rotate in the same direction and by the same angle.

Here are the 4 basic moves:


* `[S]`: rotate the left circle one step counterclockwise,
* `[F]`: rotate the left circle one step clockwise,
* `[J]`: rotate the right circle one step counterclockwise,
* `[L]`: rotate the right circle one step clockwise.


Other keys allow you to rotate a circle by several steps at once: see the `controls` section.


# Values

Three values can be displayed during the game.


## 1. Number of moves

At the bottom right, the number of moves you have made since the last shuffle (`[*]`) or reset (`[0]`) is displayed. It turns green when the Circaminx is solved.


## 2. Timer

At the top left, the elapsed time between two presses of `[Space]` is displayed in the format `MM:SS.CC` (hundredths). This allows you to time the duration of a solve.


## 3. Score

The score is displayed at the bottom left when the timer stops. It is an indicator of the efficiency and speed of a solve. The score is calculated from the time (in seconds) and the number of moves. The lower the time and number of moves, the higher the score.

If the attempt status is `DNF` (see next section), the score is forced to `0`.

Here are some examples:

* 1:45.00 in 60 moves: score 10 ~ beginner*
* 25.00   in 40 moves: score 50 ~ regular
* 10.00   in 33 moves: score 80 ~ intermediate
* 8.00    in 20 moves: score 90 ~ skilled
* 4.00    in 20 moves: score 95  ~ mastery

The score is calculated as $100-\tan^{-1}(TM/1000)\cdot(200/\pi)$ where $T$ is the time in seconds and $M$ the number of moves.

_*proposed skill levels._


## 4. Solve history

### How it works

Each time the timer is stopped (`[Space]`), a new line is added to an internal history in the form:

`[time, status, moves, score, avg, stdev]`

with:

* `time`: time in seconds rounded to the hundredth. If `status = +2`, 2 seconds are added.
* `status`:
  * `DNF`: not solved and not solvable in 1 move,
  * `ok`: solved,
  * `+2`: not solved but solvable in 1 move (penalty of +2s).
* `moves`: number of moves.
* `score`: calculated score (or `0` if `DNF`).
* `avg` and `stdev`: average and standard deviation calculated only on times whose status is not `DNF`.

If no usable time exists yet (no `ok`/`+2` status), then `avg` and `stdev` are considered not computable.

### Console display of times

When the timer stops, the console first displays the header:

`time status moves score avg stdev`

then the last recorded line, for example:

`> 12.34 ok 41 65.20 18.02 4.31`

If `avg` and `stdev` are not computable, they are displayed as `nan`.

### Exporting times

The times export command `[T]` writes (overwriting) the file `./export/times.csv`.

Content:

1. First fixed line: `time, status, moves, score, avg, stdev`
2. One CSV line per element of the `times` history

Export format rules:

* `status` is exported as `DNF`, `ok` or `+2`
* `avg` and `stdev` are exported as `nan` if not computable


# Game tips

We invite you to read the file `rsc/advice.txt` for practical tips on solving the Circaminx and improving your score.

Enjoy the game!


# Controls

## 1. MOVEMENT CONTROLS


* Left circle
  * `[Q]`: two steps counterclockwise,
  * `[S]`: one step counterclockwise,
  * `[D]`: half turn,
  * `[F]`: one step clockwise,
  * `[G]`: two steps clockwise.

* Right circle
  * `[H]`: two steps counterclockwise,
  * `[J]`: one step counterclockwise,
  * `[K]`: half turn,
  * `[L]`: one step clockwise,
  * `[M]`: two steps clockwise.


## 2. TECHNICAL CONTROLS

Each activation of a technical control is reported in the console, sometimes with details (e.g.: position after shuffling).

* `[Esc]` > quits the game,
* `[0]` > resets the position, timer, and move count,
* `[*]` > shuffles the position (1), resets the timer and move count, and saves the shuffled position,
* `[Del]` > resets the move count,
* `[Tab]` > hides/shows the values,
* `[Home]` > solves the Circaminx without resetting other values,
* `[C]` > shuffles only the central and bottom symbols (2),
* `[Enter]` > saves the current configuration,
* `[Z]` > displays the last saved position using the previous command (3),
* `[E]` > exports the current configuration to the file `./export/position.txt` (4),
* `[I]` > imports the current configuration from the file `./export/position.txt`,
* `[Space]` > starts/stops the timer. No value is displayed while the timer is running to avoid disturbing the player,
* `[T]` > exports the times history to `./export/times.csv`.



**(1)** The shuffling algorithm is designed so that it is not possible to solve the shuffled position in less than two moves (for information, there is about 1 chance in 100,000 that the shuffled position can be solved in only two moves).

**(2)** For training to solve the last step.

**(3)** If you save a position with `[Enter]` and then shuffle, the saved position is overwritten by the shuffled one.

**(4)** The export format consists of a sequence of 10 digits from 0 to 9 inclusive.
* `0` corresponds to symbol `1`,
* `1` to symbol `2`,
* `2` to symbol `3`,
* `3` to symbol `4`,
* `4` to symbol `v`,
* `5` to symbol `^`,
* `6` to symbol `1` upside down,
* `7` to symbol `2` upside down,
* `8` to symbol `3` upside down,
* `9` to symbol `4` upside down.

  Finally, to understand the positional order of the export format, note that the export
  of the solved configuration of the Circaminx is simply `0123456789`.
