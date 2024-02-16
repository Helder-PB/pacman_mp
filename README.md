
# pacman_mp

Remake of the multilplayer pacman game from my old group project in PSis.

I decided to make this project because:

- I want to explore more the capabilities of my ESP32;
- I wanted to implement one of my favourite group projects with concepts and skills that I lacked at the time of development;
- I like embedded systems;
- I like automation and electronics;

The final goal is a more efficient implementation of the game to allow the creation of a small network of ESP32 to play a multiplayer pacman (like a classic gameboy in a local network).

## Concepts

This project requires knowledge in:

- Programming in C
- Efficient memory usage
- Valgrind and gdb usage
- Multithreading
- Networking (sockets, pipes)
- FreeRTOs

## Stages of development

### * Implementation in a UNIX desktop (CURRENT)

The game must at least work in a computer, having in mind efficiency.

### * Implementation in a desktop - ESP32 network

This stage will require the biggest effort in optimization. Here the relation between the designed arquitecture and the hardware will expose the main bottlenecks.
Here the main effort will be in:

- memory usage
- processing power
- best FreeRTOs usage

### * Implementation only in FreeRTOs usage

Essentially the previous stage but without the desktop component as a server or client.

### * Hardware choosal

Mainly the batteries, display and controls.
This stage will focus on the best equilibrium in affordability, performance and usability.
