/**
 * @brief Orbital simulation
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

#ifndef ORBITALSIM_H
#define ORBITALSIM_H

#include "raylib.h"
#include "raymath.h"

/**
 * @brief Orbital body definition
 */
typedef struct OrbitalBody
{
    char name[100];
    float mass;
    float radius;
    Color color;
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

}OrbitalBody_t;

/**
 * @brief Orbital simulation definition
 */
typedef struct OrbitalSim
{
    float timestep; //Timesteps used to calculate object physics
    float total_time; //Time since the simulation started
    int bodies_count;
    OrbitalBody *pBodies;

}OrbitalSim_t;

/**
 * @brief Creates orbital simulation
 * @param timeStep timestep to be utilized for physics calculations in the simulation
 */
OrbitalSim_t *constructOrbitalSim(float timeStep);

/**
 * @brief Destroys orbital simulation
 * @param sim simulation to destroy
 */
void destroyOrbitalSim(OrbitalSim_t *sim);

/**
 * @brief Updates the simulation by a tick
 * @param sim simulation to update
 */
void updateOrbitalSim(OrbitalSim_t *sim);

#endif