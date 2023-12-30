import tkinter as tk
global vinnerTall 



def LagNyttVindu():
    global vinnerTall
    root = tk.Tk()
    root.configure(bg="#000000")
    root.title("BASAR")
    root.geometry("850x500")

    vinnerTall = tk.Label(root, text="", font=("Roboto", 250), bg="#000000", fg="#ffffff")
    vinnerTall.pack(expand=True)
    root.mainloop()

def ByttTall(nummer):
    global vinnerTall
    vinnerTall.config(text=nummer) 
