/*
Queen Mary University of London, 2018
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

using UnityEngine;

namespace RosSharp.RosBridgeClient
{
    public class GazeInputOVR : MonoBehaviour
    {

        public OVRCameraRig vrRig;

        private Transform centreEyeTransform;
        private float GazeAngle = 0.0F;
        private float gazeAxis;
        private float gazeAngleRad;

        public float GazeAxis { get { return gazeAxis; } private set { gazeAxis = value; } }
        public float GazeRad { get { return gazeAngleRad; } private set { gazeAngleRad = value; } }

        // Use this for initialization
        public void Start()
        {
            GazeAngle = 0.0F;
            gazeAngleRad = 0.0F;
            gazeAxis = 0.0F; // may need to deprecate
            centreEyeTransform = vrRig.centerEyeAnchor;
        }

        // Update is called once per frame
        public void Update()
        {
            // Range: 0 - 360 DEG.
            GazeAngle = centreEyeTransform.transform.eulerAngles.y;

            if (GazeAngle <= 180)
            {
                gazeAngleRad = -(Mathf.Min(GazeAngle * Mathf.Deg2Rad,Mathf.PI/2));
            }
            else {
                gazeAngleRad = Mathf.Min((360-GazeAngle) * Mathf.Deg2Rad, Mathf.PI / 2);
            }
            

            Debug.Log("GazeAngle: [" + GazeAngle + "], GazeRad: [" + GazeRad + "]");
        }
    }

}
