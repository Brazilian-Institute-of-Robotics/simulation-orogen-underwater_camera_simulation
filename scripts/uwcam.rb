#
# In this sample test we send an array with the model state
# updateHook read this information and update the model joints and positions
#
require 'orocos'
require 'sdf'
require 'vizkit'
require 'io/console'

include Orocos
Orocos.initialize

#gui/robot_model is a dependency of this orogen package.
#load model paths from gui/robot_model/test_data
model_path = ["#{ENV['AUTOPROJ_CURRENT_ROOT']}/gui/robot_model/test_data"]

#gui/orogen/vizkit3d_world is a dependency of this orogen package.
#load world file from gui/orogen/vizkit3d_world/test_data
world_path = "#{ENV['AUTOPROJ_CURRENT_ROOT']}/gui/orogen/vizkit3d_world/test_data/simple.world"

SDF::XML.model_path << model_path
sdf = SDF::Root.load(world_path)

## create a widget that emulates a joystick
joystickGui = Vizkit.default_loader.VirtualJoystick

#show it
joystickGui.show()

Orocos.run 'underwater_camera_simulation::Task' => 'uwcam' do

    uwcam_task = TaskContext.get 'uwcam'

    #set an array with model paths
    uwcam_task.model_paths = model_path
    #path to world file
    uwcam_task.world_file_path = world_path
    #show gui
    uwcam_task.show_gui = false

    uwcam_task.configure
    uwcam_task.start

    rbs = Types::Base::Samples::RigidBodyState.new

    #set the camera position
    trans_x = 10
    rbs.position = Eigen::Vector3.new(0, 0, trans_x)
    rbs.orientation = Eigen::Quaternion.from_euler( Eigen::Vector3.new(Math::PI/2, 0, 0), 0, 0, 1)
    uwcam_task.camera_position.writer.write(rbs);

    joystickGui.connect(SIGNAL('axisChanged(double, double)')) do |x, y|
        #translate the camera position in the axis Z
        trans_x = trans_x + x * 0.1
        rbs.position = Eigen::Vector3.new(0, 0, trans_x)
        uwcam_task.camera_position.writer.write(rbs);
    end
 
    Vizkit.exec

end

