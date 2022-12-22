from random import randint
from Constants import *


class Model:
    '''Клас для збереження матриці відстаней та феромонів'''
    def __init__(self, number_of_nodes):
        self.distance_matrix = list()
        self.pheromone_matrix = list()
        self.__set_random(number_of_nodes)

    def __set_random(self, number_of_nodes):
        for i in range(number_of_nodes):
            self.distance_matrix.append([0 for i in range(number_of_nodes)])
            self.pheromone_matrix.append([0 for i in range(number_of_nodes)])

        for i in range(number_of_nodes):
            for j in range(i + 1, number_of_nodes):
                self.distance_matrix[i][j] = randint(MIN_DISTANCE, MAX_DISTANCE)
                self.distance_matrix[j][i] = self.distance_matrix[i][j]
                self.pheromone_matrix[i][j] = START_PHEREMONE
                self.pheromone_matrix[j][i] = START_PHEREMONE

    #жадібний алгоритм, що шукає цикл починаючи з current_node
    def greedy_search(self, current_node):
        visited_nodes = list()
        full_dist = 0
        for i in range(len(self.distance_matrix) - 1):
            next_node = self.__find_min(self.distance_matrix[current_node], visited_nodes)
            full_dist += self.distance_matrix[current_node][next_node]
            visited_nodes.append(current_node)
            current_node = next_node

        full_dist += self.distance_matrix[current_node][visited_nodes[0]]
        visited_nodes.append(current_node)
        return full_dist

    def __find_min(self, distances, visited_nodes):
        min_value = MAX_DISTANCE + 1
        min_index = 0
        for i in range(len(distances)):
            if min_value > distances[i] > 0 and (i not in visited_nodes):
                min_value = distances[i]
                min_index = i
        return min_index

    def print_graph(self):
        for row in self.distance_matrix:
            print(row)

    def print_pheromone(self):
        print("The pheromone matrix is")
        for row in self.pheromone_matrix:
            for value in row:
                print(f'{value:.3f}', end=' ')
            print()
        print()