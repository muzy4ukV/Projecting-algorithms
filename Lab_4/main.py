from Model import *
from Algo import *

num_of_nodes = int(input("Введіть кількість вершин"))

world = Model(num_of_nodes)
world.print_graph()

solution = Algo(world, num_of_nodes)
solution.run()
