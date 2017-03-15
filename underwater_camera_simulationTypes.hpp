#ifndef underwater_camera_simulation_TYPES_HPP
#define underwater_camera_simulation_TYPES_HPP

/* If you need to define types specific to your oroGen components, define them
 * here. Required headers must be included explicitly
 *
 * However, it is common that you will only import types from your library, in
 * which case you do not need this file
 */

#include <string>
#include <base/Types.hpp> 

namespace underwater_camera_simulation {

    struct CameraParams {
        /**
         * camera parameters
         * the main camera parameters used by Gazebo
         */
        double near;
        double far;
        double horizontal_fov;
    };

    struct OceanParameters
    {
        OceanParameters() 
            : surfDirty(true)
              , surfEndless(true)
              , surfWaveScale(1e-7)
              , surfDepth(1000)
              , surfWindDirection(1, 2)
              , surfWindSpeed(3.0)
              , surfReflectionDamping(0.2)
              , surfIsChoppy(true)
              , surfChoppyFactor(-2.5)
              , surfCrestFoam(true)
              , surfCrestFoamHeight(2.2)
              , surfFoamBottomHeight(2.2)
              , surfFoamTopHeight(2.2)
              , sceneDirty(true)
              , airFogColor(199, 226, 255)
              , airFogDensity(0.012)
              , sunPosition(326, 1212, 1275)
              , sunDiffuseColor(191, 191, 191)
              , uwFogColor(27, 57, 109)
              , uwFogDensity(0.02)
              , uwAttenuation(0.015, 0.0075, 0.005)
              , uwDiffuseColor(27, 57, 109)
              , glareAttenuation(0.8)
              , reflections(true)
              , refractions(false)
              , heightmap(true)
              , godRays(true)
              , silt(true)
              , underwaterDOF(false)
              , underwaterScattering(true)
              , distortion(true)
              , glare(false)
        {
        }

        /// Ocean surface parameters
        bool      surfDirty;
        bool      surfEndless;
        float     surfWaveScale;
        float     surfDepth;
        base::Vector2d surfWindDirection;
        float     surfWindSpeed;
        float     surfReflectionDamping;
        bool      surfIsChoppy;
        float     surfChoppyFactor;
        bool      surfCrestFoam;
        float     surfCrestFoamHeight;
        float     surfFoamBottomHeight;
        float     surfFoamTopHeight;

        /// Ocean scene parameters
        bool      sceneDirty;
        base::Vector3d    airFogColor;
        float     airFogDensity;
        base::Vector3d sunPosition;
        base::Vector3d sunDiffuseColor;
        base::Vector3d uwFogColor;
        float     uwFogDensity;
        base::Vector3d uwAttenuation;
        base::Vector3d uwDiffuseColor;
        float     glareAttenuation;
        bool      reflections;
        bool      refractions;
        bool      heightmap;
        bool      godRays;
        bool      silt;
        bool      underwaterDOF;
        bool      underwaterScattering;
        bool      distortion;
        bool      glare;

    };
}

#endif

