/*
Queen Mary University of London - 2018
Author: Sameen Islam (s.islam@se14.qmul.ac.uk)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
<http://www.apache.org/licenses/LICENSE-2.0>.
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

using System;
using UnityEngine;

namespace RosSharp.RosBridgeClient
{
    public class OVRProvider : MessageProvider
    {
        private SensorJoy message;
        public override Type MessageType { get { return (typeof(SensorJoy)); } }

        public string FrameId;

        private JoyOVRReader JoyOVRReader;

        private void Start()
        {
            InitializeGameObject();
            InitializeMessage();
        }
        private void Update()
        {
            if (IsMessageRequested)
                UpdateMessage();
        }
        private void InitializeGameObject()
        {
            JoyOVRReader = this.gameObject.GetComponent<JoyOVRReader>();
            JoyOVRReader.GazePointer = this.gameObject.GetComponent<GazeInputOVR>();
        }
        private void InitializeMessage()
        {
            message = new SensorJoy();
            message.header.frame_id = FrameId;
            message.axes = new float[1];
            message.buttons = new int[1];
        }
        private void UpdateMessage()
        {
            message.header.Update();
            message.axes[0] = JoyOVRReader.ReadRadian();
            RaiseMessageRelease(new MessageEventArgs(message));
        }
    }
}
