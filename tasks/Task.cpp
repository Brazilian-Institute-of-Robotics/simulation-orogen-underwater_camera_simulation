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

    vizkit3dWorld->getWidget()->addPlugin(oceanEnvPlugin);
    vizkit3dWorld->getWidget()->setEnvironmentPlugin(oceanEnvPlugin);

    vizkit3dWorld->postEnableGrabbing();

    //it is necessary call notifyEvents to process GUI events
    vizkit3dWorld->notifyEvents();

    //Init the buffer
    Frame *frame = vizkit3dWorld->grabFrame();
    buffer.init(*frame);

    return true;
}
void Task::updateHook()
{
    TaskBase::updateHook();

    base::samples::RigidBodyState cameraPose;
    while (_camera_pose.read(cameraPose) == RTT::NewData) {
        vizkit3dWorld->setTransformation(cameraPose);

        /**
         * set the camera position
         * if the gui is showing and camera manipulator is enable the
         * camera pose is set using the user inputs
         */
        if (!_show_gui.get() || !_enable_camera_manipulator.get()) {
            //change the camera position
            vizkit3dWorld->setCameraPose(cameraPose);
        }
    }

    //grab the frame
    Frame *frame = vizkit3dWorld->grabFrame();
    buffer.init(*frame);

    //write in the output frame port
    cameraFrame.reset(&buffer);
    _frame.write(cameraFrame);
}

void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    //disable grabbing
    vizkit3dWorld->postDisableGrabbing();
    vizkit3dWorld->notifyEvents();
    TaskBase::stopHook();
}
void Task::cleanupHook()
{

    //remove ocean plugin from memory
    if (oceanEnvPlugin){
        delete oceanEnvPlugin;
        oceanEnvPlugin = NULL;
    }

    TaskBase::cleanupHook();
}
