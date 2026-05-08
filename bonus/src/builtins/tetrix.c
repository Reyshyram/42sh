/*
** EPITECH PROJECT, 2026
** tetrix.c
** File description:
** tetrix file
*/

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tetrix.h"
#include "builtins.h"
#include "my/misc.h"
#include "shell.h"

static void init_piece(piece_t *p, int type)
{
    p->type = type;
    p->rot = 0;
    p->x = BOARD_W / 2 - 2;
    p->y = 0;
}

static void random_piece(piece_t *p)
{
    init_piece(p, rand() % 7);
}

static int valid(const piece_t *p) 
{
    const int (*s)[4] = SHAPES[p->type][p->rot];

    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            if (s[r][c]) {
                int bx = p->x + c;
                int by = p->y + r;
                if (bx < 0 || bx >= BOARD_W) return 0;
                if (by >= BOARD_H) return 0;
                if (by >= 0 && board[by][bx]) return 0;
            }
    return 1;
}

static void lock_piece(void)
{
    const int (*s)[4] = SHAPES[cur.type][cur.rot];
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            if (s[r][c]) {
                int bx = cur.x + c;
                int by = cur.y + r;
                if (by >= 0 && by < BOARD_H && bx >= 0 && bx < BOARD_W)
                    board[by][bx] = cur.type + 1;
            }
}

static int clear_lines(void)
{
    int count = 0;
    for (int r = BOARD_H - 1; r >= 0; r--) {
        int full = 1;
        for (int c = 0; c < BOARD_W; c++)
            if (!board[r][c]) {
                full = 0;
                break;
            }
        if (full) {
            for (int rr = r; rr > 0; rr--)
                memcpy(board[rr], board[rr-1], sizeof(board[0]));
            memset(board[0], 0, sizeof(board[0]));
            count++;
            r++;
        }
    }
    return count;
}

static void spawn_next(void)
{
    cur = nxt;
    random_piece(&nxt);
    if (!valid(&cur))
        game_over = 1;
}

void clear_window(WINDOW *win)
{
    for (int i = 1; i < BOARD_W - 1; i++){
        for (int j = 1; j < BOARD_H - 1; j++){
            mvwprintw(win, i, j, " ");
        }
    }
}

static void draw_cell(WINDOW *w, int row, int col, int color_pair)
{
    if (color_pair) {
        wattron(w, COLOR_PAIR(color_pair) | A_BOLD);
        mvwprintw(w, row, col * CELL, "[]");
        wattroff(w, COLOR_PAIR(color_pair) | A_BOLD);
    } else {
        mvwprintw(w, row, col * CELL, "  ");
    }
}

static void draw_board_win(void)
{
    wattron(wboard, COLOR_PAIR(CP_BORDER));
    box(wboard, 0, 0);
    wattroff(wboard, COLOR_PAIR(CP_BORDER));
    for (int r = 0; r < BOARD_H; r++)
        for (int c = 0; c < BOARD_W; c++)
            draw_cell(wboard, r + 1, c + 1, board[r][c]);
    piece_t ghost = cur;
    while (valid(&ghost))
        ghost.y++;
    ghost.y--;
    if (ghost.y != cur.y) {
        const int (*gs)[4] = SHAPES[ghost.type][ghost.rot];
        for (int r = 0; r < 4; r++)
            for (int c = 0; c < 4; c++)
                if (gs[r][c]) {
                    int bx = ghost.x + c;
                    int by = ghost.y + r;
                    if (by >= 0 && by < BOARD_H && bx >= 0 && bx < BOARD_W
                        && !board[by][bx]) {
                        wattron(wboard, COLOR_PAIR(cur.type + 1) | A_DIM);
                        mvwprintw(wboard, by + 1, (bx + 1) * CELL, "..");
                        wattroff(wboard, COLOR_PAIR(cur.type + 1) | A_DIM);
                    }
                }
    }
    const int (*s)[4] = SHAPES[cur.type][cur.rot];
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            if (s[r][c]) {
                int bx = cur.x + c;
                int by = cur.y + r;
                if (by >= 0 && by < BOARD_H && bx >= 0 && bx < BOARD_W)
                    draw_cell(wboard, by + 1, bx + 1, cur.type + 1);
            }
    wrefresh(wboard);
}

static void draw_info(void)
{
    werase(winfo);
    wattron(winfo, COLOR_PAIR(CP_BORDER));
    box(winfo, 0, 0);
    wattroff(winfo, COLOR_PAIR(CP_BORDER));
    mvwprintw(winfo, 1, 2, "TETRIS");
    mvwprintw(winfo, 3, 2, "Score:");
    mvwprintw(winfo, 4, 2, "%d", score);
    mvwprintw(winfo, 6, 2, "Lines:");
    mvwprintw(winfo, 7, 2, "%d", lines_cleared);
    mvwprintw(winfo, 9, 2, "Level:");
    mvwprintw(winfo, 10, 2, "%d", level);
    mvwprintw(winfo, 12, 2, "Next:");
    const int (*ns)[4] = SHAPES[nxt.type][nxt.rot];
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            if (ns[r][c]) {
                wattron(winfo, COLOR_PAIR(nxt.type + 1) | A_BOLD);
                mvwprintw(winfo, 13 + r, 2 + c * 2, "[]");
                wattroff(winfo, COLOR_PAIR(nxt.type + 1) | A_BOLD);
            }
    mvwprintw(winfo, 18, 2, "Controls:");
    mvwprintw(winfo, 19, 2, "<- ->  move");
    mvwprintw(winfo, 20, 2, "Up     rotate");
    mvwprintw(winfo, 21, 2, "Down   soft drop");
    mvwprintw(winfo, 22, 2, "Space  hard drop");
    mvwprintw(winfo, 23, 2, "P      pause");
    mvwprintw(winfo, 24, 2, "Q      quit");
    wrefresh(winfo);
}

