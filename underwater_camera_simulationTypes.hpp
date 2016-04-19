#ifndef underwater_camera_simulation_TYPES_HPP
#define underwater_camera_simulation_TYPES_HPP

/* If you need to define types specific to your oroGen components, define them
 * here. Required headers must be included explicitly
 *
 * However, it is common that you will only import types from your library, in
 * which case you do not need this file
 */

#include <string>

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
}

#endif

