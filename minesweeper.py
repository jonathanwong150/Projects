# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import random
from tkinter import Tk, Canvas, CENTER

dispBoard = []
board = []
flagged = []
gameOver = False
clicked = 0
canvas = None
n = 0


def format_row(row):
    return '|' + '|'.join('{0:^3s}'.format(str(x)) for x in row) + '|'


def print_board(board):
    header = ['+']
    for k in range(len(board)):
        header.append(k)
    print(format_row(header))
    for i in range(len(board)):
        pRow = [i] + board[i]
        for k in range(1, len(pRow)):
            if pRow[k] == None:
                pRow[k] = '?'
        print(format_row(pRow))


def find_space_vals():
    for i in range(len(board)):
        for k in range(len(board[0])):
            if board[i][k] == None:
                board[i][k] = get_mine_count(i, k)


def get_mine_count(i, k):
    mCount = 0
    for a in range(i - 1, i + 2):
        for b in range(k - 1, k + 2):
            if not (a == i and b == k) and 0 <= a < len(board) and 0 <= b < len(board[0]) and board[a][b] == '*':
                mCount += 1
    return mCount


def create_board(nRows, nCols, nMines):
    # established boundary conditions -> set min and max for dimensions
    nRows = max(nRows, 10)
    nCols = max(nCols, 10)
    maxMines = nCols * nRows / 2
    nMines = min(maxMines, nMines)
    nMines = max(nMines, 10)

    # made the board
    for i in range(nRows):
        bRow = []
        bRow2 = []
        for k in range(nCols):
            bRow.append(None)
            bRow2.append(None)
        dispBoard.append(bRow2)
        board.append(bRow)

    # dropping the mines
    for i in range(nMines):
        mx = random.randint(0, nRows - 1)
        my = random.randint(0, nCols - 1)
        while board[mx][my] == '*':
            mx = random.randint(0, nRows - 1)
            my = random.randint(0, nCols - 1)
        board[mx][my] = '*'

    find_space_vals()


def show_space(x, y):
    if dispBoard[x][y] != None:
        return
    dispBoard[x][y] = board[x][y]
    if board[x][y] == 0:
        for a in range(x - 1, x + 2):
            for b in range(y - 1, y + 2):
                if not (a == x and b == y) and 0 <= a < len(board) and 0 <= b < len(board[0]):
                    show_space(a, b)
    global gameOver
    global clicked
    if (board[x][y] == '*'):
        gameOver = True
    clicked += 1


def click_space(event):
    global clicked
    show_space(int(event.x / 31), int(event.y / 31))
    display_board(dispBoard)
    if (gameOver): print("Game Over")
    if (len(board) * len(board[0]) - n == clicked): print("You Win")


def flag_space(event):
    flagged.append((int(event.x / 31), int(event.y / 31)))
    display_board(dispBoard)


def display_board(gboard):
    height = len(gboard) * 31
    width = len(gboard[0]) * 31
    for i in range(0, width, 31):
        for j in range(0, height, 31):
            y = int(i / 31)
            x = int(j / 31)
            canvas.create_rectangle(i, j, (i + 30), (j + 30), fill="green")
            if (gboard[y][x] == None):
                canvas.create_rectangle(i, j, (i + 30), (j + 30), fill="green")
            elif (gboard[y][x] == '*'):
                canvas.create_rectangle(i, j, (i + 30), (j + 30), fill="red")
                canvas.create_text(i + 15, j + 15, anchor=CENTER, font="Purisa", text=str(gboard[y][x]))
            else:
                canvas.create_rectangle(i, j, (i + 30), (j + 30), fill="grey")
                canvas.create_text(i + 15, j + 15, anchor=CENTER, font="Purisa", text=str(gboard[y][x]))
    for n in flagged:
        canvas.create_text(n[0] * 31 + 15, n[1] * 31 + 15, anchor=CENTER, font="Purisa", text="F")


def game():
    global clicked
    global canvas
    global n
    width = int(input("Side Length (min 10):\t"))
    height = width
    maxN = width * height / 2
    text = "How many bombs? (Min 10, Max " + str(maxN) + ")\t"
    n = int(input(text))
    input("Press enter to start")
    create_board(height, width, n)
    root = Tk()
    root.wm_title("Minesweeper")
    heightpxls = len(board) * 31
    widthpxls = len(board[0]) * 31
    canvas = Canvas(master=root, height=heightpxls, width=widthpxls)
    canvas.pack()
    display_board(dispBoard)
    # display_board(gboard, canvas)
    canvas.bind("<Button-1>", click_space)
    canvas.bind("<Button-2>", flag_space)
    root.mainloop()
    if (gameOver or (width * height - n == clicked)): return


game()
