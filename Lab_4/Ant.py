class Ant:
    def __init__(self, ant_type, position):
        self.__is_wild = ant_type
        self.__position = position
        self.way = list()

    def get_way_length(self, world):
        length = 0
        for i in range(len(self.way) - 1):
            length += world.distance_matrix[self.way[i]][self.way[i + 1]]
        length += world.distance_matrix[self.way[-1]][self.way[0]]
        return length

    def get_type(self):
        return self.__is_wild

    def get_position(self):
        return self.__position
