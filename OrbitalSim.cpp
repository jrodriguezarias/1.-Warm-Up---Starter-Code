/**
 * @brief Orbital simulation
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

// Enables M_PI #define in Windows
#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "OrbitalSim.h"
#include "ephemerides.h"

#define GRAVITATIONAL_CONSTANT 6.6743E-11F
#define ASTEROIDS_MEAN_RADIUS 4E11F

/**
 * @brief Gets a uniform random value in a range
 *
 * @param min Minimum value
 * @param max Maximum value
 * @return The random value
 */
float getRandomFloat(float min, float max)
{
    return min + (max - min) * rand() / (float)RAND_MAX;
}

/**
 * @brief Configures an asteroid
 *
 * @param body An orbital body
 * @param centerMass The mass of the most massive object in the star system
 */
void configureAsteroid(OrbitalBody *body, float centerMass)
{
    // Logit distribution
    float x = getRandomFloat(0, 1);
    float l = logf(x) - logf(1 - x) + 1;

    // https://mathworld.wolfram.com/DiskPointPicking.html
    float r = ASTEROIDS_MEAN_RADIUS * sqrtf(fabsf(l));
    float phi = getRandomFloat(0, 2.0F * (float)M_PI);

    // Surprise!
    // phi = 0;

    // https://en.wikipedia.org/wiki/Circular_orbit#Velocity
    float v = sqrtf(GRAVITATIONAL_CONSTANT * centerMass / r) * getRandomFloat(0.6F, 1.2F);
    float vy = getRandomFloat(-1E2F, 1E2F);

    // Fill in with your own fields:
    // body->mass = 1E12F;  // Typical asteroid weight: 1 billion tons
    // body->radius = 2E3F; // Typical asteroid radius: 2km
    // body->color = GRAY;
    // body->position = {r * cosf(phi), 0, r * sinf(phi)};
    // body->velocity = {-v * sinf(phi), vy, v * cosf(phi)};
}

/**
 * @brief Constructs an orbital simulation
 *
 * @param float The time step
 * @return The orbital simulation
 */
OrbitalSim_t *constructOrbitalSim(float timeStep)
{
    int bodyCount = 9;
    OrbitalBody_t * Bodies = new OrbitalBody_t[bodyCount];

   int i,j;

   //Copying the solarSystem to an array of OrbitalBodys
    for(j = 0; j < bodyCount; j++){
        strcpy(Bodies[j].name,solarSystem[j].name);
        Bodies[j].mass = solarSystem[j].mass;
        Bodies[j].radius = solarSystem[j].radius;
        Bodies[j].color = solarSystem[j].color;
        Bodies[j].position = solarSystem[j].position;
        Bodies[j].velocity = solarSystem[j].velocity;
    }
    
    OrbitalSim_t *Simulation = new OrbitalSim_t({timeStep,0,bodyCount,Bodies});
    
    return Simulation; // This should return your orbital sim
}

/**
 * @brief Destroys an orbital simulation
 */
void destroyOrbitalSim(OrbitalSim_t *sim)
{
    delete[] sim;
    delete[] sim->pBodies;
}

/**
 * @brief Simulates a timestep
 *
 * @param sim The orbital simulation
 */
void updateOrbitalSim(OrbitalSim_t *sim)
{
    //Acceleration Calculations
   
    int i,j;
    for(i = 0; i < sim->bodies_count; i++){
        Vector3 F = Vector3Zero();
        for(j = 0; j < sim->bodies_count; j++){
            if(i!=j){
            double norma = Vector3Distance(sim->pBodies[i].position, sim->pBodies[j].position); 
            float scalar = -GRAVITATIONAL_CONSTANT * sim->pBodies[i].mass * sim->pBodies[j].mass / (norma * norma); 
            Vector3 F_ij = Vector3Scale(Vector3Subtract(sim->pBodies[i].position, sim->pBodies[j].position) , scalar / norma);
            F = Vector3Add(F,F_ij);
            }
        }
        sim->pBodies[i].acceleration = Vector3Add(sim->pBodies[i].acceleration, Vector3Scale(F,1/(sim->pBodies[i].mass)));
    }
    

    //Velocity and Position Calculations

    for(i = 0; i < sim->bodies_count; i++){
        sim->pBodies[i].velocity = Vector3Add(sim->pBodies[i].velocity, Vector3Scale(sim->pBodies[i].acceleration, sim->timestep));
        sim->pBodies[i].position = Vector3Add(sim->pBodies[i].position, Vector3Scale(sim->pBodies[i].velocity, sim->timestep));
    }

    sim->total_time += sim->timestep;
}
