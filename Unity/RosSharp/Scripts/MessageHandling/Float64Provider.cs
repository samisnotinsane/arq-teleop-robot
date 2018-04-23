using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace RosSharp.RosBridgeClient
{
    public class Float64Provider : MessageProvider
    {
        private double message;
        public override Type MessageType { get { return (typeof(double)); } }

        public string FrameId;

        private JoyAxisReader JoyAxisReader;

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
            JoyAxisReader = this.gameObject.GetComponent<JoyAxisReader>();
        }

        private void InitializeMessage()
        {
            message = 0.0;
        }

        private void UpdateMessage()
        {
            message = JoyAxisReader.Read(); 
            //RaiseMessageRelease(new MessageEventArgs(message));
        }
    }
}


