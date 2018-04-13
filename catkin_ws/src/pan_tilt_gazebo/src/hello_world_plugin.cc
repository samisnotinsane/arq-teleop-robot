#include<ros/ros.h>
#include <gazebo/gazebo.hh>

namespace gazebo
{
  class WorldPluginTutorial : public WorldPlugin
  {
    public: WorldPluginTutorial() : WorldPlugin()
			{
			    ROS_INFO("Hello World!");
			}
	public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
			{
				ROS_INFO("Hello World loaded");	
			}
  };
  GZ_REGISTER_WORLD_PLUGIN(WorldPluginTutorial)
}
