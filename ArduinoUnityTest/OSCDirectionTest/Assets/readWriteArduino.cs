using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class readWriteArduino : MonoBehaviour
{
    //after you apply the oscIn script to the game object, you can drag the game object into the inspector
    public OSC osc;

    //should correspond to the address in the arduino code
    public string ArduinoMessageAddress = "/arduino2";
    //variables to store the values from the arduino
    public float arduinoVal1;
    public float arduinoVal2;
    //should correspond to the address in the arduino code
    public string UnityMessageAddress = "/unity2";
    float move;
    float move2;
    // Start is called before the first frame update
    void Start()
    {
        //create a handler for the OSC message
        //the handler is a method that will be called when the OSC message is received
        //the first value is the address of the message, the second is the method that will be called
        osc.SetAddressHandler(ArduinoMessageAddress, OnReceiveArduino);

    }

    // Update is called once per frame
    void Update()
    {
        move = Input.GetAxis("Horizontal");
        move2 = Input.GetAxis("Vertical");
         //send the X and Y and Z position of the cube to the arduino as OSC messages
         //the target port and IP address are set on the OSC component   
        OscMessage message = new OscMessage();
        message.address = UnityMessageAddress;
        message.values.Add(move);
        message.values.Add(move2);
        osc.Send(message);

        //print the output to the console
        Debug.Log("Sent " + UnityMessageAddress + "\n" + transform.position.x + " " + transform.position.y + " " + transform.position.z + "\n");

         //print the input to the console
        Debug.Log("Received " + ArduinoMessageAddress + "\n" + arduinoVal1 + " " + arduinoVal2 + "\n");

        Debug.Log(move);
        Debug.Log(move2);

        
    }

    //this method will be called when the OSC message is received
    void OnReceiveArduino(OscMessage message)
    {
        //get the values from the OSC message
        //the values are stored in the message in the order they are sent
        //the first value is at index 0, the second at index 1, etc.
        arduinoVal1 = message.GetFloat(0);
        arduinoVal2 = message.GetFloat(1);

       
    }
}
