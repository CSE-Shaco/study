import pygame
import random

pygame.init()

width, height = 288, 512
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Flappy Bird")

bird_image = pygame.image.load("bird.png").convert_alpha()
# background_image = pygame.image.load("/background.png").convert()
pipe_image = pygame.image.load("pipe.png").convert_alpha()


class Bird(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = bird_image
        self.rect = self.image.get_rect(center=(50, 256))
        self.velocity = 0

    def update(self):
        self.velocity += 0.5
        self.rect.y += self.velocity


class Pipe(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pipe_image
        self.rect = self.image.get_rect(midtop=(width + 50, random.randint(-400, -200)))
        self.velocity = -4

    def update(self):
        self.rect.x += self.velocity


clock = pygame.time.Clock()
bird = Bird()
pipes = pygame.sprite.Group()
score = 0

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                bird.velocity = -10

    # screen.blit(background_image, (0, 0))

    bird.update()
    pipes.update()

    screen.fill((255, 255, 255))

    if len(pipes) < 1:
        pipes.add(Pipe())

    for pipe in pipes:
        if pipe.rect.right < 0:
            pipes.remove(pipe)
            score += 1

    pipes.draw(screen)
    screen.blit(bird.image, bird.rect)

    pygame.display.update()
    clock.tick(60)
