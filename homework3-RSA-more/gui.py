from Tkinter import *
from rsa import rsa_encrypt
from rsa import rsa_decrypt

class GUIDemo(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.grid()
        self.createWidgets()

    def createWidgets(self):
        # labels
        self.inputText = Label(self)
        self.inputText["text"] = "Input:"
        self.inputText.grid(row=1, column=0)
        self.inputField = Entry(self)
        self.inputField["width"] = 50
        self.inputField.grid(row=1, column=1, columnspan=9)

        self.encryptOutputText = Label(self)
        self.encryptOutputText["text"] = "encryptOutput:"
        self.encryptOutputText.grid(row=2, column=0)
        self.encryptOutputField = Entry(self)
        self.encryptOutputField["width"] = 50
        self.encryptOutputField.grid(row=2, column=1, columnspan=9)

        self.decryptOutputText = Label(self)
        self.decryptOutputText["text"] = "decryptOutput:"
        self.decryptOutputText.grid(row=3, column=0)
        self.decryptOutputField = Entry(self)
        self.decryptOutputField["width"] = 50
        self.decryptOutputField.grid(row=3, column=1, columnspan=9)


        self.decryptOutputText = Label(self)
        self.decryptOutputText["text"] = "Keylength:"
        self.decryptOutputText.grid(row=4, column=0)
        # select keylength 1024
        self.keylengthRadio = IntVar()
        self.keylengthRadio1 = Radiobutton(self)
        self.keylengthRadio1["text"] = "1024"
        self.keylengthRadio1["variable"] = self.keylengthRadio
        self.keylengthRadio1["value"] = 1024
        self.keylengthRadio1.grid(row=4, column=1, columnspan=2)
        self.keylengthRadio1["command"] =  self.selectKeylength
        # select keylength 2048
        self.keylengthRadio2 = Radiobutton(self)
        self.keylengthRadio2["text"] = "2048"
        self.keylengthRadio2["variable"] = self.keylengthRadio
        self.keylengthRadio2["value"] = 2048
        self.keylengthRadio2.grid(row=4, column=3, columnspan=2)
        self.keylengthRadio2["command"] =  self.selectKeylength
        # select keylength 4096
        self.keylengthRadio3 = Radiobutton(self)
        self.keylengthRadio3["text"] = "4096"
        self.keylengthRadio3["variable"] = self.keylengthRadio
        self.keylengthRadio3["value"] = 4096
        self.keylengthRadio3.grid(row=4, column=5, columnspan=4)
        self.keylengthRadio3["command"] =  self.selectKeylength

        # buttons
        self.encrypt = Button(self)
        self.encrypt["text"] = "Encrypt"
        self.encrypt.grid(row=9, column=2)
        self.encrypt["command"] =  self.encrypt_display
        self.decrypt = Button(self)
        self.decrypt["text"] = "Decrypt"
        self.decrypt.grid(row=9, column=4)
        self.decrypt["command"] =  self.decrypt_display
        self.clear = Button(self)
        self.clear["text"] = "Clear"
        self.clear.grid(row=9, column=6)
        self.clear["command"] =  self.clear_field

        # message for remind user and show the operation-result for user
        self.displayText = Label(self)
        self.displayText["text"] = "Nothing happened"
        self.displayText.grid(row=8, column=0, columnspan=10)

    # method for encrypt button event
    def encrypt_display(self):
        self.plaintext = self.inputField.get()
        keylength = self.keylengthRadio.get()

        # make sure user input is not null and encrypt it
        if self.plaintext == "":
            self.displayText["text"] = "No user input!"
            return

        # make sure user must select the keylength
        if keylength == 0:
            self.displayText["text"] = "You should select the keylength !"
            return

        # make sure the input is digit
        if not self.plaintext.isdigit():
            self.displayText["text"] = "Only is allowed input the digit !"
            return
        else:
            p, q, n, e, d, plain, cipher, timeEncrypt = rsa_encrypt(int(self.plaintext), keylength)
            self.d = d
            self.p = p
            self.q = q
            self.encryptOutputField.delete(0, END)
            self.encryptOutputField.insert(0, cipher)
            self.displayText["text"] = "Encrypt success ! Cost Time : " + str(timeEncrypt) + " seconds."

    # method for decrypt button event
    def decrypt_display(self):
        self.cipher = self.encryptOutputField.get()
        if self.cipher == "":
            self.displayText["text"] = "No cipher!"
        else:
            timeDecrypt, decrypted  = rsa_decrypt(int(self.d), int(self.p), int(self.q), int(self.cipher))
            self.decryptOutputField.delete(0, END)
            self.decryptOutputField.insert(0, decrypted)
            self.displayText["text"] = "Decrypt success ! Cost Time : " + str(timeDecrypt) + " seconds."

    # method for clear button event
    def clear_field(self):
        self.inputField.delete(0, END)
        self.encryptOutputField.delete(0, END)
        self.decryptOutputField.delete(0, END)
        self.displayText["text"] = "Clear done."

    # method for select keylength-radio event
    def selectKeylength(self):
        self.displayText["text"] = "You have setted the keylength is " + str(self.keylengthRadio.get()) + " !"

if __name__ == '__main__':
    tk = Tk()
    tk.title("Homework3-RSA")
    app = GUIDemo(master=tk)
    app.mainloop()
