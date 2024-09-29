import ctypes
import tkinter as tk

game = ctypes.CDLL("./game.so")
root = tk.Tk()

def start():
    root.destroy()
    game.main()

game.stinky("LOL\n".encode())
    
font_tuple = ("Iosevka Nerd Font", 90, "bold")
tk.Button(root, text="START", font=font_tuple, command=start).pack()
root.mainloop()
