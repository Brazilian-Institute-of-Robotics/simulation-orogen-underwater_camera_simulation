/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"

using namespace base::samples::frame;
using namespace underwater_camera_simulation;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
{
}

Task::~Task()
{
}

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    if (! TaskBase::configureHook())
        return false;

    oceanEnvPlugin = new vizkit3d::Ocean();
    vizkit3dWorld->getWidget()->addPlugin(oceanEnvPlugin);
    vizkit3dWorld->getWidget()->setEnvironmentPlugin(oceanEnvPlugin);

    return true;
}

bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;


    /**
     * Apply the camera parameters
     */
    underwater_camera_simulation::CameraParams params = _camera_params.get();
    vizkit3dWorld->setCameraParams((params.width <= 0) ? 800 : params.width,
                                   (params.height <= 0) ? 600 : params.height,
                                   params.horizontal_fov,
                                   params.near,
                                   params.far);

    vizkit3dWorld->enableGrabbing();
    return true;
}
void Task::updateHook()
{
    TaskBase::updateHook();

    base::samples::RigidBodyState cameraPose;
    RTT::FlowStatus flow = _camera_pose.readNewest(cameraPose);
    if (flow == RTT::NoData)
        return;

    if (flow == RTT::NewData)
        vizkit3dWorld->setCameraPose(cameraPose);

    //grab the frame
    std::auto_ptr<Frame> frame(new Frame());
    vizkit3dWorld->grabFrame(*frame.get());
    frame->time = cameraPose.time;
    _frame.write(RTT::extras::ReadOnlyPointer<Frame>(frame.release()));
}

void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    vizkit3dWorld->disableGrabbing();
    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    //remove ocean plugin from memory
    if (oceanEnvPlugin){
        vizkit3dWorld->getWidget()->removePlugin(oceanEnvPlugin);
        delete oceanEnvPlugin;
        oceanEnvPlugin = NULL;
    }

    TaskBase::cleanupHook();
}