static void rotate_cw(piece_t *p)
{
    piece_t tmp = *p;
    tmp.rot = (tmp.rot + 1) % 4;
    if (valid(&tmp)) {
        *p = tmp;
        return;
    }
    int kicks[] = {-1, 1, -2, 2};
    for (int i = 0; i < 4; i++) {
        tmp.x = p->x + kicks[i];
        if (valid(&tmp)) {
            *p = tmp;
            return;
        }
    }
}

static void hard_drop(void)
{
    int dropped = 0;

    while (1) {
        piece_t tmp = cur;
        tmp.y++;
        if (!valid(&tmp))
            break;
        cur.y++;
        dropped++;
    }
    score += dropped * 2;
    lock_piece();
    int n = clear_lines();
    lines_cleared += n;
    int pts[] = {0, 100, 300, 500, 800};
    score += pts[n] * level;
    level = lines_cleared / 10 + 1;
    spawn_next();
}

static void handle_input_tetrix(int ch)
{
    piece_t tmp;
    switch (ch) {
        case KEY_LEFT:
            tmp = cur; tmp.x--;
            if (valid(&tmp)) cur = tmp;
            break;
        case KEY_RIGHT:
            tmp = cur; tmp.x++;
            if (valid(&tmp)) cur = tmp;
            break;
        case KEY_UP:
            rotate_cw(&cur);
            break;
        case KEY_DOWN:
            tmp = cur; tmp.y++;
            if (valid(&tmp)) { cur = tmp; score += 1; }
            break;
        case ' ':
            hard_drop();
            break;
        case 'p': case 'P':
            paused = !paused;
            break;
        case 'q': case 'Q':
            game_over = 1;
            break;
    }
}

static int gravity_tick(void)
{
    piece_t tmp = cur;

    tmp.y++;
    if (valid(&tmp)) {
        cur = tmp;
        return 0;
    }
    lock_piece();
    int n = clear_lines();
    lines_cleared += n;
    int pts[] = {0, 100, 300, 500, 800};
    score += pts[n] * level;
    level = lines_cleared / 10 + 1;
    spawn_next();
    return 1;
}

static void init_colors(void)
{
    start_color();
    init_pair(CP_I, COLOR_CYAN, COLOR_BLACK);
    init_pair(CP_O, COLOR_YELLOW, COLOR_BLACK);
    init_pair(CP_T, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CP_S, COLOR_GREEN, COLOR_BLACK);
    init_pair(CP_Z, COLOR_RED, COLOR_BLACK);
    init_pair(CP_J, COLOR_BLUE, COLOR_BLACK);
    init_pair(CP_L, COLOR_WHITE, COLOR_BLACK);
    init_pair(CP_BORDER, COLOR_WHITE, COLOR_BLACK);
}

static void init_windows(void)
{
    int brows = BOARD_H + 2;
    int bcols = (BOARD_W + 2) * CELL;

    wboard = newwin(brows, bcols, BOARD_OFF_Y, BOARD_OFF_X);
    winfo = newwin(brows, 26, BOARD_OFF_Y, BOARD_OFF_X + bcols + 2);
}

static void show_game_over(void)
{
    int brows = BOARD_H + 2;
    int bcols = (BOARD_W + 2) * CELL;
    WINDOW *wgo = newwin(7, 22, BOARD_OFF_Y + brows / 2 - 5, BOARD_OFF_X + (bcols - 22) / 2);

    clear_window(wboard);
    wrefresh(wboard);
    wattron(wgo, COLOR_PAIR(CP_Z) | A_BOLD);
    box(wgo, 0, 0);
    mvwprintw(wgo, 1, 5, "GAME  OVER");
    wattroff(wgo, COLOR_PAIR(CP_Z) | A_BOLD);
    mvwprintw(wgo, 3, 3, "Score : %d", score);
    mvwprintw(wgo, 4, 3, "Lines : %d", lines_cleared);
    mvwprintw(wgo, 5, 3, "Press any key...");
    wrefresh(wgo);
    timeout(-1);
    getch();
    delwin(wgo);
}

static long now_ms(void)
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
}

int game_tetrix(shell_t *shell, size_t argc, char **argv)
{
    srand(time(NULL));
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    init_colors();
    init_windows();
    memset(board, 0, sizeof(board));
    score = 0;
    lines_cleared = 0;
    level = 1;
    game_over = 0;
    paused = 0;
    random_piece(&cur);
    random_piece(&nxt);
    timeout(16);
    long last_gravity = now_ms();
    while (!game_over) {
        int ch;
        while ((ch = getch()) != ERR) {
            if (paused) {
                if (ch == 'p' || ch == 'P') paused = 0;
            } else {
                handle_input_tetrix(ch);
            }
            if (game_over) break;
        }
        if (!paused && !game_over) {
            int gravity_ms = 500 - (level - 1) * 40;
            if (gravity_ms < 60) gravity_ms = 60;

            long now = now_ms();
            if (now - last_gravity >= gravity_ms) {
                gravity_tick();
                last_gravity = now;
            }
        } else {
            last_gravity = now_ms();
        }
        draw_board_win();
        draw_info();
        if (paused) {
            clear_window(wboard);
            wattron(wboard, A_BOLD | COLOR_PAIR(CP_T));
            mvwprintw(wboard, BOARD_H / 2, 5, "[** PAUSED **]");
            wattroff(wboard, A_BOLD | COLOR_PAIR(CP_T));
        }
        wrefresh(wboard);
    }
    show_game_over();
    delwin(wboard);
    delwin(winfo);
    endwin();
    return 0;
}
