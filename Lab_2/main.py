from Chessboard import *
from Algo import *
from Node import *

N = 8

initial_board = Chessboard(N)
#initial_board.board = [7, 7, 0, 6, 3, 7, 4, 5]
root = Node(initial_board, -1, 0)

print("Ось так виглядає початковий стан:")
print(initial_board.board)
initial_board.output_board()

flag = int(input("Оберіть алгоритм:\n1 - Iterative Deep Search\n2 - Recursive Best First Search\n"))

if flag == 1:
    algo = Algo(root, N)
    algo.IDS()
    algo.output_result()
elif flag == 2:
    algo = Algo(root, N)
    algo.RBFS(root, float('inf'))
    algo.output_result()
else:
    print("От халепа, щось пішло не так")

