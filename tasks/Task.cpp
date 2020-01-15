/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include <base/commands/Joints.hpp>

using namespace motion_generator;
using namespace locomotion_switcher;

Task::Task(std::string const& name) : TaskBase(name) {}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine) : TaskBase(name, engine) {}

Task::~Task() {}

bool Task::configureHook()
{
    if (!TaskBase::configureHook()) return false;

    // Initialize the motion_command message parameters
    motion_command.translation = 0.0;
    motion_command.rotation = 0.0;
    locomotion_mode = LocomotionMode::DRIVING;
    not_started = true;

    // Read the motion commands from the config file
    commands_time = _commandsTime.get();
    commands_translation = _commandsTranslation.get();
    commands_rotation = _commandsRotation.get();
    commands_locomotion_mode = _commandsLocomotionMode.get();

    // sanity check: empty vector
    if (commands_time.size() == 0 || commands_time.size() == 0 || commands_translation.size() == 0
        || commands_locomotion_mode.size() == 0)
    {
        std::cerr << "MOTION_GENERATOR ERROR: the fields (time, translation and rotation) of the "
                     "motion commands in the motion_generator::MotionCommands.yml file MUST all "
                     "have at least one element"
                  << std::endl;
        return false;
    }

    // sanity check: dimentions mismatch
    if (commands_time.size() != commands_translation.size()
        || commands_time.size() != commands_rotation.size()
        || commands_time.size() != commands_locomotion_mode.size())
    {
        std::cerr << "MOTION_GENERATOR ERROR: the fields (time, translation and rotation) of the "
                     "motion commands in the motion_generator::MotionCommands.yml file MUST be of "
                     "the same lenght"
                  << std::endl;
        return false;
    }

    N = commands_time.size();
    std::cout << "[Motion Generator: configureHook]"
              << "N=" << N << std::endl;
    // motion.resize(N);

    // initialize the MotionChange vector
    for (int i = 0; i < N; i++)
    {
        MotionChange motion_change;
        motion_change.time = commands_time[i];
        motion_change.translational_vel = commands_translation[i];
        motion_change.rotational_vel = commands_rotation[i];
        motion_change.is_executed = false;
        motion_change.locomotion_mode = (int)commands_locomotion_mode[i];
        motion.push_back(motion_change);
    }

    // MANUAL INITIALIZATIONS FOR TESTS PURPOSES
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
    /*
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
    */

    /*
    motion.push_back(MotionChange()); motion[0] = {2.0, -0.06, 0.0, false};
    motion.push_back(MotionChange()); motion[1] = {12.0, 0.0, 0.0, false};
    */
    N = motion.size();

    return true;
}

bool Task::startHook()
{
    if (!TaskBase::startHook()) return false;
    return true;
}

void Task::updateHook()
{
    TaskBase::updateHook();

    // if first call of updateHook set the startTime
    if (not_started)
    {
        startTime = base::Time::now();
        not_started = false;
    }

    // update time (current = now - start)
    currentTime = base::Time::now() - startTime;

    for (int i = 0; i < N; i++)
    {
        // check if there is a command to be executed
        if ((currentTime.toSeconds() > motion[i].time) && (!motion[i].is_executed))
        {
            // read the motion command
            motion_command.translation = motion[i].translational_vel;
            motion_command.rotation = motion[i].rotational_vel;

            // change locomotion mode for driving or wheelwalking
            if (motion[i].locomotion_mode == 1)
            {
                std::cout << "switched to DRIVING" << std::endl;
                locomotion_mode = LocomotionMode::DRIVING;
                _locomotion_mode.write(locomotion_mode);
            }
            else if (motion[i].locomotion_mode == 2)
            {
                std::cout << "switched to WHEEL WALKING" << std::endl;
                locomotion_mode = LocomotionMode::WHEEL_WALKING;
                _locomotion_mode.write(locomotion_mode);
            }

            // send the motion command
            _motion_command.write(motion_command);
            motion[i].is_executed = true;

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

    // When an error occurs, send ptu to zero pan and tilt
    _pan_command_out.write(0.0);
    _tilt_command_out.write(0.0);

    unsigned int microseconds = 5 * 10 ^ 6;
    usleep(microseconds);
}

void Task::stopHook()
{
    TaskBase::stopHook();

    std::cout << "motion_translator::stopHook: task stopped, stopping." << std::endl;

    // When the task is stopped, stop the rover
    motion_command.translation = 0.0;
    motion_command.rotation = 0.0;
    _motion_command.write(motion_command);
    // write the timestamp of the motion command
    _motion_command_time.write(base::Time::now());

    // When the task is stopped, send ptu to zero pan and tilt
    _pan_command_out.write(0.0);
    _tilt_command_out.write(0.0);

    std::this_thread::sleep_for(std::chrono::seconds(5));
}

void Task::cleanupHook() { TaskBase::cleanupHook(); }
