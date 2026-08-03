import keyboard
import threading
import time

running = False

def spam_f4():
    global running
    while running:
        keyboard.send('f4')  # This uses low-level key event
        time.sleep(0.01)

def toggle():
    global running
    running = not running
    print("Running" if running else "Stopped")
    if running:
        threading.Thread(target=spam_f4, daemon=True).start()

def main():
    print("Press Ctrl to toggle F4 spam. Press ESC to exit.")
    while True:
        if keyboard.is_pressed('ctrl'):
            toggle()
            while keyboard.is_pressed('ctrl'):
                time.sleep(0.2)
        if keyboard.is_pressed('esc'):
            print("Exiting.")
            break

main()
