#include <raylib.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define DEFAULT_W 720
#define DEFAULT_H 480
#define SPACING 10

int min(int x, int y){
  return (x < y) ? x : y;
}

typedef struct {
    Rectangle rec;
    char *text;
    Color bdColor;
    Color bgColor;
    int lenPx;
} Button;

typedef struct {
    Vector2 pos;
    Vector2 vel;
    int radius;
    Color color;
} Ball;

#define DRAWBTN(btn){ \
    DrawRectangleRec(btn.rec, btn.bgColor); \
    DrawRectangleLinesEx(btn.rec, 2, btn.bdColor); \
    DrawTextEx(GetFontDefault(), btn.text, (Vector2){btn.rec.x+5,btn.rec.y+5}, textSize*scale, 1, btn.bdColor); \
}

int main(void){
    // Raylib initialising.
    int screenWidth = DEFAULT_W;
    int screenHeight = DEFAULT_H;
    int screenHalfX = screenWidth/2;
    int screenHalfY = screenHeight/2;
    //SetTraceLogLevel(LOG_NONE);
    InitWindow(screenWidth, screenHeight, "Bebre2288 Game");
    SetTargetFPS(120);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();
    SetExitKey(KEY_F10);
    bool gameStarted    = false;
    bool audioMuted    = false;
    bool settingsOpened = false;
    int tmp;
    //-Raylib initialising.-
    // Variables setup.
    Music music = LoadMusicStream("theme.mp3");
    Ball ball = (Ball){(Vector2){screenHalfX, screenHalfY}, (Vector2){1,1}, 20, YELLOW}; 
    //-Variables setup.-
    while(!WindowShouldClose()){
        // Global game variables. DO NOT TOUCH UNTIL YOU KNOW WHAT YOU ARE DOING
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
        screenHalfX = screenWidth/2;
        screenHalfY = screenHeight/2;
        float scale = fminf((float)screenHeight/DEFAULT_H, (float)screenWidth/DEFAULT_W);
        float textSize = scale*20;
        Vector2 mousePosition = GetMousePosition();
        if(IsKeyPressed(KEY_ESCAPE)){
            settingsOpened = !settingsOpened;
        }

        //-Global game variables.-
        if(settingsOpened){
            tmp = MeasureText("Mute", textSize);
            Button muteBtn = (Button){(Rectangle){screenHalfX-tmp/2, screenHalfY, SPACING+tmp, SPACING+textSize},
                                        "Mute", BLACK, (audioMuted)?GRAY:WHITE, tmp};
            if(CheckCollisionPointRec(mousePosition, muteBtn.rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                SetMasterVolume((audioMuted)?0.5: 0);
                audioMuted=!audioMuted;
            }
            BeginDrawing();
                ClearBackground(GREEN);
                DRAWBTN(muteBtn)
            EndDrawing();
            continue;
        }
        if(!gameStarted){
            tmp = MeasureText("Start Game", textSize);
            Button startBtn = (Button){(Rectangle){screenHalfX-tmp/2, screenHalfY, SPACING+tmp, SPACING+textSize},
                                        "Start Game", BLACK, WHITE, tmp};
            tmp = MeasureText("Settings", textSize);
            Button settingsBtn = (Button){(Rectangle){screenHalfX-tmp/2, screenHalfY+startBtn.rec.height+SPACING, SPACING+tmp, SPACING+textSize},
                                        "Settings", BLACK, WHITE, tmp};

            if(CheckCollisionPointRec(mousePosition, startBtn.rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                gameStarted = true;
                PlayMusicStream(music);
            }
            if(CheckCollisionPointRec(mousePosition, settingsBtn.rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                settingsOpened = true;
            }
            BeginDrawing();
                ClearBackground(GREEN);
                DRAWBTN(startBtn)
                DRAWBTN(settingsBtn)
            EndDrawing();
            continue;
        }
        // Game part HERE.
        // Update variables.
        if(ball.pos.x+ball.radius>screenWidth || ball.pos.x-ball.radius<0){
            ball.vel.x=-ball.vel.x;
        }
        if(ball.pos.y+ball.radius>screenHeight || ball.pos.y-ball.radius<0){
            ball.vel.y=-ball.vel.y;
        }

        ball.pos.x += ball.vel.x;
        ball.pos.y += ball.vel.y;
        //-Update variables.-
        UpdateMusicStream(music);
        BeginDrawing();
            ClearBackground(GRAY);
            DrawTextEx(GetFontDefault(), "Hello World!", (Vector2){screenHalfX-50, screenHalfY}, textSize, 1, BLACK);
            DrawCircleV(ball.pos, ball.radius*scale, ball.color);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
