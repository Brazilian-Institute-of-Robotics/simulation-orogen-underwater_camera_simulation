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
         * the camera name
         */
        std::string camera_name;

        /**
         * camera link name
         * the name of link which represents the camera
         * the link position is used to map the camera position
         */
        std::string camera_link;

        /**
         * camera parameters
         * the main camera parameters used by Gazebo
         */
        int width;
        int height;
        double near;
        double far;
        double horizontal_fov;
    };
}

#endif

