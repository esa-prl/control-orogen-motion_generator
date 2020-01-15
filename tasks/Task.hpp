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

namespace motion_generator{

    class Task : public TaskBase
    {
	friend class TaskBase;
    protected:

        base::commands::Motion2D motion_command;
        int N, commands_ptu;
        std::vector<MotionChange> motion;
        std::vector<double> commands_time, commands_translation, commands_rotation;
        std::vector<double> commands_locomotion_mode;
        bool not_started;
        base::Time startTime, currentTime;
        locomotion_switcher::LocomotionMode locomotion_mode;
        double commands_pan, commands_tilt;

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
>>>>>>> 4e4221141be9783d9b2f28fdb4cdb8a06f1cde23
}

#endif
