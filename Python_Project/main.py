import copy
import sys
import pygame
import random
import numpy as np

from const import *

# --- PYGAME SETUP ---

pygame.init()
screen = pygame.display.set_mode((1000, 600))   # dimensiunea ferestrei de joc (latime si inaltime)
pygame.display.set_caption('TIC TAC TOE AI')

myfont = pygame.font.SysFont("Times New Roman", 30)
black = (0, 0, 0)
screen.fill(BG_COLOR)

# --- CLASSES ---

class Board:
    # initializam tabla de joc
    def __init__(self):
        self.sqrs = np.zeros((ROWS, COLS))    #salvam progresul jocului intr o matricesi asignam 0 ca start
        self.empty_squares = self.sqrs  # [squares]1
        self.assigned_squares = 0

    # verificam daca a castigat unul din playeri
    def stop_game(self, show=False):

        # vericam daca avem 3 de x/0 pe verticala/orizontala/diagonale

        for columns in range(COLS):
            if self.sqrs[0][columns] == self.sqrs[1][columns] == self.sqrs[2][columns] != 0:   #daca gasim 3 piese de acelasi fel
                if show:
                    color_line = color_X if self.sqrs[0][columns] == 2 else color_0     # formula pentru aflarea pct de start al liniei
                    initial_p = (columns * square_position + square_position // 2, 20)  # final
                    final_p = (columns * square_position + square_position // 2, HEIGHT - 20)
                    if final_p==10:
                        print("---test---")
                    pygame.draw.line(screen, color_line, initial_p, final_p, width_win_line)  #desenam o linie pt a marca win
                return self.sqrs[0][columns]


        for row in range(ROWS):
            if self.sqrs[row][0] == self.sqrs[row][1] == self.sqrs[row][2] != 0:
                if show:
                    color_line = color_X if self.sqrs[row][0] == 2 else color_0
                    initial_p = (20, row * square_position + square_position // 2)
                    final_p = (WIDTH - 20, row * square_position + square_position // 2)
                    if final_p==10:
                        print("---test---")
                    pygame.draw.line(screen, color_line, initial_p, final_p, width_win_line)
                return self.sqrs[row][0]


        if self.sqrs[0][0] == self.sqrs[1][1] == self.sqrs[2][2] != 0:
            if show:
                color_line = color_X if self.sqrs[1][1] == 2 else color_0
                initial_p = (20, 20)
                final_p = (WIDTH - 20, HEIGHT - 20)
                if final_p == 10:
                    print("---test---")
                pygame.draw.line(screen, color_line, initial_p, final_p, width_X)
            return self.sqrs[1][1]


        if self.sqrs[2][0] == self.sqrs[1][1] == self.sqrs[0][2] != 0:
            if show:
                color_line = color_X if self.sqrs[1][1] == 2 else color_0
                initial_p = (20, HEIGHT - 20)
                final_p = (WIDTH - 20, 20)
                if final_p == 10:
                    print("---test---")
                pygame.draw.line(screen, color_line, initial_p, final_p, width_X)
            return self.sqrs[1][1]
        return 0

    # asignam coloanei si liniei playerul dupa apasare
    def mark_sqr(self, row, col, player):
        self.sqrs[row][col] = player
        self.assigned_squares += 1

    def get_empty_sqrs(self):
        empty_sqrs = []
        for row in range(ROWS):
            for col in range(COLS):
                if self.empty_sqr(row, col):
                    empty_sqrs.append((row, col))

        return empty_sqrs

    def empty_sqr(self, row, col):
        if row < 3 and col < 3:
            return self.sqrs[row][col] == 0
    def isfilled(self):
        return self.assigned_squares == 9

    def isunfilled(self):
        return self.assigned_squares == 0


class AI_Decision:

    def __init__(self, lvl=1, person=2):
        self.lvl = lvl
        self.player = person

     # AI va alege urmatoarea mutare randmo

    def rnd(self, board):
        empty_sqrs = board.get_empty_sqrs()
        idx = random.randrange(0, len(empty_sqrs))

        return empty_sqrs[idx]  # (row, col)

    # AI va alege uramtoare mutare cu ajutorul algoritmului AI

    def mini_max(self, board, maximizing):


        case = board.stop_game()

        # player 1 wins
        if case == 1:
            return 1, None  # eval, move

        # player 2 wins
        if case == 2:
            return -1, None

        # draw
        elif board.isfilled():
            return 0, None

        if maximizing:
            max_eval = -100
            best_move = None
            empty_sqrs = board.get_empty_sqrs()

            for (row, col) in empty_sqrs:
                temp_board = copy.deepcopy(board)
                temp_board.mark_sqr(row, col, 1)
                eval = self.mini_max(temp_board, False)[0]
                if eval > max_eval:
                    max_eval = eval
                    best_move = (row, col)

            return max_eval, best_move

        elif not maximizing:
            min_eval = 100
            best_move = None
            empty_sqrs = board.get_empty_sqrs()

            for (row, col) in empty_sqrs:
                temp_board = copy.deepcopy(board)
                temp_board.mark_sqr(row, col, self.player)
                eval = self.mini_max(temp_board, True)[0]
                if eval < min_eval:
                    min_eval = eval
                    best_move = (row, col)

            return min_eval, best_move

    # Selectam modul de joc si modul o data random o data minmax

    def ai_lvl_difficulty(self, main_board, random):
        if self.lvl == 0:
            # random choice
            eval = 'random'
            move = self.rnd(main_board)
        elif self.lvl == 1:
            # minimax algo choice
            eval, move = self.mini_max(main_board, False)
        elif self.lvl == 2:
            # min max and random algo ~ medium dificulty
            if random % 2 == 0:
                eval = 'random'
                move = self.rnd(main_board)
            else:
                eval, move = self.mini_max(main_board, False)
            print(self.player)
        print(move, eval)

        return move  # row, col


class Game:

    def __init__(self):
        self.board = Board()
        self.ai = AI_Decision()
        self.player = 1  # 1-X  #2-0
        self.gamemode = 'ai'  # pvp or ai
        self.running = True
        self.show_lines()

    # --- DRAW METHODS ---

    # desenam liniile orizontale si verticale pentru joc vizual
    def show_lines(self):

        screen.fill(BG_COLOR)

        pygame.draw.line(screen, color_win_line, (square_position, 0), (square_position, HEIGHT), width_win_line)
        pygame.draw.line(screen, color_win_line, (WIDTH - square_position, 0), (WIDTH - square_position, HEIGHT), width_win_line)

        pygame.draw.line(screen, color_win_line, (0, square_position), (WIDTH, square_position), width_win_line)
        pygame.draw.line(screen, color_win_line, (0, HEIGHT - square_position), (WIDTH, HEIGHT - square_position), width_win_line)

        # desenam piesele de joc
    def draw_piece(self, row, col):
        if self.player == 1:
            # desenam X
            # linia diagonalei principale
            desc = (col * square_position + OFFSET, row * square_position + OFFSET)
            final_desc = (col * square_position + square_position - OFFSET, row * square_position + square_position - OFFSET)
            pygame.draw.line(screen, color_0, desc, final_desc, width_X)
            #lini diagonalei secundare
            asc = (col * square_position + OFFSET, row * square_position + square_position - OFFSET)
            final_asc = (col * square_position + square_position - OFFSET, row * square_position + OFFSET)
            pygame.draw.line(screen, color_0, asc, final_asc, width_X)

        elif self.player == 2:
            # desenam 0
            center = (col * square_position + square_position // 2, row * square_position + square_position // 2)
            pygame.draw.circle(screen, color_X, center, RADIUS, width_0)

    # --- OTHER METHODS ---

    def next_move(self, row, col):
        self.board.mark_sqr(row, col, self.player)
        self.draw_piece(row, col)
        self.next_player()

    def next_player(self):
        self.player = self.player % 2 + 1

    def change_gamemodeAI(self):
        self.gamemode = 'ai'  # if self.gamemode == 'pvp' else 'pvp'

    def change_gamemodeAI(self):
        self.gamemode = 'pvp'  # if self.gamemode == 'pvp' else 'pvp'

    def isover(self):
        return self.board.stop_game(show=True) != 0 or self.board.isfilled()

    def reset(self):
        self.__init__()

def button(screen, position, text):
    font = pygame.font.SysFont("Arial", 50)
    text_render = font.render(text, 1, (255, 0, 0))
    x, y, w, h = text_render.get_rect()
    x, y = position
    pygame.draw.line(screen, (150, 150, 150), (x, y), (x + w, y), 5)
    pygame.draw.line(screen, (150, 150, 150), (x, y - 2), (x, y + h), 5)
    pygame.draw.line(screen, (50, 50, 50), (x, y + h), (x + w, y + h), 5)
    pygame.draw.line(screen, (50, 50, 50), (x + w, y + h), [x + w, y], 5)
    pygame.draw.rect(screen, (100, 100, 100), (x, y, w, h))
    return screen.blit(text_render, (x, y))


def main():
    # --- OBJECTS ---

    game = Game()
    board = game.board
    ai = game.ai

    # --- MAINLOOP ---

    computer_score = 0
    player1_score = 0
    player2_score = 0
    random = 0
    previous_rect = None

    while True:
        b1 = button(screen, (920, 5), "Quit")
        b2 = button(screen, (601, 5), "Reset")
        b3 = button(screen, (750, 10), "pvp")
        b4 = button(screen, (750, 90), "pvc")
        b5 = button(screen, (600, 140), "Easy")
        b6 = button(screen, (600, 220), "Medium")
        b7 = button(screen, (600, 300), "Hard")

        # pygame events
        for event in pygame.event.get():

            if event.type == pygame.MOUSEBUTTONDOWN:
                if b1.collidepoint(pygame.mouse.get_pos()):
                    pygame.quit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                if b2.collidepoint(pygame.mouse.get_pos()):
                    game.reset()
                    board = game.board
                    ai = game.ai
            if event.type == pygame.MOUSEBUTTONDOWN:
                if b4.collidepoint(pygame.mouse.get_pos()):
                    game.reset()
                    board = game.board
                    ai = game.ai
                    game.gamemode = 'ai'
                    print("game mode changed PvC")

            if event.type == pygame.MOUSEBUTTONDOWN:
                if b3.collidepoint(pygame.mouse.get_pos()):
                    game.reset()
                    board = game.board
                    ai = game.ai
                    game.gamemode = 'pvp'
                    print("game mode changed to PvP")

            if event.type == pygame.MOUSEBUTTONDOWN:
                if b5.collidepoint(pygame.mouse.get_pos()):
                    ai.lvl = 0
                if b6.collidepoint(pygame.mouse.get_pos()):
                    ai.lvl = 2
                if b7.collidepoint(pygame.mouse.get_pos()):
                    ai.lvl = 1
            # quit event
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()



            # click event
            if event.type == pygame.MOUSEBUTTONDOWN:
                pos = event.pos
                row = pos[1] // square_position
                col = pos[0] // square_position

                # mark sqr
                if board.empty_sqr(row, col) and game.running:
                    game.next_move(row, col)

                    if game.isover():
                        if board.stop_game() == 1:
                            player1_score += 1
                        elif board.stop_game() == 2:
                            player2_score += 1
                        game.running = False
        pygame.display.update()

        # AI initial call

        if game.gamemode == 'ai' and game.player == ai.player and game.running:
            if ai.lvl == 2:
                random = random % 2 + 1

                # update the screen
            pygame.display.update()

            # eval
            row, col = ai.ai_lvl_difficulty(board, random=random)
            game.next_move(row, col)

            if game.isover():
                if board.stop_game() == 1:
                    player1_score += 1
                elif board.stop_game() == 2:
                    player2_score += 1
                game.running = False

        #score_display = myfont.render(f"X {player1_score} / O {player2_score}", 2, black)
        # print(player1_score, player2_score, computer_score)
        #screen.blit(score_display, (700, 350))
        if previous_rect:
            screen.fill((255, 255, 255), rect=previous_rect)
        score_display = myfont.render(f"X {player1_score} / O {player2_score}", 2, black)
        previous_rect = score_display.get_rect(topleft=(750, 350))
        screen.blit(score_display, (750, 350))

main()