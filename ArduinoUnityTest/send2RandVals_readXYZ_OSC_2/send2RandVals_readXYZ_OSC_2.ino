#include <ArduinoOSCWiFi.h>



// WiFi stuff change it to whatever matches your network
const char* ssid = "Khan_2.4G";
const char* pwd = "9053387336";


// for ArduinoOSC
///IP address of your computer
const char* sendIPaddress = "192.168.1.132";
//this is message address that is used by unity 
const char* arduinoMessageTag = "/arduino2";
//port specified in the OSC in variable in Unity
const int mySendPort = 8000;
//this is message address that is SENT from unity 
const char* unityMessageTag = "/unity2";
//port specified int eh OSC out variable in Unity
const int myReceivePort = 9000;

//this is the variables that are sent to unity
float randomSend1;
float randomSend2;

//values from Unity, the XYZ values of the sphere
float movement;
float movement2;



void setup() 
{
    Serial.begin(9600);

//connect to WiFi
    WiFi.begin(ssid, pwd);

    //lets you know it is connecting
    while (WiFi.status() != WL_CONNECTED) 
    {
    Serial.print(" .connecting.");
    delay(500);
    }
    Serial.print("WiFi connected, IP = ");
    Serial.println(WiFi.localIP());

    //turns on the built in LED to show it conneted
    pinMode(LED_BUILTIN,OUTPUT);
    digitalWrite(LED_BUILTIN,HIGH);


    //////******THE OUTPUTS*********//////
    //sets up publishing the osc message with the 2 values from your defined variables 
    //if you need to send more than 2 values you will need to add more variables and add them to the publish function
    //you can mix different types of variables in the publish function
    OscWiFi.publish(sendIPaddress, mySendPort, arduinoMessageTag, randomSend1, randomSend2);


    //////******THE OUTPUTS*********//////
    //the variables that receive the data should be in the same order as they were packaged
    OscWiFi.subscribe(myReceivePort, unityMessageTag, movement, movement2);


}

void loop() 
{

//calculates random numbers to send. replace this with sensor data
randomSend1 = random(0,1000)/10.0;
randomSend2 = random(0,1000)/10.0;
    
    
    OscWiFi.update();  // should be called to receive + send osc
    // or do that separately
    // OscWiFi.parse(); // to receive osc
    // OscWiFi.post(); // to publish osc

    //print out the data to Serial
    printOSCdata();

}



void printOSCdata() 
{
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  String cnvIP = "IP: "+IpAddress2String(ip);
  Serial.print("::: SEND ::: Arduino ");
  Serial.print(cnvIP);
  Serial.print("-> Target IP: ");
  Serial.print(sendIPaddress);
  Serial.print(" Port: ");
  Serial.print(mySendPort);
  Serial.print(" : ");
  Serial.print(arduinoMessageTag);
  Serial.print("\t");
  Serial.print(randomSend1);
  Serial.print("\t");
  Serial.println(randomSend1);

  Serial.print("::: RECEIVE ::: Unity ");
  Serial.print(sendIPaddress);
  Serial.print("-> Arduino IP: ");
  Serial.print(cnvIP);
  Serial.print(" Port: ");
  Serial.print(myReceivePort);
  Serial.print(" : ");
  Serial.print(unityMessageTag);
  Serial.print("\t");
  Serial.print(movement);
  Serial.print("\t");
  Serial.print(movement2);
  //Serial.print("\t");
  //Serial.println(tz);


  
}

//helper function to convert the IP address to a string
String IpAddress2String(const IPAddress& address)
{
  return String() + address[0] + "." + address[1] + "." + address[2] + "." + address[3];
}
