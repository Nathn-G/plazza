from parsing import *
import time
import pygame
from math import *

def get_circle_coord(angle, r):
    return r * sin(angle), r * cos(angle)

def main():
    kitchens,ingredients = parsing("../log")
    if kitchens == None:
        kitchens,ingredients = {}, {}
    pygame.init()
    running = True

    screen = pygame.display.set_mode((1800, 1000))
    fountain = pygame.image.load("assets/fountain.png")
    fountain = pygame.transform.scale(fountain, (100, 100))
    kitchen = pygame.image.load("assets/kitchen.png")
    kitchen = pygame.transform.scale(kitchen, (200, 200))
    clock = time.time() * 1000
    font = pygame.font.SysFont(None, 42)
    cook_font = pygame.font.SysFont(None, 22)
    displayed = {}
    while running:
        kitchen_pos = []
        now = time.time() * 1000
        if now - clock > 1000:
            a,b = parsing("../log")
            if a != None:
                kitchens,ingredients = a,b
            clock = now
        screen.fill((0, 155, 0))
        screen.blit(fountain, (850, 450))
        text = font.render("nb Kitchen: " + str(len(kitchens)), True, (0, 0, 0))
        screen.blit(text, (10, 10))
        for i in kitchens:
            angle = (i * pi * 2) / len(kitchens)
            x, y = get_circle_coord(angle, 400)
            x += 800
            y += 400
            save_y = y
            kitchen_pos.append((x, y, i))
            screen.blit(kitchen, (x, y))
            if i in displayed and displayed[i] == 1:
                text = cook_font.render("id: " + str(i), True, (0, 0, 0))
                if y - 20 < 0:
                    screen.blit(text, (x + 100, 200))
                else:
                    screen.blit(text, (x + 100, y - 20))
                for m in kitchens[i]["cooks"]:
                    txt = "Cook: " + m
                    cook_text = cook_font.render(txt, True, (0, 0, 0))
                    screen.blit(cook_text, (x + 200, y))
                    y += 25
                x += 100
                y = save_y
                for j in ingredients[i]:
                    txt = str(j) + " " + str(ingredients[i][j])
                    txt_render = cook_font.render(txt, True, (0, 0, 0))
                    screen.blit(txt_render, (x +200, y))
                    y += 25
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.MOUSEBUTTONDOWN:
                x, y = pygame.mouse.get_pos()
                for kx, ky, ki in kitchen_pos:
                    if kx <= x <= kx + 200 and ky <= y <= ky + 200:
                        if ki in displayed and displayed[ki] == 1:
                            displayed[ki] = 0
                        else:
                            displayed[ki] = 1
        pygame.display.update()

if __name__ == '__main__':
    main()