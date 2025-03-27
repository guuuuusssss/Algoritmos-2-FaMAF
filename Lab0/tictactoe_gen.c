#include <stdbool.h> /* Tipo bool             */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdlib.h>  /* exit() y EXIT_FAILURE */

#include <assert.h> /* assert() */

#define CANT_TAB 5 
// en CANT_TAB habría que poner 4 para el ejercicio 3A
#define CELL_MAX (CANT_TAB * CANT_TAB - 1)

void print_sep(int length) {
  printf("\t ");
  for (int i = 0; i < length; i++)
    printf("................");
  printf("\n");
}

void print_board(char board[CANT_TAB][CANT_TAB]) {
  int cell = 0;

  print_sep(CANT_TAB);
  for (int row = 0; row < CANT_TAB; ++row) {
    for (int column = 0; column < CANT_TAB; ++column) {
      printf("\t | %d: %c ", cell, board[row][column]);
      ++cell;
    }
    printf("\t | \n");
    print_sep(CANT_TAB);
  }
}

char get_winner(char board[CANT_TAB][CANT_TAB]) {
    char winner = '-';
    bool line_complete;

    // Buscar horizontal
    for (int i = 0; i < CANT_TAB; i++) {
        line_complete = true;
        for (int j = 1; j < CANT_TAB && line_complete; j++) {
            if (board[i][0] == '-' || board[i][j] != board[i][0]) {
                line_complete = false;
            }
        }
        if (line_complete) {
            winner = board[i][0];
        }
    }

    // Buscar vertical
    for (int j = 0; j < CANT_TAB; j++) {
        line_complete = true;
        for (int i = 1; i < CANT_TAB && line_complete; i++) {
            if (board[0][j] == '-' || board[i][j] != board[0][j]) {
                line_complete = false;
            }
        }
        if (line_complete) {
            winner = board[0][j];
        }
    }

    // Buscar diagonal izq a der
    line_complete = true;
    for (int i = 1; i < CANT_TAB && line_complete; i++) {
        if (board[0][0] == '-' || board[i][i] != board[0][0]) {
            line_complete = false;
        }
    }
    if (line_complete) {
        winner = board[0][0];
    }

    // Buscar diagonal der a izq
    line_complete = true;
    for (int i = 1; i < CANT_TAB && line_complete; i++) {
        if (board[0][CANT_TAB-1] == '-' || 
            board[i][CANT_TAB-1-i] != board[0][CANT_TAB-1]) {
            line_complete = false;
        }
    }
    if (line_complete) {
        winner = board[0][CANT_TAB-1];
    }

    return winner;
}

bool has_free_cell(char board[CANT_TAB][CANT_TAB]) {
  bool free_cell = false;
  for (int i = 0; i < CANT_TAB; i++) {
    for (int j = 0; j < CANT_TAB; j++) {
      if (board[i][j] == '-') {
        free_cell = true;
      }
    }
  }
  return free_cell;
}

int main(void) {
  printf("TicTacToe [Completo!! :D]\n");

  char board[CANT_TAB][CANT_TAB];
  for (int i = 0; i < CANT_TAB; i++) {
    for (int j = 0; j < CANT_TAB; j++) {
      board[i][j] = '-';
    }
  }

  char turn = 'X';
  char winner = '-';
  int cell = 0;
  while (winner == '-' && has_free_cell(board)) {
    print_board(board);
    printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
           CELL_MAX);
    int scanf_result = scanf("%d", &cell);
    if (scanf_result <= 0) {
      printf("Error al leer un número desde teclado\n");
      exit(EXIT_FAILURE);
    }
    if (cell >= 0 && cell <= CELL_MAX) {
      int row = cell / CANT_TAB;
      int colum = cell % CANT_TAB;
      if (board[row][colum] == '-') {
        board[row][colum] = turn;
        turn = turn == 'X' ? 'O' : 'X';
        winner = get_winner(board);
      } else {
        printf("\nCelda ocupada!\n");
      }
    } else {
      printf("\nCelda inválida!\n");
    }
  }
  print_board(board);
  if (winner == '-') {
    printf("Empate!\n");
  } else {
    printf("Ganó %c\n", winner);
  }
  return 0;
}