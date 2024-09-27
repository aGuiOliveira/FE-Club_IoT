#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Configurações - variáveis editáveis
const char* default_SSID = "Wokwi-GUEST"; // Nome da rede Wi-Fi, importante a sua rede wi-fi ter suporte a dispositivos de 2,4GHz devido ao ESP32 utilizar essa frequência 
const char* default_PASSWORD = ""; // Senha da rede Wi-Fi
const char* default_BROKER_MQTT = ""; // IP do Broker MQTT -> SEU IP DA VM AQUI
const int default_BROKER_PORT = 1883; // Porta do Broker MQTT
const char* default_TOPICO_SUBSCRIBE = "/TEF/device001/cmd"; // Tópico MQTT de escuta
const char* default_TOPICO_PUBLISH_1 = "/TEF/device001/attrs/temp"; // Tópico MQTT de envio de informações para Broker
const char* default_TOPICO_PUBLISH_2 = "/TEF/device001/attrs/move"; // Tópico MQTT de envio de informações para Broker
const char* default_ID_MQTT = "fiware_001"; // ID MQTT
// Declaração da variável para o prefixo do tópico
const char* topicPrefix = "device001";

// Variáveis para configurações editáveis
char* SSID = const_cast<char*>(default_SSID);
char* PASSWORD = const_cast<char*>(default_PASSWORD);
char* BROKER_MQTT = const_cast<char*>(default_BROKER_MQTT);
int BROKER_PORT = default_BROKER_PORT;
char* TOPICO_SUBSCRIBE = const_cast<char*>(default_TOPICO_SUBSCRIBE);
char* TOPICO_PUBLISH_1 = const_cast<char*>(default_TOPICO_PUBLISH_1);
char* TOPICO_PUBLISH_2 = const_cast<char*>(default_TOPICO_PUBLISH_2);
char* ID_MQTT = const_cast<char*>(default_ID_MQTT);

//Variáveis dos componentes
int sensorPin = 2;

OneWire oneWire (sensorPin);  // creates the OneWire object using a specific pin
DallasTemperature sensor (&oneWire);

WiFiClient espClient;
PubSubClient MQTT(espClient);
char EstadoSaida = '0';

void initSerial() {
    Serial.begin(115200);
}

void initWiFi() {
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
    reconectWiFi();
}

void initMQTT() {
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);
}

void setup() {
    initSerial();
    initWiFi();
    initMQTT();
    pinMode(4, INPUT_PULLUP); // Configura o pino do sensor PIR como entrada
    sensor.begin(); // Inicia sensor de temperatura
    delay(5000);
}

void loop() {
    VerificaConexoesWiFIEMQTT();
    handleTemperature(); // Função para escrever a temperatura
    handleMotion(); // Função para lidar com o sensor de movimento
    MQTT.loop();
    delay(1000);
}

void reconectWiFi() {
    if (WiFi.status() == WL_CONNECTED)
        return;
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}

void VerificaConexoesWiFIEMQTT() {
    if (!MQTT.connected())
        reconnectMQTT();
    reconectWiFi();
}

void reconnectMQTT() {
    while (!MQTT.connected()) {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE);
        } else {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Haverá nova tentativa de conexão em 2s");
            delay(2000);
        }
    }
}

void handleTemperature() {
    sensor.requestTemperatures ();
    float temp = sensor.getTempCByIndex (0);
    String temperatura = String(temp);
    Serial.print("Temperatura: ");
    Serial.println(temp);
    MQTT.publish(TOPICO_PUBLISH_1, temperatura.c_str());

}

void handleMotion() {
    int pirPin = 4; // Pino do sensor PIR
    int sensorValue = digitalRead(pirPin);
    if (sensorValue == HIGH) {
      String mensagem = "Movimento detectado";
      Serial.print(mensagem);
      MQTT.publish(TOPICO_PUBLISH_2, mensagem.c_str());
    }
}
