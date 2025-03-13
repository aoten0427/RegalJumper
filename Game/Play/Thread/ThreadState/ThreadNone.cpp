#include"pch.h"
#include"ThreadNone.h"

ThreadNone::ThreadNone(ThreadStateMachine* machine, Thread* thread) :ThreadState(machine, thread)
{
}

void ThreadNone::PreUpdate()
{
}

void ThreadNone::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void ThreadNone::PostUpdate()
{
}
