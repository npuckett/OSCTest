#include <ArduinoOSCWiFi.h>



// WiFi stuff change it to whatever matches your network
//const int LEDpin = 21;
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

IPAddress ip;
String cnvIP;

//values from Unity, 
float xDirection;
float yDirection;


///function called when data is received from Unity
void unityOSCdata(const OscMessage& unityMessage) 
{

//read the 2 float values from Unity
xDirection = unityMessage.arg<float>(0);
yDirection = unityMessage.arg<float>(1);

  Serial.print("::: RECEIVE ::: Unity ");
  Serial.print(sendIPaddress);
  Serial.print("-> Arduino IP: ");
  Serial.print(cnvIP);
  Serial.print(" Port: ");
  Serial.print(myReceivePort);
  Serial.print(" : ");
  Serial.print(unityMessageTag);
  Serial.print("\t");
  Serial.print(xDirection);
  Serial.print("\t");
  Serial.print(yDirection);
  Serial.println();

  //pinMode(LEDpin, OUTPUT);
  //int brightness = map(xDirection,-1,1,0,255);
  //analogWrite(LEDpin,brightness);
 
}





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

    ip = WiFi.localIP();
    cnvIP = "IP: "+IpAddress2String(ip);

    Serial.print("WiFi connected, IP = ");
    Serial.println(ip);

    //turns on the built in LED to show it conneted
    pinMode(LED_BUILTIN,OUTPUT);
    digitalWrite(LED_BUILTIN,HIGH);

    
 
    //////******THE OUTPUTS*********//////
    //This binds the incoming data to a callback function (just like how it is set up on the unity side)
    OscWiFi.subscribe(myReceivePort, unityMessageTag, unityOSCdata);

}

void loop() 
{
    
    //OscWiFi.update();  // should be called to receive + send osc
    // or do that separately
    OscWiFi.parse(); // to receive osc
    // OscWiFi.post(); // to publish osc
   

}


//helper function to convert the IP address to a string
String IpAddress2String(const IPAddress& address)
{
  return String() + address[0] + "." + address[1] + "." + address[2] + "." + address[3];
}