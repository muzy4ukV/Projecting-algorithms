from Constants import *
from random import *
from Ant import *


class Algo:
    def __init__(self, world, num):
        self.__model = world
        self.__num_of_nodes = num
        # L min
        self.__l_min = MAX_DISTANCE * self.__num_of_nodes
        self.__find_l_min()
        # L*
        self.__l_best = MAX_DISTANCE * self.__num_of_nodes
        #індекс мурахи з найкоротшим шляхом
        self.__best_ant = 0

    def __find_l_min(self):
        for i in range(self.__num_of_nodes):
            new_value = self.__model.greedy_search(i)
            if new_value < self.__l_min:
                self.__l_min = new_value
        print("L-min =", self.__l_min)


    def run(self):
        ants = self.__set_ants()
        for t in range(1, T_MAX + 1):
            #обчислюємо шляху для всіх мурах
            for ant in ants:
                ant.way = list()
                ant.way.append(ant.get_position())
                while len(ant.way) < self.__num_of_nodes:
                    new_node = self.__find_new_node(ant)
                    ant.way.append(new_node)
            #знаходимо найкортоший шлях серед всіх мурах
            best_length, best_ant = self.__find_min_way(ants)
            if best_length < self.__l_best:
                self.__l_best = best_length
                self.__best_ant = best_ant
            self.__update_pheromone(ants)
            if t % T_ITER == 0:
                print("On the", t, "iteration, the best lenght is:", self.__l_best)
                print("And way is", ants[self.__best_ant].way)
                #self.__model.print_pheromone()

    #функція що визначає наступну вершину для розгляду
    def __find_new_node(self, ant):
        if ant.get_type():
            possible_node = [x for x in range(self.__num_of_nodes) if x not in ant.way]
            new_node = choice(possible_node)
            return new_node
        else:
            cur = ant.way[-1]
            probabilities = list()
            for i in range(self.__num_of_nodes):
                if i in ant.way:
                    probabilities.append(0)
                else:
                    probabilities.append(pow(self.__model.pheromone_matrix[cur][i], ALPHA) * pow(1 / self.__model.distance_matrix[cur][i], BETA))
            prob_sum = sum(probabilities)
            for i in range(len(probabilities)):
                probabilities[i] /= prob_sum
            rand_num = random()
            sum_num = 0
            for prob in probabilities:
                sum_num += prob
                if rand_num < sum_num:
                    return probabilities.index(prob)
            return len(probabilities) - 1

    def __find_min_way(self, ants):
        min_length = MAX_DISTANCE * self.__num_of_nodes
        ant_index = 0
        for ant in ants:
            way_len = ant.get_way_length(self.__model)
            if way_len < min_length:
                min_length = way_len
                ant_index = ants.index(ant)
        return min_length, ant_index

    #задаємо масив мурах
    def __set_ants(self):
        nodes_in_use = list()
        ants = list()
        num_of_wild = 0
        while len(ants) < NUM_OF_ANTS:
            new_position = randint(0, self.__num_of_nodes - 1)
            if new_position not in nodes_in_use:
                if num_of_wild < NUM_OF_WILD_ANTS:
                    ants.append(Ant(True, new_position))
                    num_of_wild += 1
                else:
                    ants.append(Ant(False, new_position))
                nodes_in_use.append(new_position)
        return ants

    def __update_pheromone(self, ants):
        for i in range(self.__num_of_nodes):
            for j in range(self.__num_of_nodes):
                self.__model.pheromone_matrix[i][j] *= (1 - R)
        for ant in ants:
            pheromone_of_ant = self.__l_min / ant.get_way_length(self.__model)
            for i in range(len(ant.way) - 1):
                self.__model.pheromone_matrix[ant.way[i]][ant.way[i+1]] += pheromone_of_ant
                self.__model.pheromone_matrix[ant.way[i+1]][ant.way[i]] += pheromone_of_ant
            self.__model.pheromone_matrix[ant.way[-1]][ant.way[0]] += pheromone_of_ant
            self.__model.pheromone_matrix[ant.way[0]][ant.way[-1]] += pheromone_of_ant
