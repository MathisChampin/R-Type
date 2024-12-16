# R-Type Project

This repository contains the structure for an R-Type project with a **client** and a **server**, each in its own directory. The project uses CMake to manage configuration and compilation.

## Project Structure

### ECS (Entity-Component-System)
The ECS architecture is used to manage game entities. It separates data (components) from logic (systems) to efficiently handle entities.

### Server
The server handles network communication and game state synchronization. It uses multiple threads to manage incoming and outgoing packets, ensuring consistent game state across clients.

### Client
The client is responsible for communicating with the server, sending player inputs, and rendering the game state received from the server.

## Build and Run Instructions

### Step 1: Build the project

To build the project, simply run the following command at the root of the repository:

```bash
make
```

### Step 2: Run the executables

After building the project, navigate to the `build` directory and then to the `client` and `server` directories to run the respective executables.

#### Run the Server

```bash
cd build/server
./r_type_server
```

#### Run the Client

```bash
cd build/client
./r_type_client
```