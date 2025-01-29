#include "physics.h"
#include <math.h>

// Apply gravity to the rigid body
void apply_gravity(RigidBody *body, float gravity) {
  body->acceleration.y += gravity;
}

// Apply an external force to the rigid body
void apply_force(RigidBody *body, Vect2 force) {
  body->acceleration.x += force.x / body->mass;
  body->acceleration.y += force.y / body->mass;
}

// Update the physics state (pos, velocity, etc...)
void update_physics(RigidBody *body, float deltaTime) {
  body->velocity.x += body->acceleration.x * deltaTime;
  body->velocity.y += body->acceleration.y * deltaTime;

  body->position.x += body->velocity.x * deltaTime;
  body->position.y += body->velocity.y * deltaTime;

  // Boundry collisions
  if (body->position.x - body->radius < 0) {
    body->position.x = body->radius;
    body->velocity.x = -body->velocity.x;
  }
  if (body->velocity.x + body->radius > WIDTH) {
    body->position.x = WIDTH - body->radius;
    body->velocity.x = -body->velocity.x;
  }
  if (body->position.y - body->radius < 0) {
    body->position.y = body->radius;      // Keep object inside window
    body->velocity.y = -body->velocity.y; // Reverse velocity to bounce
  }
  if (body->position.y + body->radius > HEIGHT) {
    body->position.y = HEIGHT - body->radius; // Keep object inside window
    body->velocity.y = -body->velocity.y;     // Reverse velocity to bounce
  }

  // Reset acceleration for the next frame
  body->acceleration.x = 0;
  body->acceleration.y = 0;
}

// Check for collisions between two circular rigid bodies
int check_collision(RigidBody *body1, RigidBody *body2) {
  float dx = body1->position.x - body2->position.x;
  float dy = body1->position.y - body2->position.y;
  float distance = sqrt(dx * dx + dy * dy);

  return distance < (body1->radius + body2->radius);
}

// Handle collisions between two rigid bodies
void handle_collision(RigidBody *body1, RigidBody *body2) {
  if (check_collision(body1, body2)) {
    // Simple collision response (elastic)
    float dx = body1->position.x - body2->position.x;
    float dy = body1->position.y - body2->position.y;
    float normal_x = dx / sqrt(dx * dx + dy * dy);
    float normal_y = dy / sqrt(dx * dx + dy * dy);

    // Reflect velocities
    float relative_velocity_x = body1->velocity.x - body2->velocity.x;
    float relative_velocity_y = body1->velocity.y - body2->velocity.y;
    float dot_product =
        (relative_velocity_x * normal_x + relative_velocity_y * normal_y);

    if (dot_product > 0) {
      float bounce = 1.0; // Perfect elastic collision
      body1->velocity.x -= 2 * dot_product * normal_x * bounce;
      body1->velocity.y -= 2 * dot_product * normal_y * bounce;
      body1->velocity.x += 2 * dot_product * normal_x * bounce;
      body1->velocity.y += 2 * dot_product * normal_y * bounce;
    }
  }
}
