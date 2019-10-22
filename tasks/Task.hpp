/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef MOTION_GENERATOR_TASK_TASK_HPP
#define MOTION_GENERATOR_TASK_TASK_HPP
#include "locomotion_switcher/locomotion_switcherTypes.hpp"
#include "motion_generator/TaskBase.hpp"
#include <base/commands/Joints.hpp>
#include "controldev/JoystickTaskBase.hpp"


struct MotionChange
{
    double time;
    double value;
    int descr;
    bool exec;
};

namespace motion_generator{

    class Task : public TaskBase
    {
	friend class TaskBase;
    protected:

        base::commands::Motion2D motion_command;

        /*double motion[3][3] = {
                { 0, 0, 1, false },
                { 1, 0.03, 1, false },
                { 167.67, 0, 1, false },
        };*/
        static const int N = 3;
        MotionChange motion[N] = {
            { 0.0, 0.0, 1, false},
            { 1.0, 0.03, 1, false},
            { 10.0, 0.0, 1, false}};
            //{ 167.6667, 0.0, 1, false}};

        bool pointTurn, start;
        locomotion_switcher::LocomotionMode locomotion_mode;
        base::Time startTime, currentTime;

    public:
        /** TaskContext constructor for Task
         */
        Task(std::string const& name = "motion_generator::Task");
        Task(std::string const& name, RTT::ExecutionEngine* engine);

        /** Default deconstructor of Task
         */
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

