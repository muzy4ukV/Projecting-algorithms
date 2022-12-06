T = 10
FILE_NAME = 'data/MOCK_DATA.txt'
from Model import *
from tkinter import messagebox


class Control:
    def __init__(self, view):
        self.__view = view
        self.__BTree = BTree(T)
        self.open_file()

    def open_file(self):
        try:
            file = open(FILE_NAME, "rt")
            data = file.read()
            data = data.strip()
            data = data.split('\n')
            for i in range(0, len(data)):
                k = data[i][1:-1].split(', ')
                self.__BTree.insert([int(k[0]), k[1][1:-1]])
            file.close()
            self.__view.set_label(f"Файл {FILE_NAME} був успішно відкритий")
        except IOError:
            messagebox.showerror("Помилка", f"Файл {FILE_NAME} неможливо відкрити")

    def submit(self, action, key, value):
        try:
            key = int(key)
        except ValueError:
            action = 0
            messagebox.showerror('Помилка', "Неправильно заданий ключ")
        match action:
            case 1:
                self.__search(key)
            case 2:
                self.__add(key, value)
            case 3:
                self.__delete(key)
            case 4:
                self.__edit(key, value)
            case _:
                pass

    def __search(self, key):
        value = self.__BTree.search(key)
        if value is not None:
            self.__view.set_key(key)
            self.__view.set_value(value)
            self.__view.set_label(f"За ключем {key} знаходиться {value}")
        else:
            self.__view.set_label("Запис не занйдено")
            self.__view.set_value("Запис не занйдено")

    def __add(self, key, value):
        value = value.strip()
        if value:
            res = self.__BTree.search(key)
            if not res:
                self.__BTree.insert([key, value])
                self.__view.set_label("Елемент було успішно додано за ключем")
            else:
                messagebox.showwarning("Попередження", "Даний ключ вже існує")
        else:
            messagebox.showwarning("Попередження", "Поле 'Значення' пусте")

    def __delete(self, key):
        res = self.__BTree.search(key)
        if res:
            self.__BTree.delete(self.__BTree.root, [key, ])
            self.__view.set_label(f"Елемент {key} було успішно видалено")
        else:
            messagebox.showwarning("Попередження", "Такого ключа не існує")

    def __edit(self, key, value):
        value = value.strip()
        if value:
            res = self.__BTree.search(key)
            if res:
                self.__BTree.edit(key, value)
                self.__view.set_label("Елемент було успішно відредаговано")
            else:
                messagebox.showwarning("Попередження", "Такого ключа не існує")
        else:
            messagebox.showwarning("Попередження", "Поле 'Значення' пусте")

    def save_file(self):
        self.__BTree.all_values = list()
        self.__BTree.save_data(self.__BTree.root)
        with open(FILE_NAME, "wt") as file:
            file.writelines("%s\n" % i for i in self.__BTree.all_values)
        self.__view.set_label("БД була успішно збережена")
