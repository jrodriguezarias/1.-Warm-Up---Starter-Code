/**
 * @brief Implements an orbital simulation view
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

#include <time.h>

#include "View.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

/**
 * @brief Converts a timestamp (number of seconds since 1/1/2022)
 *        to an ISO date ("YYYY-MM-DD")
 *
 * @param timestamp the timestamp
 * @return The ISO date (a raylib string)
 */
const char *getISODate(float timestamp)
{
    // Timestamp epoch: 1/1/2022
    struct tm unichEpochTM = {0, 0, 0, 1, 0, 122};

    // Convert timestamp to UNIX timestamp (number of seconds since 1/1/1970)
    time_t unixEpoch = mktime(&unichEpochTM);
    time_t unixTimestamp = unixEpoch + (time_t)timestamp;

    // Returns ISO date
    struct tm *localTM = localtime(&unixTimestamp);
    return TextFormat("%04d-%02d-%02d",
                      1900 + localTM->tm_year, localTM->tm_mon + 1, localTM->tm_mday);
}

/**
 * @brief Constructs an orbital simulation view
 *
 * @param fps Frames per second for the view
 * @return The view
 */
View *constructView(int fps)
{
    View *view = new View();

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "EDA Orbital Simulation");
    SetTargetFPS(fps);
    DisableCursor();

    view->camera.position = {10.0f, 10.0f, 10.0f};
    view->camera.target = {0.0f, 0.0f, 0.0f};
    view->camera.up = {0.0f, 1.0f, 0.0f};
    view->camera.fovy = 45.0f;
    view->camera.projection = CAMERA_PERSPECTIVE;

    return view;
}

/**
 * @brief Destroys an orbital simulation view
 *
 * @param view The view
 */
void destroyView(View *view)
{
    CloseWindow();

    delete view;
}

/**
 * @brief Should the view still render?
 *
 * @return Should rendering continue?
 */
bool isViewRendering(View *view)
{
    return !WindowShouldClose();
}

/**
 * @brief Renders an orbital simulation
 *
 * @param view The view
 * @param sim The orbital sim
 */
void renderView(View *view, OrbitalSim *sim)
{
    UpdateCamera(&view->camera, CAMERA_FREE);

    BeginDrawing();
    
    ClearBackground(BLACK);
    BeginMode3D(view->camera);

    // 3D Drawing

    int i;
    for(i = 0; i < sim->bodies_count; i++){
        if(i < sim->bodies_count - sim->asteroid_count){
            DrawSphere(Vector3Scale(sim->pBodies[i].position, 1E-11), 0.005F * logf(sim->pBodies[i].radius), sim->pBodies[i].color);
        }
        DrawPoint3D(Vector3Scale(sim->pBodies[i].position, 1E-11),sim->pBodies[i].color);
    }
    
    DrawGrid(10, 10.0f);
    EndMode3D();
    
    // 2D Drawing

    DrawFPS(5,700);
    DrawText(getISODate(sim->total_time), 975, 675, 50, WHITE);

    EndDrawing();
}
