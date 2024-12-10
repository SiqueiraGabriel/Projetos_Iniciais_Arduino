#include <Servo.h>  // Importação da biblioteca para utilização do Servo Motor

#define pino_servo 10       // Definir o pino conectado o Servo Motor
#define pino_trigger 12     // Definir o pino trigger do Sensor Ultrassônico
#define pino_echo  11       // Definir o pino echo do Sersor Ultrassônico
#define pino_ledVermelho 2  // Definir o pino do LED Vermelho
#define pino_ledVerde 3     // Definir o pino do LED Verde
#define pino_buzzer 4       // Definir o pino do Buzzer


int DURACION;         // Armazenar a duração da leitura do sensor ultrassonico para realizar a conversão
int DISTANCIA;        // Armazenar a distância em cm do obtido no sensor ultrassônico com base na duração obtida
int distance_now = 0; // Armazenar a última distância obtida no sernsor ultrassonico
Servo meuServo;       // Criar o objeto para controle do servo motor


void setup() {

  // Definir os pinos a ser utilizados e se serão de entrada ou saída
  pinMode(pino_trigger, OUTPUT);
  pinMode(pino_echo, INPUT);
  pinMode(pino_ledVermelho, OUTPUT);
  pinMode(pino_ledVerde, OUTPUT);
  pinMode(pino_buzzer, OUTPUT);
  
  // Definir o pino que será utilizado para conexão com o servo motor
  meuServo.attach(pino_servo);

  // Ajustar o servo motor para 0 graus
  meuServo.write(0);

  // Definir o sensor serial que será utilizado para comunicação com o processing
  Serial.begin(9600);
}

/*
* Função responsável por obter a distância do sensor ultrassonico em relação ao objeto detectado
*/
int get_distance(){

  // Realizar a ativação do pino Trigger do Sensor Ultrassônico
	digitalWrite(pino_trigger,HIGH);
	delay(1);

  // Realizar a desativação do pino Trigger do Sensor Ultrassonico
	digitalWrite(pino_trigger,LOW);

  // Calcular a duração da transmissão do pulso encaminhado, em tensão
	DURACION=pulseIn(pino_echo,HIGH);

  // Realizar a conversão da tensão em centimetros
	DISTANCIA=DURACION/58.2;

  // Retornar a distância em cm
  return DISTANCIA;
}


/*
* Função responsável por simular o BatSinal quando um objeto é detectado
*/
void tocarBatsinal() {

  // Alterna tons graves e agudos para simular o som do Batsinal
  for (int i = 0; i < 3; i++) { // Repete o som 3 vezes
    tone(pino_buzzer, 800); // Frequência grave
    delay(300);
    tone(pino_buzzer, 1200); // Frequência aguda
    delay(300);
    noTone(pino_buzzer);
    delay(100); // Pausa entre repetições
  }
}

/*
* Função responsável por desligar o LED verde e ligar o LED vermelho
*/
void liga_led_vermelho(){
  digitalWrite(pino_ledVermelho, HIGH);
  digitalWrite(pino_ledVerde, LOW);
}

/*
* Função responsável por desligar o LED vermelho e ligar o LED verde
*/
void liga_led_verde(){
	digitalWrite(pino_ledVermelho, LOW);
    digitalWrite(pino_ledVerde, HIGH);
}

/*
* Função responsável por movimentar o servo motor num determinado ângulo, efetuar a leitura da distância do objeto mais próximo e se estiver numa distância 
* inferior a 30 cm ligar o LED vermelho e soar o sinalizador do batman. 
*/
void verificador_distancia(int angulo){

  // Movimentar o servo motor para o ângulo atual
	meuServo.write(angulo);

  // Realizar a leitura da distância do objeto mais próximo
  distance_now = get_distance();
    
  // Verificar se a distância é inferior a 30 cm ou não
  if(distance_now < 30){
    tocarBatsinal();
    liga_led_vermelho();
  }else{
    noTone(pino_buzzer);
    liga_led_verde();
  }
    
  // Definir a estrutura que será encaminhado para o processing
  Serial.print(angulo);
  Serial.print(",");
  Serial.println(distance_now);

  // Dar uma pausa de 30 milisegundos para a próxima leitura
  delay(30);
}


void loop() {

  // Realizar a leitura nos angulo de 0 a 180 graus
  for(int angulo = 0; angulo < 180; angulo++)
    verificador_distancia(angulo);

  // Realizar a leitura nos angulo de 180 a 0 graus
  for(int angulo = 180; angulo > 1; angulo--)
    verificador_distancia(angulo);
}
