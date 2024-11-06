import tkinter as tk
import pickle
import os

class InkScreenApp:
    def __init__(self, master):
        self.master = master
        self.master.title("Ink Screen Simulator")
        
        self.canvas_width = 250
        self.canvas_height = 122
        
        self.canvas = tk.Canvas(self.master, width=self.canvas_width, height=self.canvas_height, bg="white")
        self.canvas.pack()
        
        # Draw coordinate axes
        self.canvas.create_line(0, 0, self.canvas_width, 0, fill="black")  # x-axis
        self.canvas.create_line(0, 0, 0, self.canvas_height, fill="black")  # y-axis
        
        self.history = []  # to store drawing commands for undo
        
        self.command_entry = tk.Entry(self.master)
        self.command_entry.pack()
        
        self.command_entry.focus_set()
        self.command_entry.bind("<Return>", self.execute_command)
        
        # Bind keys to functions
        self.master.bind("u", self.undo)
        self.master.bind("s", self.save)
        self.master.bind("l", self.load)
        self.master.bind("q", self.quit_app)  # Bind 'q' key to quit function

        # Flag to indicate whether we are redrawing from history
        self.is_redrawing = False

        # Load history from file if it exists
        self.load()

    def execute_command(self, event):
        command = self.command_entry.get()
        self.process_command(command)
        self.command_entry.delete(0, tk.END)
    
    def process_command(self, command):
        parts = command.split()
        if parts[0] == "wenzi" and len(parts) >= 4:
            x1 = int(parts[1])
            y1 = int(parts[2])
            text = " ".join(parts[3:])
            self.draw_text_placeholder(x1, y1, text)
        elif len(parts) >= 5:
            shape = parts[0]
            x1 = int(parts[1])
            y1 = int(parts[2])
            x2 = int(parts[3])
            y2 = int(parts[4])
            thickness = int(parts[5]) if len(parts) > 5 else 1
            
            if shape == "line":
                self.draw_line(x1, y1, x2, y2, thickness)
            elif shape == "rectangle":
                self.draw_rectangle(x1, y1, x2, y2, thickness)
            else:
                print("Unknown shape command")
        else:
            print("Invalid command")

    def draw_text_placeholder(self, x1, y1, text):
        # Calculate the width and height of the placeholder box
        width = len(text) * 7
        height = 12
        self.canvas.create_rectangle(x1, y1, x1 + width, y1 + height, outline="red")

        if not self.is_redrawing:
            self.history.append(("wenzi", x1, y1, text))

    def draw_line(self, x1, y1, x2, y2, thickness):
        if thickness == 1:
            line = self.canvas.create_line(x1, y1, x2, y2, fill="black")
        elif thickness == 2:
            line = self.canvas.create_line(x1, y1, x2, y2, fill="black", width=2)
        else:
            print("Unsupported line thickness")
            return
        
        if not self.is_redrawing:
            self.history.append(("line", x1, y1, x2, y2, thickness))
    
    def draw_rectangle(self, x1, y1, x2, y2, thickness):
        if thickness == 1:
            rect = self.canvas.create_rectangle(x1, y1, x2, y2, outline="black")
        elif thickness == 2:
            rect = self.canvas.create_rectangle(x1, y1, x2, y2, outline="black", width=2)
        else:
            print("Unsupported line thickness")
            return
        
        if not self.is_redrawing:
            self.history.append(("rectangle", x1, y1, x2, y2, thickness))
    
    def undo(self, event=None):
        if self.history:
            self.history.pop()
            self.redraw_canvas()
        else:
            print("Nothing to undo")
    
    def save(self, event=None):
        with open("drawing_history.pkl", "wb") as f:
            pickle.dump(self.history, f)
        print("Drawing saved.")
    
    def load(self, event=None):
        if os.path.exists("drawing_history.pkl"):
            with open("drawing_history.pkl", "rb") as f:
                self.history = pickle.load(f)
            self.redraw_canvas()
            print("Drawing loaded.")
        else:
            print("No saved drawing found.")
    
    def redraw_canvas(self):
        self.is_redrawing = True
        self.canvas.delete("all")
        # Redraw axes
        self.canvas.create_line(0, 0, self.canvas_width, 0, fill="black")  # x-axis
        self.canvas.create_line(0, 0, 0, self.canvas_height, fill="black")  # y-axis
        
        for command in self.history:
            shape = command[0]
            if shape == "line":
                _, x1, y1, x2, y2, thickness = command
                self.draw_line(x1, y1, x2, y2, thickness)
            elif shape == "rectangle":
                _, x1, y1, x2, y2, thickness = command
                self.draw_rectangle(x1, y1, x2, y2, thickness)
            elif shape == "wenzi":
                _, x1, y1, text = command
                self.draw_text_placeholder(x1, y1, text)
        self.is_redrawing = False

    def quit_app(self, event=None):
        self.master.quit()

if __name__ == "__main__":
    root = tk.Tk()
    app = InkScreenApp(root)
    root.mainloop()
