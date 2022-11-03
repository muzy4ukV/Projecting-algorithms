from Node import *
from copy import deepcopy, copy


class Algo:
    """Class that contains 2 algorithms: IDS and RBFS"""

    def __init__(self, root, number):
        self.__path = list()
        self.__n = number
        self.root = root
        self.__iterations = 0
        self.__states_num = 0
        self.__max_states = 0

    def IDS(self):
        for i in range(0, self.__n + 2):
            result = self.DLS(self.root, i)
            if result:
                return

    def DLS(self, node, max_depth):
        self.__iterations += 1   # statistics
        if node.current_depth >= max_depth and node.state.is_true():
            if node.max_states_num > self.__max_states:
                self.__max_states = node.max_states_num
            self.__path.insert(0, node)
            return True
        elif node.current_depth >= max_depth:
            if node.max_states_num > self.__max_states:
                self.__max_states = node.max_states_num
            return False
        child_nodes = self.expand_ids(node)
        self.__states_num += len(child_nodes)  # statistics
        for child in child_nodes:
            child.max_states_num += len(child_nodes)   # statistics
            result = self.DLS(child, max_depth)
            if result:
                self.__path.insert(0, node)
                return True
        return False

    def expand_ids(self, node):
        child_nodes = list()
        for i in range(self.__n):
            new_node = Node(deepcopy(node.state), copy(node.current_row) + 1, copy(node.current_depth) + 1,
                            copy(node.max_states_num))
            new_node.state.move_queen(new_node.current_row, i)
            child_nodes.append(new_node)
        return child_nodes

    def RBFS(self, node, f_limit):
        self.__iterations += 1   # statistics
        if node.state.is_true():
            if node.max_states_num > self.__max_states:
                self.__max_states = node.max_states_num
            self.__path.insert(0, node)
            return True, None
        child_nodes = self.expand_rbfs(node)
        self.__states_num += len(child_nodes)   # statistics
        while True:
            self.sort(child_nodes)
            best_node = child_nodes[0]
            if not best_node.state.board == node.state.board:
                if best_node.f_value > f_limit:
                    return False, best_node.f_value
                alternative = child_nodes[1].f_value
                best_node.max_states_num += len(child_nodes)
                result, best_node.f_value = self.RBFS(best_node, min(alternative, f_limit))
                if result:
                    self.__path.insert(0, node)
                    return True, None

    def expand_rbfs(self, node):
        child_nodes = list()
        for i in range(self.__n):
            if not i == node.current_row:
                for j in range(1, self.__n):
                    new_node = Node(deepcopy(node.state), i, copy(node.current_depth) + 1, copy(node.max_states_num))
                    new_node.state.move_queen(i, j)
                    new_node.f_value = new_node.state.f1() + new_node.current_depth
                    child_nodes.append(new_node)
        return child_nodes

    @staticmethod
    def sort(array):
        length = len(array)
        flag = False
        for i in range(length - 1):
            for j in range(0, length - i - 1):
                if array[j].f_value > array[j + 1].f_value:
                    flag = True
                    array[j], array[j + 1] = array[j + 1], array[j]
            if not flag:
                return

    def output_result(self):
        print("Рішення покроково:")
        if self.__path:
            for i in range(0, len(self.__path) - 1):
                print("Переміщуємо ферзя у", self.__path[i + 1].current_row + 1, "колонці")
                self.__path[i].state.output_board()
                print()
            print("Розв'язок:")
            self.__path[-1].state.output_board()
            print("Кількість переміщень:", len(self.__path) - 1)
            print("\nСтатистика:")
            print("Кількість ітерацій -", self.__iterations)
            print("Кількість створених станів -", self.__states_num)
            print("Максимална кількість станів збережених у пам'яті -", self.__max_states)
        else:
            print("Рішення не знайдено")
