#ifndef PHYSICS_H
#define PHYSICS_H

#include <SDL2/SDL.h>

extern int WIDTH;
extern int HEIGHT;

// define a vector structure
typedef struct {
  float x, y;
} Vect2;

// define a rigid body structure
typedef struct {
  Vect2 position;
  Vect2 velocity;
  Vect2 acceleration;
  float mass;
  float radius;
} RigidBody;

// Function prototypes
void apply_gravity(RigidBody *body, float gravity);
void apply_force(RigidBody *body, Vect2 force);
void update_physics(RigidBody *body, float deltaTime);
void handle_collision(RigidBody *body1, RigidBody *body2);
int check_collision(RigidBody *body1, RigidBody *body2);

#endif
