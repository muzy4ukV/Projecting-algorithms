class Node:
    """Class that represents a node"""
    def __init__(self, state, current_row, current_depth, current_state=0):
        self.state = state
        self.current_row = current_row
        self.current_depth = current_depth
        self.f_value = -1
        self.max_states_num = current_state
