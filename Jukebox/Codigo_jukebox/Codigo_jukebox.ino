#include "pitches.h"

#define BUZZER_PIN 6
#define BUTTON_PIN 2
#define INTERRUPTOR_PIN 3
#define VERMELHO_PIN 10
#define VERDE_PIN 11

int *melody[] = { 
  
  (int[]){
    NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_F5, NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_F5, NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_C6, NOTE_G5, NOTE_G5, REST, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C6, NOTE_C6, NOTE_F6, NOTE_DS6, NOTE_CS6, NOTE_C6, NOTE_AS5, NOTE_GS5, NOTE_G5, NOTE_F5, NOTE_C6
  },
    
   // Musica Harry Potter
  (int[]){
    REST, NOTE_D4, NOTE_G4, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_G4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_GS4, NOTE_D4, NOTE_D4, NOTE_G4, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_D5, NOTE_F5, NOTE_E5, NOTE_DS5, NOTE_B4, NOTE_DS5, NOTE_D5, NOTE_CS5, NOTE_CS4, NOTE_B4, NOTE_G4, NOTE_AS4, NOTE_D5, NOTE_AS4, NOTE_D5, NOTE_AS4, NOTE_DS5, NOTE_D5, NOTE_CS5, NOTE_A4, NOTE_AS4, NOTE_D5, NOTE_CS5, NOTE_CS4, NOTE_D4, NOTE_D5, REST, NOTE_AS4, NOTE_D5, NOTE_AS4, NOTE_D5, NOTE_AS4, NOTE_F5, NOTE_E5, NOTE_DS5, NOTE_B4, NOTE_DS5, NOTE_D5, NOTE_CS5, NOTE_CS4, NOTE_AS4, NOTE_G4
  }
 
};

int *durations[] = {
// Musica do Star Wars
  (int[]){
    8, 8, 8, 2, 2, 8, 8, 8, 2, 4, 8, 8, 8, 2, 4, 8, 8, 8, 2, 8, 8, 8, 2, 2, 8, 8, 8, 2, 4, 8, 8, 8, 2, 4, 8, 8, 8, 2, 8, 16, 4, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 4, 8, 16, 4, 8, 8, 8, 8, 8, 8, 16, 2, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 4, 8, 16, 4, 8, 4, 8, 4, 8, 4, 8, 1
  },
    
   // Musica do Harry Potter
  (int[]){
    2, 4, 4, 8, 4, 2, 4, 2, 2, 4, 8, 4, 2, 4, 1, 4, 4, 8, 4, 2, 4, 2, 4, 2, 4, 4, 8, 4, 2, 4, 1, 4, 2, 4, 2, 4, 2, 4, 2, 4, 4, 8, 4, 2, 4, 1, 4, 4, 2, 4, 2, 4, 2, 4, 2, 4, 4, 8, 4, 2, 4, 1
  }
};

// Vetor indicando a duração de cada música, visto que é utilizado para armazenamento das mesmas vetores dinâmicos
int size_duration[] = {72, 60}; 

// Informar a quantidade de músicas disponíveis
int total_musics = 2;

// Estado da música e do botão

// Inicialmente, a música está parada
bool tocando = false;  

// Para detectar mudanças de estado do botão
bool botao_anterior = false; 

// Indice da música que esta tocando
int actual_music = 0;

// Índice da nota atual
int nota_atual = 0;

// Indicar se o interruptor esta ativado ou não
int vb = 0;


void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Usar pull-up interno para o botão
  pinMode(INTERRUPTOR_PIN, INPUT);
  pinMode(VERMELHO_PIN, OUTPUT);
  pinMode(VERDE_PIN, OUTPUT);
}


// Função responsável por desligar o LED vermelho e ligar o verde
void liga_led(){
	Serial.println("Ligado");
    digitalWrite(VERDE_PIN, HIGH);
    digitalWrite(VERMELHO_PIN, LOW);
}

