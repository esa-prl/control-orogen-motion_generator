/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef MOTION_GENERATOR_TASK_TASK_HPP
#define MOTION_GENERATOR_TASK_TASK_HPP
#include "motion_generator/TaskBase.hpp"
#include <base/commands/Joints.hpp>
#include "controldev/JoystickTaskBase.hpp"
#include <vector>


struct MotionChange
{
    double time;
    double translational_vel;
    double rotational_vel;
    bool isExecuted;
};

namespace motion_generator{

    class Task : public TaskBase
    {
	friend class TaskBase;
    protected:

        base::commands::Motion2D motion_command;

        int N; 
        std::vector<MotionChange> motion;

        bool pointTurn, start;
        base::Time startTime, currentTime;

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

