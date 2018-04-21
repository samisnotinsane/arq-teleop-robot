using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScreenController : MonoBehaviour {
    public GameObject leftScreen;
    public GameObject rightScreen;

    private Vector3 leftOffset;
    private Vector3 rightOffset;

    public void Start()
    {
        leftOffset = transform.position + leftScreen.transform.position;
        rightOffset = transform.position + rightScreen.transform.position;

    }

    public void LateUpdate()
    {
        // Move screen with HMD orientation
        //leftScreen.transform.position = transform.right + leftOffset;
        //rightScreen.transform.position = transform.localPosition + rightOffset;

        // transform.position = leftScreen.transform.position + offset;
        // leftScreen.transform.position = offset;
        // lScreenTransform.localRotation =
        //    Quaternion.Euler(0f, 0f, (float)90);
    }

}
