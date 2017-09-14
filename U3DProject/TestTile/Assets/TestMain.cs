using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;

public class TestMain : MonoBehaviour {


    [DllImport("UWPWrappers.dll", SetLastError = true, CallingConvention = CallingConvention.StdCall)]
    extern static bool CreateToast(int n);
    [DllImport("UWPWrappers.dll", SetLastError = true, CallingConvention = CallingConvention.StdCall)]
    extern static bool CreateTile(int n);

    private void Awake()
    {
        
    }

	// Use this for initialization
	void Start ()
    {

    }
	
	// Update is called once per frame
	void Update () {
	
	}

    int nFlag = 0;


    void InitTile()
    {
        CreateTile(0);
    }

    void OnGUI()
    {
        if (GUI.Button(new Rect(0, 0, 200, 100), "CLICK Toast"))
        {
            Debug.Log("click");
            if (CreateToast(0))
            {
                nFlag = 1;
            }
            else
            {
                nFlag = 2;
            }
        }
        if (GUI.Button(new Rect(300, 0, 200, 100), "CLICK Tile"))
        {
            Debug.Log("click");
            if (CreateTile(0))
            {
                nFlag = 3;
            }
            else
            {
                nFlag = 4;
            }
        }
        if (nFlag == 1)
        {
            GUI.Label(new Rect(200, 200, 300, 250), "Toast True");
        }
        else if(nFlag == 2)
        {
            GUI.Label(new Rect(200, 200, 300, 250), "Toast False");
        }
        if (nFlag == 3)
        {
            GUI.Label(new Rect(200, 200, 300, 250), "Tile True");
        }
        else if (nFlag == 4)
        {
            GUI.Label(new Rect(200, 200, 300, 250), "Tile False");
        }
    }
}
