import serial
import pygame
from pygame.locals import *

# Serial port settings
ser_port = "/dev/cu.usbmodem1401"  # Change this to your serial port
ser_baudrate = 9600

# Pygame settings
window_size = (800, 600)
text_size = 100
text_color = (255, 255, 255)
background_color = (0, 0, 0)

def main():
    # Initialize serial port
    ser = serial.Serial(ser_port, ser_baudrate)

    # Initialize Pygame
    pygame.init()
    screen = pygame.display.set_mode(window_size)
    pygame.display.set_caption("Serial Data Display")
    font = pygame.font.Font(None, text_size)

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == QUIT:
                running = False

        # Read data from serial port
        if ser.in_waiting > 0:
            data = ser.readline().decode("utf-8").strip()

            # Clear the screen
            screen.fill(background_color)

            # Display the received data as large text
            text_surface = font.render(data, True, text_color)
            text_rect = text_surface.get_rect(center=(window_size[0] // 2, window_size[1] // 2))
            screen.blit(text_surface, text_rect)

            pygame.display.flip()

    # Close serial port and quit Pygame
    ser.close()
    pygame.quit()

if __name__ == "__main__":
    main()
