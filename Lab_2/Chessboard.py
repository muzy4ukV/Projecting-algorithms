from random import randint


class Chessboard:
    """Class which represents a chessboard"""

    def __init__(self, number):
        self.board = list()
        self.__n = number
        self.__create_board()

    def __create_board(self):
        for i in range(self.__n):
            number = randint(0, self.__n - 1)
            self.board.append(number)

    def output_board(self):
        matrix = list()
        for i in range(self.__n):
            matrix.append(list())
            for j in range(self.__n):
                matrix[i].append(0)

        for i in range(len(self.board)):
            matrix[i][self.board[i]] = 1

        for i in range(self.__n):
            for j in range(self.__n):
                if matrix[j][i] == 0:
                    print("[ ]", end='')
                else:
                    print("[Q]", end='')
            print()

    def is_queen_right(self, row):
        queen_place = self.board[row]
        for i in range(len(self.board)):
            if i != row:
                diff = i - row
                if queen_place == self.board[i] or self.board[i] - diff == queen_place or self.board[i] + diff == queen_place:
                    return False
        return True

    def is_true(self):
        for i in range(self.__n):
            if not self.is_queen_right(i):
                return False
        return True

    def move_queen(self, row, num_of_cells):
        self.board[row] = (self.board[row] + num_of_cells) % self.__n

    def f1(self):
        cntr = 0
        for i in range(self.__n - 1):
            queen_row = self.board[i]
            row_cnt = True
            diagonal_1 = True
            diagonal_2 = True
            for j in range(i + 1, self.__n):
                diff = j - i
                if queen_row == self.board[j] and row_cnt:
                    cntr += 1
                    row_cnt = False
                if queen_row == self.board[j] - diff and diagonal_1:
                    cntr += 1
                    diagonal_1 = False
                if queen_row == self.board[j] + diff and diagonal_2:
                    cntr += 1
                    diagonal_2 = False
        return cntr
