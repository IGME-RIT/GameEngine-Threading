#include "pch.h"

struct Global global;

int main()
{
    printf("Globals: %d bytes\n", sizeof(global));

    // this should be the one and only "malloc"
    void* mempackRamData = malloc(ramSize);

    // initialize mempack for RAM
    MEMPACK_Init(&global.ramPack, mempackRamData, ramSize, "ram");

    // create a window, create context,
    // create GPU Mempacks, etc
    InitOpenGL();

    Sprite* manSprite = Sprite_Init("Assets/man.bmp");
    Sprite* coinSprite = Sprite_Init("Assets/coin.bmp");

    printf("Allocating game objects\n");

    Instance* manInst1 = (Instance*)MEMPACK_AllocMem(&global.ramPack, sizeof(Instance), "manInst");
    manInst1->sprite = manSprite;

    Thread* manThread = Thread_Init(TH_PLAYER, Player_OnTick);
    
    // link instance and thread
    manThread->inst = manInst1;
    manInst1->thread = manThread;

    // draw person on top (small depth)
    manInst1->depth = 0.1f;
    manInst1->posX = -0.5f;
    manInst1->posY = -0.5f;
    manInst1->scaleX = 0.00075f;
    manInst1->scaleY = 0.00075f;
    
    for (int i = 0; i < 5; i++)
    {
        // Notice now we dont need an array,
        // because threads are linked, so we
        // can lose the pointers and still 
        // access the data later when we need it
        Instance* in = (Instance*)MEMPACK_AllocMem(&global.ramPack, sizeof(Instance), "coinInst");

        // coin doesn't need an update function,
        // but we will use it's onCollide pointer
        // in future tutorials
        Thread* th = Thread_Init(TH_COIN, nullptr);

        in->sprite = coinSprite;

        // link instance and thread
        th->inst = in;
        in->thread = th;

        // draw coins on bottom (larger depth)
        in->depth = 0.2f; 
        in->posX = 0.5f;
        in->posY = -0.5f + 0.2f * i;
        in->scaleX = 0.002f;
        in->scaleY = 0.002f;
    }

    // timer variables
    clock_t start;
    clock_t end;

    // initialize time
    start = clock();


    // render loop
    // -----------
    while (!glfwWindowShouldClose(global.window))
    {
        // measure elapsed time per frame
        end = clock();
        global.elapsedTime = (end - start) / 1000.0f;
        start = clock();

        // Update controller "hold" variable
        glfwPollEvents();

        // Determine Tap and Release
        Input_ProcessState();

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw all instances and run all 
        // threads, at the same time

        // Problem #1, what if you want to draw
        // instances that have no threads. 
        // That will be solved in the next 
        // tutorial where we have a "Pool"

        // Problem #2, good engines separate
        // gameplay code from rendering code,
        // That will be solved with a "Pool"
        // of Instance and a "Pool" of Thread,
        // in the next tutorial

        for (int i = 0; i < TH_NUM_TYPES; i++)
        {
            // get first member of each thread bucket
            Thread* th = global.threadBucket[i];
            while (th != nullptr)
            {
                if (th->funcOnTick != nullptr)
                {
                    // execute thread's function,
                    // passing itself as a parameter
                    th->funcOnTick(th);
                }

                // draw member
                Instance_Draw(th->inst);

                // go to next thread
                th = th->siblingThread;
            }
        }

        // update swapchain
        glfwSwapBuffers(global.window);
    }

    // erase all allocated data
    MEMPACK_Clean(&global.ramPack);

    // erase resources
    delete mempackRamData;
    mempackRamData = nullptr;

    CleanOpenGL();

    // end program
    return 0;
}