#include<stdio.h>
#include<ros/ros.h>
#include<functional>
#include<boost/bind.hpp>
#include<gazebo/gazebo.hh>
#include<gazebo/physics/physics.hh>
#include<gazebo/common/common.hh>
#include<ignition/math/Vector3.hh>

namespace gazebo
{
  class ModelPush : public ModelPlugin
	{

	  public: ModelPush() : ModelPlugin()
			  {
				  ROS_INFO("Loading ModelPush plugin...");
			  }

      public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
			  {
				  ROS_INFO("Loaded ModelPush plugin.");
				  this->model = _parent;

				  /*std::cout << "\nModelPush plugin is attached to model [" <<
					  _parent->GetName() << "]\n";*/
				  this->updateConnection = event::Events::ConnectWorldUpdateBegin(
						  std::bind(&ModelPush::OnUpdate, this));
			  }

	  public: void OnUpdate()
			  {
				  // Apply linear velocity in x dimension
				  this->model->SetLinearVel(ignition::math::Vector3d(0.3, 0, 0));
			  }

	  private: physics::ModelPtr model;
	  private: event::ConnectionPtr updateConnection;
	};
  GZ_REGISTER_MODEL_PLUGIN(ModelPush);
}