void desliga_led(){
  digitalWrite(VERDE_PIN, LOW);
  digitalWrite(VERMELHO_PIN, HIGH);
  Serial.println("Desligado");
}

// Função responsável por indicar a troca da música, no qual vai desligar a luz verde, ativar a vermelha por um breve período e depois vai ativar a verde novamente
void troca_musica_led(){
  digitalWrite(VERDE_PIN, LOW);
  delay(100);
  digitalWrite(VERMELHO_PIN, HIGH);
  delay(100);
  digitalWrite(VERMELHO_PIN, LOW);
  digitalWrite(VERMELHO_PIN, HIGH);
}


/*
Função responsável por verificar se o botão foi presionado e caso afirmativo vai realizar a troca da música a ser tocada
*/
void verifica_botao_pressionado(){
  
  // Verifica o estado do botão (pressionado = LOW)
  	bool botao_atual = digitalRead(BUTTON_PIN) == LOW;
  
  	if (botao_atual && !botao_anterior) { 
      
      // Alternar a musica a ser tocada
      tocando = !tocando; 

      // Casp a musica já estiver tocando, somente apresenta no log
      if (tocando) {

        // Log: início da reprodução
        Serial.println("Tocando música..."); 
      } 
      else {

        // Acender os leds que indica troca da música
        troca_musica_led();

        // Altera a música atual para a próxima música disponível
        actual_music = (actual_music + 1) % total_musics;

        // Reinicia a contagem da nota musical, ou seja, define para que a mesma inicie na posição 0
        nota_atual = 0; 

        // Informa que o dispositivo está pronto para tocar a música e da um delay de 1 segundo antes de começar a nova música
        tocando = true;
        delay(1000);

        // Log de Troca de Música
        Serial.println("Houve a troca de música");
      }
    }
  
  	// Atualiza o estado anterior do botão para detectar mudanças futuras
  	botao_anterior = botao_atual; 

}

void tocar_nota_musical(){
  
	// Calcula a duração da nota atual
  	int duration = 1000 / durations[actual_music][nota_atual];
      
  	// Emite o som correspondente à nota, caso não seja um descanso
  	if (melody[actual_music][nota_atual] != REST) {
      tone(BUZZER_PIN, melody[actual_music][nota_atual], duration);
    }
     
  	// Aguarda a duração da nota antes de avançar
  	delay(duration * 1.30); 
  
  	// Para o som da nota atual
    noTone(BUZZER_PIN); 
 	
  	// Avança para a próxima nota
  	nota_atual++;           
}

/*
* Função responsável por trocar a música em execução ao finalizar a anterior
*/
void trocar_musica_ao_finalizar_anterior(){
  
  // Log: fim da música
  Serial.println("Música terminou."); 
  
  // Parar a reprodução
    tocando = false;  
  
  // Alterar para a próxima música disponível
  actual_music = (actual_music + 1) % total_musics; // Incrementa e reinicia no total

  // Reinicia o índice para o início da música
    nota_atual = 0;   
  
  // Iniciar a reprodução da nova música
    tocando = true;

}


void loop() {
  
  
  // Ler o Interruptor, que indica se o dispositivo está no modo ligado ou desligado
  vb = digitalRead(INTERRUPTOR_PIN);
  
  // Caso o dispositivo estiver ligado -> Interruptor como HIGH
  if (vb==HIGH) {
    
    // Acender os leds indicando que o dispositivo esta ligado
    liga_led();
    
    // Verificar se algum botão foi pressionado ou se necessita trocar de música
   verifica_botao_pressionado();
   
/**
   * Reproduz as notas da música se `tocando` for verdadeiro.
   * - Toca cada nota em sequência, respeitando sua duração.
   * - Interrompe automaticamente quando a música termina, reiniciando os índices.
 */

    if (tocando) {
      if (nota_atual < size_duration[actual_music]) 
          tocar_nota_musical();
      else 
        trocar_musica_ao_finalizar_anterior();
    }
  }
  
  // Caso o dispositivo estiver desligado
  else {
    desliga_led();
    
  }
}
