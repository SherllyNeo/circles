#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <string.h>
//#define SCREEN_WIDTH 900
#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 483
#define RADIUS 30
#define INITACC 0.01
#define INITSPEED 1.2
#define TOPSPEED 30
#define BallsLim 50

typedef struct {
    int x;
    int y;
    float radius;
    Color colour;
    Color DefColour;
    float speedx;
    float accelx;
    int count;
    Sound sound;

} DCircle;

void DrawCircleStruct(DCircle c) {
    DrawCircle(c.x, c.y, c.radius, c.colour);
}

int main()
{
    //    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    int more = 0;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bilo"); SetTargetFPS(130);
    InitAudioDevice();
    SetTargetFPS(30);


    Sound A;
    A = LoadSound("./src/notes/A.mp3");
    Sound B;
    B = LoadSound("./src/notes/B.mp3");
    Sound C;
    C = LoadSound("./src/notes/C.mp3");
    Sound D;
    D = LoadSound("./src/notes/D.mp3");
    Sound E;
    E = LoadSound("./src/notes/E.mp3");
    Sound F;
    F = LoadSound("./src/notes/F.mp3");
    Sound G;
    G = LoadSound("./src/notes/G.mp3");
    Sound H;
    H = LoadSound("./src/notes/A4.mp3");

    DCircle Circle1 = {RADIUS*2, RADIUS*1,RADIUS, RED,RED,INITSPEED,INITACC,0,A};
    DCircle Circle2 = {RADIUS*2, RADIUS*3,RADIUS, ORANGE,ORANGE,INITSPEED*2,INITACC,0,B};
    DCircle Circle3 = {RADIUS*2, RADIUS*5,RADIUS, LIME,LIME,INITSPEED*3,INITACC,0,C};
    DCircle Circle4 = {RADIUS*2, RADIUS*7,RADIUS, GREEN, GREEN,INITSPEED*4.,INITACC,0,D};
    DCircle Circle5 = {RADIUS*2, RADIUS*9,RADIUS, DARKGREEN,DARKGREEN,INITSPEED*5,INITACC,0,E};
    DCircle Circle6 = {RADIUS*2, RADIUS*11,RADIUS, SKYBLUE,SKYBLUE,INITSPEED*6,INITACC,0,F};
    DCircle Circle7 = {RADIUS*2, RADIUS*13,RADIUS, BLUE,BLUE,INITSPEED*7,INITACC,0,G};
    DCircle Circle8 = {RADIUS*2, RADIUS*15,RADIUS, PURPLE,PURPLE,INITSPEED*8,INITACC,0,H};
    DCircle *Circles[BallsLim] = {&Circle1,&Circle2,&Circle3,&Circle4,&Circle5,&Circle6,&Circle7,&Circle8};
    int AmountOfCircles = 8;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        for (int i = 0; i<AmountOfCircles;i++) {
            DCircle* circleX = Circles[i];
            circleX->x += circleX->speedx;
            if (circleX->speedx < TOPSPEED) {
                circleX->speedx += circleX->accelx;
            }
            else {
                circleX->speedx -= circleX->accelx;
            }

            if ((circleX->x - circleX->radius) < 0 || (circleX->x + circleX->radius) > GetScreenWidth()) {
                circleX->speedx = -(circleX->speedx);
                circleX->accelx = -(circleX->accelx);
                circleX -> colour = WHITE;
                DCircle TmpNewCircle;

                if ((circleX->x - circleX->radius) < 0) {
                    circleX->x = circleX->radius + 2;
                    if (more) {
                        TmpNewCircle = (DCircle){GetScreenWidth() - (circleX->radius + 2), circleX->y,circleX->radius,circleX->DefColour,circleX->DefColour,circleX->speedx,circleX->accelx,circleX->count, circleX->sound};
                    }
                }

                if ((circleX->x + circleX->radius) > GetScreenWidth()) {
                    circleX->x = GetScreenWidth() - (circleX->radius + 2);
                    if (more) {
                        TmpNewCircle = (DCircle){(circleX->radius + 2), circleX->y,RADIUS, circleX->DefColour,circleX->DefColour,INITSPEED*8,INITACC,circleX->count,circleX->sound};
                    }
                }
                PlaySound(circleX->sound);
                if (more) {
                    DCircle *NewCircle = malloc(sizeof(DCircle));
                    memcpy(NewCircle, &TmpNewCircle, sizeof(DCircle));
                    Circles[AmountOfCircles++] = NewCircle;
                }

            }
            circleX -> count += 1;
            DrawCircleStruct(*circleX);
            if ( (circleX -> count) > 5) {
                    (circleX -> count) = 0;
                    circleX -> colour = circleX->DefColour;
                }
        }
        EndDrawing();
    }

    UnloadSound(A);
    UnloadSound(B);
    UnloadSound(C);
    UnloadSound(D);
    UnloadSound(E);
    UnloadSound(F);
    UnloadSound(G);

    CloseAudioDevice();
    CloseWindow();


    return EXIT_SUCCESS;
}
