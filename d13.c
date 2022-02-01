/*
** EPITECH PROJECT, 2021
** toad
** File description:
** capitaine
*/

#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <SFML/Audio.h>
#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundBuffer.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc == 1)
        gamebase();
    else if (argv[1][1] == 'h')
        printf("My_Hunter :\n Infinite duckhunt-inspired game.\
        \n\nPoint and click, aim at the boos to gain points.\
        \nIf they leave the screen you will lose a life.");
    else
        gamebase();
}

int gamebase()
{
    sfClock *clock;
    int scene = 0;
    sfTime time;
    float seconds;
    int lives = 3;
    int score = 0;
    char *scorestr = malloc(sizeof(char) * 10);
    char *lifestr = malloc(sizeof(char) * 10);
    clock = sfClock_create();
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "Boo !", sfResize | sfClose, NULL);
    if (!window)
        return EXIT_FAILURE;
    sfIntRect back_rect = {0, 0, 1920, 1080};
    sfTexture *back = sfTexture_createFromFile("assets/test.jpg", &back_rect);
    if (!back)
        return (1);
    sfSprite *backsprite = sfSprite_create();
    sfSprite_setTexture(backsprite, back, sfTrue);
    sfIntRect boo_rect = {0, 0, 202, 202};
    sfIntRect boo_rect2 = {0, 0, 202, 202};
    sfFont *font = sfFont_createFromFile("assets/font.ttf");
    sfVector2f score_pos = {20, 20};
    sfVector2f score_size = {2, 2};
    sfText *score_text = sfText_create();
    sfText_setFont(score_text, font);
    sfText_setString(score_text, "Score :");
    scorestr[0] = '0';
    sfText_setPosition(score_text, score_pos);
    sfText_setScale(score_text, score_size);
    sfText_setColor(score_text, sfWhite);
    sfVector2f title_pos = {650, 150};
    sfVector2f title_size = {4, 4};
    sfText *title_text = sfText_create();
    sfText_setFont(title_text, font);
    sfText_setString(title_text, "BOO HUNTER");
    sfText_setPosition(title_text, title_pos);
    sfText_setScale(title_text, title_size);
    sfText_setColor(title_text, sfWhite);
    sfVector2f score_pos2 = {230, 20};
    sfText *score_text2 = sfText_create();
    sfText_setFont(score_text2, font);
    sfText_setString(score_text2, scorestr);
    sfText_setPosition(score_text2, score_pos2);
    sfText_setScale(score_text2, score_size);
    sfText_setColor(score_text2, sfWhite);
    sfVector2f life_pos = {20, 60};
    sfVector2f life_size = {2, 2};
    sfText *life_text = sfText_create();
    sfText_setFont(life_text, font);
    sfText_setString(life_text, "Life :");
    lifestr[0] = '3';
    sfText_setPosition(life_text, life_pos);
    sfText_setScale(life_text, life_size);
    sfText_setColor(life_text, sfWhite);
    sfVector2f life_pos2 = {220, 60};
    sfText *life_text2 = sfText_create();
    sfText_setFont(life_text2, font);
    sfText_setString(life_text2, lifestr);
    sfText_setPosition(life_text2, life_pos2);
    sfText_setScale(life_text2, life_size);
    sfText_setColor(life_text2, sfWhite);
    sfTexture *bootext2 = sfTexture_createFromFile("assets/boosheet2.png", NULL);
    if (!bootext2)
        return (1);
    sfSprite *boosprite2 = sfSprite_create();
    sfSprite_setTexture(boosprite2, bootext2, sfTrue);
    sfSprite_setTextureRect(boosprite2, boo_rect2);
    sfVector2f playpos = {720, 500};
    sfTexture *playtext = sfTexture_createFromFile("assets/play.png", NULL);
    if (!playtext)
        return (1);
    sfSprite *playsprite = sfSprite_create();
    sfSprite_setTexture(playsprite, playtext, sfTrue);
    sfSprite_setPosition(playsprite, playpos);
    sfTexture *bootext = sfTexture_createFromFile("assets/boosheet.png", NULL);
    if (!bootext)
        return (1);
    sfSprite *boosprite = sfSprite_create();
    sfSprite_setTexture(boosprite, bootext, sfTrue);
    sfSprite_setTextureRect(boosprite, boo_rect);
    sfIntRect spr_rect = {0, 0, 72, 72};
    sfTexture* cross = sfTexture_createFromFile("assets/cross.png", &spr_rect);
    if (!cross)
        return (1);
    sfSprite* cursors = sfSprite_create();
    sfSprite_setTexture(cursors, cross, sfTrue);
    sfEvent event;
    sfSoundBuffer    *shootbuffer;
    sfSound          *shootsound;
    shootbuffer = sfSoundBuffer_createFromFile("assets/shoot.wav");
    shootsound = sfSound_create();
    sfSound_setBuffer(shootsound, shootbuffer);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    sfSoundBuffer    *deathbuffer = sfSoundBuffer_createFromFile("assets/death.wav");;
    sfSound          *deathsound = sfSound_create();
    sfSound_setBuffer(deathsound, deathbuffer);
    sfSoundBuffer    *themebuffer;
    sfSound          *themesound;
    themebuffer = sfSoundBuffer_createFromFile("assets/theme.wav");
    themesound = sfSound_create();
    sfSound_setBuffer(themesound, themebuffer);
    sfSound_play(themesound);
    sfVector2f cursprite = {500, 500};
    sfVector2f boopos = {1920, 900};
    sfVector2f boopos2 = {-200, 700};
    sfFloatRect view = {0, 0, 0, 0};
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            else if (event.type == sfEvtMouseMoved) {
                cursprite.x = event.mouseMove.x - 36;
                cursprite.y = event.mouseMove.y - 36;
                sfSprite_setPosition(cursors, cursprite);
            }
            else if (event.type == sfEvtKeyPressed) {
                if (event.key.code == sfKeyEscape)
                    sfRenderWindow_close(window);
            }
            else if (event.type == sfEvtMouseButtonPressed) {
                sfSound_play(shootsound);
                if ((boopos.x + 202 >= event.mouseButton.x && boopos.x <= event.mouseButton.x) \
                && (boopos.y + 202 >= event.mouseButton.y && boopos.y <= event.mouseButton.y)) {
                        boopos.x = 1950;
                        boopos.y = rand() % 960 + 150;
                        score += 30;
                        sfSound_play(deathsound);
                    }
                else if ((boopos2.x + 202 >= event.mouseButton.x && boopos2.x <= event.mouseButton.x) && \
                (boopos2.y + 202 >= event.mouseButton.y && boopos2.y <= event.mouseButton.y)) {
                    boopos2.x = -250;
                    boopos2.y = rand() % 950 + 150;
                    score += 30;
                    sfSound_play(deathsound);
                    }
                    if ((playpos.x + 486 >= event.mouseButton.x && playpos.x <= event.mouseButton.x) \
                    && (playpos.y + 165 >= event.mouseButton.y && playpos.y <= event.mouseButton.y)) {
                        scene = 1;
                    }
                else
                    score -= 15;
            }
            itoa(score, scorestr, 10);
        }
        itoa(lives, lifestr, 10);
        sfRenderWindow_clear(window, sfBlack);
        if (scene == 1) {
            time = sfClock_getElapsedTime(clock);
            seconds = time.microseconds / 1000000.0;
            if (seconds > 0.08) {
                boo_rect.left += 202;
                if (boo_rect.left >= 2626) {
                    boo_rect.left = 0;
                }
                boo_rect2.left += 202;
                if (boo_rect2.left >= 2626) {
                    boo_rect2.left = 0;
                }
                if (boopos.y <= -202) {
                boopos.x = 1950;
                boopos.y = rand() % 960 + 150;
                lives -= 1;
                }
                if (boopos2.y <= -202) {
                boopos2.x = -250;
                boopos2.y = rand() % 950 + 150;
                lives -= 1;
                }
                if (lives <= 0) {
                    scene = 0;
                    score = 0;
                }
                boopos.x -= rand() % 25;
                boopos.y -= rand() % 15;
                boopos2.x += rand() % 29;
                boopos2.y -= rand() % 12;
                sfSprite_setTextureRect(boosprite, boo_rect);
                sfSprite_setPosition(boosprite, boopos);
                sfSprite_setTextureRect(boosprite2, boo_rect2);
                sfSprite_setPosition(boosprite2, boopos2);
                sfClock_restart(clock);
            }
            disp_all(window, backsprite, boosprite, boosprite2, cursors);
            sfRenderWindow_drawText(window, score_text, NULL);
            sfText_setString(score_text2, scorestr);
            sfText_setString(life_text2, lifestr);
            sfRenderWindow_drawText(window, score_text2, NULL);
            sfRenderWindow_drawText(window, life_text, NULL);
            sfRenderWindow_drawText(window, life_text2, NULL);
        }
        else if (scene == 0) {
            score = 0;
            boopos.x = 1920;
            boopos.y = 900;
            boopos2.x = -200;
            boopos2.y = 700;
            sfRenderWindow_drawSprite(window, backsprite, NULL);
            sfRenderWindow_drawSprite(window, playsprite, NULL);
            sfRenderWindow_drawText(window, title_text, NULL);
            sfRenderWindow_drawSprite(window, cursors, NULL);
        }
        sfRenderWindow_display(window);
    }
    sfSprite_destroy(cursors);
    sfTexture_destroy(cross);
    sfSprite_destroy(boosprite);
    sfTexture_destroy(bootext);
    sfSprite_destroy(backsprite);
    sfTexture_destroy(back);
    sfRenderWindow_destroy(window);
    return EXIT_SUCCESS;
}