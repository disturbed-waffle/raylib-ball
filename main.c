#include <raylib.h>
#include <time.h>
#include <raymath.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){
    const int window_height = 720; 
    const int window_width = 1280;
    InitWindow(window_width,window_height, "Your mom");
    SetTargetFPS(120);
    // Circle
    float x = 400.0, y = 300.0;
    int radius = 80;
    float mass = 10.0;
    float dampening = -0.6;

    float gravity = 490.0; // scale of 1m = 50 pixels
    float impulse = 1e5;
    float impulse_time = 0.1;
    float cooldown = 2.0;
    int can_force = 1;

    const char *text = "BALL";
    int font_size = 30;


    Vector2 pos = {x,y};
    Vector2 velocity = Vector2Zero();
    Vector2 accel = {0,gravity};
    
    double force_start_time;
    double cooldown_start_time; // Goofy
    
    while(!WindowShouldClose()){
        BeginDrawing();
        {   
            // FPS
            float dt = GetFrameTime();
            char fps[8];
            sprintf(fps,"%d",GetFPS());
            SetWindowTitle(fps);

            // Check force Timers
            if (!can_force){
                if (GetTime()-force_start_time >= impulse_time){
                    force_start_time = 0.0;
                    accel.x = 0, accel.y = gravity;
                }
                if (GetTime()-cooldown_start_time >= cooldown){
                    can_force = 1;
                }
            }

            // Force
            if ((IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))&& can_force){
                gravity = 490;
                force_start_time = GetTime();
                cooldown_start_time = GetTime();
                // direction to mouse
                Vector2 dir = Vector2Subtract(GetMousePosition(),pos);
                dir = Vector2Normalize(dir);

                Vector2 force = Vector2Scale(dir, impulse);
                accel = Vector2Add(accel, Vector2Scale(force,1.0/mass));
                can_force = 0;
            }
            velocity = Vector2Add(velocity, Vector2Scale(accel,dt));
            
            // Colision
            if (pos.x+radius >= window_width && velocity.x > 0) velocity.x *= dampening;
            if (pos.x-radius <= 0 && velocity.x < 0) velocity.x *= dampening;
            if (pos.y+radius >= window_height && velocity.y > 0) velocity.y *= dampening;
            if (pos.y-radius <= 0 && velocity.y < 0) velocity.y *= dampening;
            
            // Friction and Ground
            if (pos.y+radius >= window_height - 3 && abs(velocity.y) < 20){
                int friction = 80;
                velocity.x = velocity.x>0 ? velocity.x - friction*dt : velocity.x + friction*dt;
                velocity.y = abs(velocity.y) < 4 ? 0 : velocity.y;
                gravity = 0;
            }

            pos.x += velocity.x*dt;
            pos.y += velocity.y*dt;     
            
            // Drawing
            char debug[64]; sprintf(debug, "speed\n\n%.0f", Vector2Length(velocity));
            DrawText(debug,5,5,32,WHITE);
            DrawText("Cooldown",window_width-MeasureText("Cooldown",32)-5,5,32,WHITE);
            DrawRing((Vector2){window_width-80,80}, 20,40, 0,300,20,ORANGE);

            Vector2 mouse = GetMousePosition();
            DrawLineEx(pos,mouse,3,WHITE);
            
            DrawCircle((int) pos.x,(int) pos.y, radius, RED);
            int offset = MeasureText(text, font_size)/2;
            DrawText(text,pos.x-offset,pos.y,font_size,WHITE); 

            ClearBackground(DARKPURPLE);
           
        }
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}