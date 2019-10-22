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

    //std::cout << "[motion_generator] UpdateHook" << std::endl;
    
    if (start)
    {
        startTime = base::Time::now();
        start = false;
    }

    // update time (current = now - start)
    currentTime = base::Time::now() - startTime;

    // check if there is a command to be exec: 
    for (int i = 0; i < N; i++)
    {
        /*
        std::cout << "currenttime=" << currentTime.toSeconds() << std::endl;
        std::cout << "motiontime=" << motion[i].time << std::endl;
        std::cout << "motionexec=" << motion[i].exec << std::endl;
        std::cout << "if1=" << (currentTime.toSeconds() > motion[i].time)  << std::endl;
        std::cout << "if2=" << (!motion[i].exec) << std::endl;
        */
        if ( (currentTime.toSeconds() > motion[i].time) && (!motion[i].exec) )
        {
            // update motion_command
            switch (motion[i].descr)
            {
                case 1 : motion_command.translation = motion[i].value;
                         break;
                case 2 : motion_command.rotation = motion[i].value;
                         break;
            }
            // write motion command port
            _motion_command.write(motion_command);
            std::cout << currentTime.toSeconds() << ": " << "motion command sent = " << motion_command.translation << ","
                << motion_command.rotation << std::endl;
            // set exec to true
            motion[i].exec = true;
        }
    }
    std::cout << std::endl;
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
