import random
import tkinter as tk 
from PIL import Image, ImageTk
import basarui 
import time

# init
global trekkingHarStartet
trekkingHarStartet= False
logfile = open("log.txt", "a")

root = tk.Tk()
root.geometry("600x350")
root.title("UtøyBedehusBasartrekker") 
root.config(bg="#252525") #001116
root.rowconfigure(10, weight=1)
root.columnconfigure(0, weight=1)
root.resizable(False, False)
logo = tk.PhotoImage(file="../img/mortennobg.png")
root.iconphoto(False, logo)



def Trekk(event=0): # event fra tkinter.bind("<Return>", Trekk)
    minst = entryMinsteTall.get()
    størst = entryStørsteTall.get()
    randomNumber = random.randint(int(minst), int(størst))
    logfile.write(f"[Time: {time.ctime()}] {randomNumber}\n")
    basarui.ByttTall(randomNumber)

def StartTrekking(nyttImg):
    global trekkingHarStartet
    if trekkingHarStartet:
        Trekk()
    else:
        trekkingHarStartet = True
        startTrekking.configure(image=nyttImg)
        basarui.LagNyttVindu()



labelMinsteTall = tk.Label(root, text="Skriv det minste tallet her", bg="#252525", fg="#ffffff", font=("Areal", 12, "bold"))
labelStørsteTall = tk.Label(root, text="Skriv det største tallet her", bg="#252525", fg="#ffffff", font=("Areal", 12, "bold"))
labelMinsteTall.grid(row=0, column=0, padx=20, pady=20, sticky="nw")
labelStørsteTall.grid(row=0, column=1, padx=20, pady=20, sticky="ne")


entryMinsteTall = tk.Entry(root, border=0, font=("helvetica", 12), justify="center") 
entryStørsteTall = tk.Entry(root, border=0, font=("helvetica", 12), justify="center")
entryMinsteTall.insert(0, 1)
entryStørsteTall.insert(0, 1000)
entryMinsteTall.grid(row=1, column=0, padx=20, pady=20, sticky="nw")
entryStørsteTall.grid(row=1, column=1, padx=20, pady=20, sticky="ne")


tempImgNy = Image.open("../img/nyttTall.png")
resizeTempImgNy = tempImgNy.resize((200, 100), Image.LANCZOS)
startTrekkingImgNy= ImageTk.PhotoImage(resizeTempImgNy)

if not trekkingHarStartet:
    tempImg = Image.open("../img/startTrekking.png")
    resizeTempImg = tempImg.resize((200, 100), Image.LANCZOS)
    startTrekkingImg = ImageTk.PhotoImage(resizeTempImg)
    startTrekking = tk.Button(root, image=startTrekkingImg, border=0, highlightthickness=0, bg="#252525", activebackground="#252525", command=lambda: StartTrekking(startTrekkingImgNy))
    startTrekking.grid(row=10, column=0, columnspan=2, padx=20, pady=20)

root.bind("<Return>", Trekk)


root.mainloop()
logfile.close()
