# Tic-Tac-Toe with an Unbeatable AI

## Spec

### Build a terminal-based Tic-Tac-Toe game in C++ where a human plays against the computer.

Requirements

	1	The board is a 3x3 grid displayed in the terminal, redrawn after every move.
	2	The human plays X and moves first. The computer plays O.
	3	The human selects a move by entering a cell number (1-9) corresponding to the board position.
	4	Invalid input (non-numeric, out of range, or an occupied cell) is rejected with a message, and the human is prompted again.
	5	The computer must never lose. Against perfect play from the human, the game ends in a draw.
	6	After each game ends, announce the result (human wins, computer wins, or draw).
	7	After the result, ask whether to play again. If yes, start a fresh game; if no, exit cleanly.
	8	Keep a running tally of wins, losses, and draws across games in the same session, and display it after each game.

Constraints
	•	C++ standard library only, no external dependencies.
	•	Single file or multiple files, your choice.
	•	Runs entirely in the terminal.
