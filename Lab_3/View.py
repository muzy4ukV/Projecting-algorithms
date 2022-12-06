from tkinter import *
from Control import *


class View(Tk):
    def __init__(self):
        super().__init__()
        self.__frame = Frame(self)
        self.__bd_lbl = Label(self.__frame, text="Моя СУБД", font=("Comic Sans MS", 14))
        self.__key_lbl = Label(self.__frame, text="Ключ", font=("Comic Sans MS", 12))
        self.__key_ent = Entry(self.__frame, font=("Comic Sans MS", 12))
        self.__value_lbl = Label(self.__frame, text="Значення", font=("Comic Sans MS", 12))
        self.__value_ent = Entry(self.__frame, font=("Comic Sans MS", 12))
        self.__clear_btn = Button(self.__frame, text="Очистити поля", font=("Comic Sans MS", 12), command=self.__clear)
        self.__choose_lbl = Label(self.__frame, text="Оберіть дію", font=("Comic Sans MS", 14))
        self.__action = IntVar()
        self.__action.set(1)
        self.__search_rbtn = Radiobutton(self.__frame, text="Пошук за ключем", variable=self.__action, value=1,
                                         font=("Comic Sans MS", 12))
        self.__add_rbtn = Radiobutton(self.__frame, text="Додати значення", variable=self.__action, value=2,
                                      font=("Comic Sans MS", 12))
        self.__delete_rbtn = Radiobutton(self.__frame, text="Видалити значення", variable=self.__action, value=3,
                                         font=("Comic Sans MS", 12))
        self.__edit_rbtn = Radiobutton(self.__frame, text="Редагування значення", variable=self.__action, value=4,
                                       font=("Comic Sans MS", 12))
        self.__submit_btn = Button(self.__frame, text="Виконати", font=("Comic Sans MS", 12), command=self.__submit)
        self.__result = StringVar()
        self._control = Control(self)
        self.__result_lbl = Label(self.__frame, textvariable=self.__result, font=("Comic Sans MS", 14))
        self.__save_btn = Button(self.__frame, text="Зберегти БД у файл", font=("Comic Sans MS", 12),
                                 command=self._control.save_file)

    def run(self):
        self.__setup_window()
        self.__place_widgets()

    def __setup_window(self):
        self.title("Лабораторна 3")
        monitor_height = self.winfo_screenheight()
        monitor_width = self.winfo_screenwidth()
        app_height = 500
        app_width = 600
        self.geometry(
            f"{app_width}x{app_height}+{int((monitor_width - app_width) / 2)}+{int((monitor_height - app_height) / 2) - 100}")
        self.resizable(False, False)
        self.__frame.place(relheight=0.96, relwidth=0.96, relx=0.02, rely=0.02)

    def __place_widgets(self):
        self.__frame.columnconfigure(0, weight=1)
        self.__frame.columnconfigure(1, weight=1)

        self.__bd_lbl.grid(row=0, column=0, columnspan=2, pady=5)
        self.__key_lbl.grid(row=1, column=0, sticky="e", pady=5, padx=20)
        self.__key_ent.grid(row=1, column=1, sticky="wens", pady=5)
        self.__value_lbl.grid(row=2, column=0, sticky="e", pady=5, padx=20)
        self.__value_ent.grid(row=2, column=1, sticky="wens", pady=5)
        self.__clear_btn.grid(row=3, column=0, columnspan=2, pady=5)
        self.__choose_lbl.grid(row=4, column=0, columnspan=2, pady=5)
        self.__search_rbtn.grid(row=5, column=0, sticky="w")
        self.__add_rbtn.grid(row=6, column=0, sticky="w")
        self.__delete_rbtn.grid(row=7, column=0, sticky="w")
        self.__edit_rbtn.grid(row=8, column=0, sticky="w")
        self.__submit_btn.grid(row=5, column=1, rowspan=4, sticky="we")
        self.__result_lbl.grid(row=9, column=0, columnspan=2, pady=5, sticky="w")
        self.__save_btn.grid(row=10, column=0, columnspan=2, pady=5, sticky="we")

    def __clear(self):
        self.__key_ent.delete(0, END)
        self.__value_ent.delete(0, END)

    def __submit(self):
        self._control.submit(self.__action.get(), self.__key_ent.get(), self.__value_ent.get())

    def set_key(self, key):
        self.__key_ent.delete(0, END)
        self.__key_ent.insert(0, key)

    def set_value(self, value):
        self.__value_ent.delete(0, END)
        self.__value_ent.insert(0, value)

    def set_label(self, line):
        self.__result.set(line)
