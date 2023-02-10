# Ecosystem Simulation
Howdy 🤠? This was supposed to be a collection of tools for making games but it has become a quest to develop an ecosystem simulation.

The tools are being developed in a modular and reusable manner. The pieces that creates the sim exist within a separate project within the solution. 

Here are the current reusable features:
- Entity Management
    - Game loop
    - ECS (without S, more like the Unity way)
- Resource Management
- Event System
- Decision System
    - Traits, Needs, Actions, and Rewards 
    - State machine
    - Behavior scheduler
- General Tools 
    - Templated/Macro-wrapped design patterns
        - Object Pool
        - Singleton
        - Blackboard
    - Timer
    - Chrono utilities
    - Logger
    - Function arguments packer/unpacker that extends the raw ability of c++ 

The ecosystem simulation has a UI that uses ImGui. The systems mentioned previously, are connected to the ui using a ImGui layer port. ImGui layer port has multiple secondary ports connected to it such as entity manager port and actions list port. The ports are responsible for literally "porting" the system to the interface and rendering their own data. The ImGui layer port calls the render function of each secondary port in each tick.

In order for the ports to communicate with each other, there are two ways implemented by far: blackboard and prompt system. The prompt system bascially consists of a bus shared between ports through which they can send prompts with payloads to each other. Blackboard is basically a shared data pool that ports subscribe to and get notified whenever blackboard gets updated.

I will change the backend of ImGui to SDL2 soon because I want to render the entities in the world space. Currently the backend of ImGui is only with OpenGL2 and I don't know anything about OpenGL.