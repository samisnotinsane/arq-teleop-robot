using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class dum : MonoBehaviour {

    public OVRCameraRig vrRig;
    private Transform centreEyeTransform;
    // Use this for initialization
    void Start () {

        centreEyeTransform = vrRig.centerEyeAnchor;
    }
	
	// Update is called once per frame
	void Update () {
        
        Debug.Log("GazeAngle: [" + centreEyeTransform.transform.eulerAngles.y + "], GazeAxis: [" + centreEyeTransform.transform.eulerAngles.y + "]");
    }
}
