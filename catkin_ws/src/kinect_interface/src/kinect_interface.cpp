
#include <iostream>
#include <kinect_interface/interface.h>

using namespace std;

int main(int argc, char **argv)
{
  cout << ros::ok() << endl;
  libfreenect2::Freenect2 freenect2;
  freenect2.enumerateDevices();
  cout << "Hello World" << endl;
  return 0;
}
