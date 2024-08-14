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
    float timestep;
    int bodies_count;
    OrbitalBody *pBodies;

}OrbitalSim_t;

/**
 * @brief Creates orbital simulation
 * @param timeStep timestep to be utilized for physics calculations in the simulation
 */
OrbitalSim_t *constructOrbitalSim(float timeStep);


void destroyOrbitalSim(OrbitalSim_t *sim);

void updateOrbitalSim(OrbitalSim_t *sim);

#endif