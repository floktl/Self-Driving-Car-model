import pygame

# Initialize Pygame
pygame.init()

# Set up display
screen = pygame.display.set_mode((500, 500))
pygame.display.set_caption("Key Detection Example")

running = True

while running:
    pygame.time.delay(100)  # Add delay to avoid excessive CPU usage

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Get the state of all keys
    keys = pygame.key.get_pressed()

    # Check if specific keys are pressed
    if keys[pygame.K_w] and keys[pygame.K_a]:
        print("W and A are both pressed!")

    # Print all currently pressed keys
    # pressed_keys = [pygame.key.name(k) for k, v in enumerate(keys) if v]
    # if pressed_keys:
    #     print("Pressed Keys:", pressed_keys)

pygame.quit()
