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
    /**
     * Apply the camera parameters
     */
    underwater_camera_simulation::CameraParams params = _camera_params.get();

    if (! TaskBase::configureHook())
        return false;

    vizkit3d::OceanParameters ocean_params = mapOceanParameters(_ocean_params.get());
    oceanEnvPlugin = new vizkit3d::Ocean(ocean_params);

    vizkit3dWorld->getWidget()->addPlugin(oceanEnvPlugin);
    vizkit3dWorld->getWidget()->setEnvironmentPlugin(oceanEnvPlugin);

    vizkit3dWorld->setCameraParams(_width.get(),
                                   _height.get(),
                                   params.horizontal_fov,
                                   params.near,
                                   params.far);

    return true;
}

bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;


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

vizkit3d::OceanParameters Task::mapOceanParameters(const OceanParameters& ocean_params) const 
{
    vizkit3d::OceanParameters viz_ocean_params;

    viz_ocean_params.surfDirty = ocean_params.surfDirty;
    viz_ocean_params.surfEndless = ocean_params.surfEndless;
    viz_ocean_params.surfWaveScale = ocean_params.surfWaveScale;
    viz_ocean_params.surfDepth = ocean_params.surfDepth;
    viz_ocean_params.surfWindDirection = vector2DToQVector2D(ocean_params.surfWindDirection);
    viz_ocean_params.surfWindSpeed = ocean_params.surfWindSpeed;
    viz_ocean_params.surfReflectionDamping = ocean_params.surfReflectionDamping;
    viz_ocean_params.surfIsChoppy = ocean_params.surfIsChoppy;
    viz_ocean_params.surfChoppyFactor = ocean_params.surfChoppyFactor;
    viz_ocean_params.surfCrestFoam = ocean_params.surfCrestFoam;
    viz_ocean_params.surfCrestFoamHeight = ocean_params.surfCrestFoamHeight;
    viz_ocean_params.surfFoamBottomHeight = ocean_params.surfFoamBottomHeight;
    viz_ocean_params.surfFoamTopHeight = ocean_params.surfFoamTopHeight;

    viz_ocean_params.sceneDirty = ocean_params.sceneDirty;
    viz_ocean_params.airFogColor = vector3DToQColor(ocean_params.airFogColor);
    viz_ocean_params.airFogDensity = ocean_params.airFogDensity;
    viz_ocean_params.sunPosition = vector3DToQVector3D(ocean_params.sunPosition); 
    viz_ocean_params.sunDiffuseColor = vector3DToQColor(ocean_params.sunDiffuseColor);
    viz_ocean_params.uwFogColor = vector3DToQColor(ocean_params.uwFogColor);
    viz_ocean_params.uwFogDensity = ocean_params.uwFogDensity;
    viz_ocean_params.uwAttenuation = vector3DToQVector3D(ocean_params.uwAttenuation);
    viz_ocean_params.uwDiffuseColor = vector3DToQColor(ocean_params.uwDiffuseColor);
    viz_ocean_params.glareAttenuation = ocean_params.glareAttenuation;

    viz_ocean_params.reflections = ocean_params.reflections;
    viz_ocean_params.refractions = ocean_params.refractions;
    viz_ocean_params.heightmap = ocean_params.heightmap;
    viz_ocean_params.godRays = ocean_params.godRays;
    viz_ocean_params.silt = ocean_params.silt;
    viz_ocean_params.underwaterDOF = ocean_params.underwaterDOF;
    viz_ocean_params.underwaterScattering = ocean_params.underwaterScattering;
    viz_ocean_params.distortion = ocean_params.distortion;
    viz_ocean_params.glare = ocean_params.glare;
    
    return viz_ocean_params;
}

QColor Task::vector3DToQColor(const base::Vector3d& vector) const
{
    std::cout << "vectorToColor " << vector[0] << " | " << vector[1] << " | " << vector[2] << std::endl;
    QColor qtcolor(vector[0], vector[1], vector[2]);
    return qtcolor;
}

QVector3D Task::vector3DToQVector3D(const base::Vector3d& vector) const
{
    std::cout << "vectorToVector3D " << vector[0] << " | " << vector[1] << " | " << vector[2] << std::endl;
    QVector3D qtvector3d(vector[0], vector[1], vector[2]);
    return qtvector3d;
}

QVector2D Task::vector2DToQVector2D(const base::Vector2d& vector) const
{
    std::cout << "vectorToVector2d " << vector[0] << " | " << vector[1] << std::endl;
    QVector2D qtvector2d(vector[0], vector[1]);
    return qtvector2d;
}
