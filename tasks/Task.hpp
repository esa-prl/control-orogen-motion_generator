/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef MOTION_GENERATOR_TASK_TASK_HPP
#define MOTION_GENERATOR_TASK_TASK_HPP
#include <base/commands/Joints.hpp>
#include <chrono>
#include <thread>
#include <vector>
#include "controldev/JoystickTaskBase.hpp"
#include "locomotion_switcher/locomotion_switcherTypes.hpp"
#include "motion_generator/TaskBase.hpp"

struct MotionChange
{
    double time;
    double translational_vel;
    double rotational_vel;
    int locomotion_mode;
    bool is_executed;
};

namespace motion_generator
{

class Task : public TaskBase
{
    friend class TaskBase;

  protected:
    base::commands::Motion2D motion_command;
    int N;
    std::vector<MotionChange> motion;
    std::vector<double> commands_time, commands_translation, commands_rotation;
    std::vector<double> commands_locomotion_mode;
    bool not_started;
    base::Time startTime, currentTime;
    locomotion_switcher::LocomotionMode locomotion_mode;

  public:
    Task(std::string const& name = "motion_generator::Task");
    Task(std::string const& name, RTT::ExecutionEngine* engine);

    ~Task();

    bool configureHook();
    bool startHook();
    void updateHook();
    void errorHook();
    void stopHook();
    void cleanupHook();
};
}

#endif
