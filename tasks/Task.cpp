/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include <base/commands/Joints.hpp>

using namespace motion_generator;
using namespace locomotion_switcher;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine): 
    TaskBase(name, engine)
{
}


Task::~Task()
{
}


bool Task::configureHook()
{
    if (! TaskBase::configureHook())
        return false;

    // Initialize the motion_command message parameters
    motion_command.translation = 0.0;
    motion_command.rotation = 0.0;

    pointTurn = false;

    locomotion_mode = LocomotionMode::DRIVING;

    start = true; 

    return true;
}

bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;
    return true;
}

void Task::updateHook()
{
    TaskBase::updateHook();

    if (start)
    {
        startTime = base::Time::now();
        start = false;
    }

    // update time (current = now - start)
    currentTime = base::Time::now() - startTime;

    for (int i = 0; i < N; i++)
    {
        // check if there is a command to be exec: 
        if ( (currentTime.toSeconds() > motion[i].time) && (!motion[i].exec) )
        {
            switch (motion[i].descr)
            {
                case 1 : motion_command.translation = motion[i].value;
                         break;
                case 2 : motion_command.rotation = motion[i].value;
                         break;
            }

            _motion_command.write(motion_command);
            std::cout << currentTime.toSeconds() << ": " << "motion command sent = " << motion_command.translation << ","
                << motion_command.rotation << std::endl;
            motion[i].exec = true;
        }
    }
}

void Task::errorHook()
{
    TaskBase::errorHook();

    // Inform user about error
    std::cout << "motion_translator::errorHook: Error encountered, stopping." << std::endl;

    // When an error occurs, stop the rover
    motion_command.translation = 0.0;
    motion_command.rotation = 0.0;
    _motion_command.write(motion_command);

}

void Task::stopHook()
{
    TaskBase::stopHook();

    // When the task is stopped, stop the rover
    motion_command.translation = 0.0;
    motion_command.rotation = 0.0;
    _motion_command.write(motion_command); 

}

void Task::cleanupHook()
{
    TaskBase::cleanupHook();
}
