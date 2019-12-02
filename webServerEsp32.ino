    /////////////////////////////////////////////////////////////////
   //         ESP32 Web Server Project  v1.00                     //
  //       Get the latest version of the code here:              //
 //         http://educ8s.tv/esp32-web-server                   //
/////////////////////////////////////////////////////////////////


#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>  //https://github.com/bbx10/WebServer_tng

WebServer server ( 80 );

const char* ssid     = "IZZI-A207";
const char* password = "704FB839A207";

int LEDPIN = 32;
int SENSORPIN = 34;

float temperature = 0;

String  ledState = "OFF";

void setup()
{
  pinMode(LEDPIN, OUTPUT);

  Serial.begin(9600);

  connectToWifi();

  beginServer();
}

void loop() {

 server.handleClient();

 getTemperature();
 delay(250);

}

void connectToWifi()
{
  WiFi.enableSTA(true);

  delay(2000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("No conecta :(");
    }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void beginServer()
{
  server.on ( "/", handleRoot );
  server.begin();
  Serial.println ( "HTTP server started" );
}

void handleRoot(){
  if ( server.hasArg("LED") ) {
    handleSubmit();
  } else {
    server.send ( 200, "text/html", getPage() );
  }
}

void getTemperature()
{
  temperature =  ((analogRead(SENSORPIN) * 500 )/4096.0);
  Serial.println(analogRead(SENSORPIN));
  Serial.println(WiFi.localIP());
}

void handleSubmit() {

  String LEDValue;
  LEDValue = server.arg("LED");
  Serial.println("Set GPIO ");
  Serial.print(LEDValue);

  if ( LEDValue == "1" ) {
    digitalWrite(LEDPIN, HIGH);
    ledState = "On";
    server.send ( 200, "text/html", getPage() );
  }
  else if( LEDValue == "0" )
  {
    digitalWrite(LEDPIN, LOW);
    ledState = "Off";
    server.send ( 200, "text/html", getPage() );
  } else
  {
    Serial.println("Error Led Value");
  }
}

String getPage(){
  String page= "<html lang=en-EN><head><meta http-equiv='refresh' content='60'/>";
  page +="  <head>";
  page +="  <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css'>";
  page +="  <script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/js/bootstrap.min.js'></script>";
  page +="  <script src='https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js'></script>";
  page +="  <title>WebServer ESP32</title>";
  page +="  <style>";
  page +="    .nav{";
  page +="        background: #202753;";
  page +="        font-size: 35px;";
  page +="      color: #d8bdfa;";
  page +="      text-align: center;";
  page +="    }";
  page +="    .back{";
  page +="      background: #1b374f;";
  page +="    }";
  page +="    .foot{";
  page +="      background: #121111;";
  page +="      position: absolute;";
  page +="      bottom: 0;";
  page +="        width: 100%;";
  page +="        height: 26%;";
  page +="      overflow: hidden;";
  page +="      color: #b4b3b3;";
  page +="    }";
  page +="    .parrafoLabel{";
  page +="      color: white;";
  page +="      text-align: center;";
  page +="      margin-top: 20px;";
  page +="      bottom: 5px;";
  page +="      font-size:25px;";
  page +="    }";
  page +="    .parrafoTemperatura{";
  page +="      color: white;";
  page +="      text-align: center;";
  page +="      margin-top: 20px;   ";
  page +="      font-size:25px;";
  page +="    }";
  page +="    .finalFooter{";
  page +="      background: #242424;";
  page +="      font-size: 15px;";
  page +="      width: 100%;";
  page +="      height: 38%;";
  page +="      text-align: center;";
  page +="      color:#d0d0d0;";
  page +="    }";
  page +="    .prueba{";
  page +="      padding:11px;";
  page +="      height:25%;";
  page +="    }";
  page +="    .resultado{";
  page +="      margin-top: 5px;";
  page +="      text-align: center;";
  page +="      font-size: 60px;";
  page +="      color: white;";
  page +="    }";
  page +="    .botonEnviar{";
  page +="      margin-top: 10px;";
  page +="    }";
  page +="    @media (max-width: 600px){";
  page +="      .back{";
  page +="        background: #1b374f;";
  page +="        }";
  page +="    .foot{";
  page +="      background: #121111;";
  page +="      position: relative;";
  page +="      margin-top: 30px;";
  page +="        width: 100%;";
  page +="        height: 40%;";
  page +="      color: #b4b3b3;";
  page +="      overflow: visible;";
  page +="      }";
  page +="    .finalFooter{";
  page +="      background: #242424;";
  page +="      font-size: 15px;";
  page +="      width: 100%;";
  page +="      height: 35%;";
  page +="      text-align: center;";
  page +="      color:#d0d0d0;";
  page +="      }";
  page +="    }";
  page +="    </style>";
  page +="</head>";
  page +="<body class='back'>";
  page +="<p class='nav'> ESP32 WebSever</p>";
  page +="  <p class='parrafoLabel'> TEMPERATURA: </p>";
  page +="  <div class='resultado'>";
  page +=    temperature;
  page +="   &deg;C";
  page +="  </div>";
  page +="  <p class='parrafoTemperatura'> ESTADO LED: </p>";
  page +="  <div style='text-align: center; font-size: 30px; color:white;'> ";
  page +="    <br>";
  page +="    <form action='/' method='POST'>";
  page +="    <INPUT type='radio' name='LED' value='1'>ON";
  page +="    <INPUT type='radio' name='LED' value='0'>OFF";
  page +="    <br>";
  page +="    <br>";
  page +="      <INPUT class='btn btn-success' type='submit' value='Enviar'>";
  page +="  </form>";
  page +="  </div>";
  page +="<footer class='foot'>";
  page +="    <div class='row'>";
  page +="      <div class='col-md-6 mt-md-0 mt-3'>";
  page +="        <p style='margin: 10px;'>PROYECTO FINAL:</p>";
  page +="        <p style= 'margin: 10px;'>Sistema de temperatura Web con ESP32</p>";
  page +="      </div>";
  page +="    <div class='col-md-3 mb-md-0 mb-3'>";
  page +="        <h5 class='text-uppercase'>Autores:</h5>";
  page +="        <ul class='list-unstyled'>";
  page +="          <li>";
  page +="            <a href='#!'>Arellano Yeo Nomar Alberto</a>";
  page +="          </li>";
  page +="          <li>";
  page +="            <a href='#!'>Hernandez Garcia Luis Angel</a>";
  page +="          </li>";
  page +="          <li>";
  page +="            <a href='#!'>Vazquez Sanchez Ilse Abril</a>";
  page +="          </li>";
  page +="        </ul>";
  page +="      </div>";
  page +="    <div class='col-md-3 mb-md-0 mb-3'>";
  page +="        <h5 class='text-uppercase'>PROFESOR:</h5>";
  page +="        <ul class='list-unstyled'>";
  page +="          <li>";
  page +="            <a href='#!'>Ramirez Chavarria Roberto Giovanni</a>";
  page +="          </li>";
  page +="        </ul>";
  page +="      </div>";
  page +="    </div>";
  page +="  <div class='finalFooter'>";
  page +="    <p class='prueba'>Fundamentos de Sistemas Embebidos</p>";
  page +="    <p>©Semestre 2020-1</p>";
  page +="  </div>";
  page +="</footer>";
  page +="</body>";
  page +="</html>";
  return page;
}
