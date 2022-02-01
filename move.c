/*
** EPITECH PROJECT, 2021
** move things.c
** File description:
** move sprites from my game
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <SFML/Audio.h>
#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundBuffer.h>
#include <stdio.h>

void move_boo(sfIntRect boo_rect, sfSprite *boosprite, sfVector2f boopos, sfRenderWindow *window)
{
    boo_rect.left += 202;
    if (boo_rect.left >= 2626)
        boo_rect.left = 0;
    sfSprite_setTextureRect(boosprite, boo_rect);
    sfSprite_setPosition(boosprite, boopos);
}

void disp_all(sfRenderWindow *window, sfSprite *backsprite, sfSprite *boosprite, sfSprite *boosprite2, sfSprite *cursors)
{
    sfRenderWindow_drawSprite(window, backsprite, NULL);
    sfRenderWindow_drawSprite(window, boosprite, NULL);
    sfRenderWindow_drawSprite(window, boosprite2, NULL);
    sfRenderWindow_drawSprite(window, cursors, NULL);
}