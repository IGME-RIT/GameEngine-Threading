Documentation Author: Niko Procopi 2020

This tutorial was designed for Visual Studio 2019
If the solution does not compile, retarget the solution
to a different version of the Windows SDK. If you do not
have any version of the Windows SDK, it can be installed
from the Visual Studio Installer Tool

AtlasEngine - Threading
Prerequisites
	Intro C tutorials, Basic OpenGL tutorials, and 
	physics tutorials are required before starting
	the engine series
	
With threading, we can attach code to the objects we build.
Right now, out of all the members in struct Thread, only
siblingThread and funcOnTick are used, just to start off simple.

Threading is not the same as multithreading. Multithreading is
where code runs on separate CPU processors in parallel, but 
"Threading" itself is where code is divided, but then runs 
sequentially (one by one).

When each thread is built, it must be added to what Naughty Dog
calls a "Thread Bucket" which is basically a linked list, so that
similar threads are grouped together (players with players, AIs 
with AIs, etc).

Also, globals.h was renamed to pch.h, it is now a precompiled header,
which makes compiling the game twice as fast as before. To learn more,
skip to 12:30 of this video, it explains everything about PCH
https://www.youtube.com/watch?v=eSI4wctZUto

With this system the following has been accomplished:
	
	- Threads and Instances can be attached to each other,
	meaning code can be indirectly "attached" to an instance,
	just like what we do with player.
	
	- By grouping similar threads together, like coin, we can
	count how many coins there are in the world by looping 
	through the list in player.cpp (press 'C' to count coins).
	This also allows us to access all threads without needing
	to save all pointers to all threads in a big array or vector
	
	- We can build a large number of Instances, and a large
	number of Threads, then have our engine automatically 
	draw all Instances, and execute all Threads, with a loop,
	without us needing to access pointers to the data.

Coming next:

	- Building "pool" systems, as Naughty Dog calls them,
	so that we can allocate and deallocate our Threads and Instances,
	without needing to undo allocations in the Stack Allocator.
	(next tutorial)
	
	- Coins will take advantage of threads, 
	by using threads for collisions
	(tutorial after next)
	