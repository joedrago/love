/**
* Copyright (c) 2006-2012 LOVE Development Team
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
**/

#include "Thread.h"

namespace love
{
namespace thread
{
namespace sdl
{
Thread::Thread(Threadable *t)
	: t(t)
	, running(false)
	, thread(0)
{
}

Thread::~Thread()
{
	if (!running) // Clean up handle
		wait();
	/*
	if (running)
		wait();
	FIXME: Needed for proper thread cleanup
	*/
}

bool Thread::start()
{
	Lock l(mutex);
	if (running)
		return false;
	if (thread) // Clean old handle up
		SDL_WaitThread(thread, 0);
	thread = SDL_CreateThread(thread_runner, this);
	running = (thread != 0);
	return running;
}

void Thread::wait()
{
	mutex.lock();
	if (!thread)
		return;
	mutex.unlock();
	SDL_WaitThread(thread, 0);
	Lock l(mutex);
	running = false;
	thread = 0;
}

void Thread::kill()
{
	Lock l(mutex);
	if (!running)
		return;
	SDL_KillThread(thread);
	SDL_WaitThread(thread, 0);
	running = false;
	thread = 0;
}

int Thread::thread_runner(void *data)
{
	Thread *self = (Thread *) data; // some compilers don't like 'this'
	self->t->threadFunction();
	Lock l(self->mutex);
	self->running = false;
	return 0;
}
} // sdl
} // thread
} // love
