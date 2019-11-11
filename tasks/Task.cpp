/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include <base/commands/Joints.hpp>

using namespace motion_generator;

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

    start = true; 

    // initialize the motion vector
    //motion.resize(N);
    
    // test
    /* 
    motion.push_back(MotionChange()); motion[0] = {0.0, 0.0, 0.0, false};
    motion.push_back(MotionChange()); motion[1] = {2.0, 0.005, 0.0, false};
    motion.push_back(MotionChange()); motion[2] = {motion[1].time + 0.3, 0.01, 0.0, false};
    motion.push_back(MotionChange()); motion[3] = {motion[2].time + 0.3, 0.015, 0.0, false};
    motion.push_back(MotionChange()); motion[4] = {motion[3].time + 0.3, 0.02, 0.0, false};
    motion.push_back(MotionChange()); motion[5] = {motion[4].time + 0.3, 0.025, 0.0, false};
    motion.push_back(MotionChange()); motion[6] = {motion[5].time + 0.3, 0.03, 0.0, false};
    motion.push_back(MotionChange()); motion[7] = {motion[6].time + 0.3, 0.035, 0.0, false};
    motion.push_back(MotionChange()); motion[8] = {motion[7].time + 0.3, 0.04, 0.0, false};
    motion.push_back(MotionChange()); motion[9] = {motion[8].time + 0.3, 0.045, 0.0, false};
    motion.push_back(MotionChange()); motion[10] = {motion[9].time+ 0.3, 0.05, 0.0, false};
    motion.push_back(MotionChange()); motion[11] = {motion[10].time+0.3, 0.055, 0.0, false};
    motion.push_back(MotionChange()); motion[12] = {motion[11].time+0.3, 0.06, 0.0, false};
    motion.push_back(MotionChange()); motion[13] = {motion[12].time+10, 0.0, 0.0, false};
    N = motion.size();
    */ 

    // reverse test
     
    motion.push_back(MotionChange()); motion[0] = {0.0, 0.0, 0.0, false};
    motion.push_back(MotionChange()); motion[1] = {2.0,                  -0.005, 0.0, false};
    motion.push_back(MotionChange()); motion[2] = {motion[1].time + 0.3, -0.01, 0.0, false};
    motion.push_back(MotionChange()); motion[3] = {motion[2].time + 0.3, -0.015, 0.0, false};
    motion.push_back(MotionChange()); motion[4] = {motion[3].time + 0.3, -0.02, 0.0, false};
    motion.push_back(MotionChange()); motion[5] = {motion[4].time + 0.3, -0.025, 0.0, false};
    motion.push_back(MotionChange()); motion[6] = {motion[5].time + 0.3, -0.03, 0.0, false};
    motion.push_back(MotionChange()); motion[7] = {motion[6].time + 0.3, -0.035, 0.0, false};
    motion.push_back(MotionChange()); motion[8] = {motion[7].time + 0.3, -0.04, 0.0, false};
    motion.push_back(MotionChange()); motion[9] = {motion[8].time + 0.3, -0.045, 0.0, false};
    motion.push_back(MotionChange()); motion[10] = {motion[9].time+ 0.3, -0.05, 0.0, false};
    motion.push_back(MotionChange()); motion[11] = {motion[10].time+0.3, -0.055, 0.0, false};
    motion.push_back(MotionChange()); motion[12] = {motion[11].time+0.3, -0.06, 0.0, false};
    motion.push_back(MotionChange()); motion[13] = {motion[12].time+10, 0.0, 0.0, false};
    N = motion.size();
    

    /*
    motion.push_back(MotionChange()); motion[0] = {2.0, -0.06, 0.0, false};
    motion.push_back(MotionChange()); motion[1] = {12.0, 0.0, 0.0, false};
    */
    N = motion.size();
    
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

    // if first call of updateHook set the startTime
    if (start)
    {
        startTime = base::Time::now();
        start = false;
    }

    // update time (current = now - start)
    currentTime = base::Time::now() - startTime;

    for (int i = 0; i < N; i++)
    {
        // check if there is a command to be executed 
        if ( (currentTime.toSeconds() > motion[i].time) && (!motion[i].isExecuted) )
        {
            // read and write to output the motion command
            motion_command.translation = motion[i].translational_vel;
            motion_command.rotation = motion[i].rotational_vel;
            _motion_command.write(motion_command);
            motion[i].isExecuted = true;
            
            // write the timestamp of the motion command
            _motion_command_time.write(base::Time::now());

            std::cout << currentTime.toSeconds() << ": " 
                << "motion command sent = " << motion_command.translation << ","
                << motion_command.rotation << std::endl;
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
    // write the timestamp of the motion command
    _motion_command_time.write(base::Time::now());
}

void Task::stopHook()
{
    TaskBase::stopHook();

    // When the task is stopped, stop the rover
    motion_command.translation = 0.0;
    motion_command.rotation = 0.0;
    _motion_command.write(motion_command); 
    // write the timestamp of the motion command
    _motion_command_time.write(base::Time::now());
}

void Task::cleanupHook()
{
    TaskBase::cleanupHook();
}
