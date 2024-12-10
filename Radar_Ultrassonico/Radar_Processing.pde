import processing.serial.*;

// Declaração do objeto serial para gerenciar a comunicação
Serial myPort;

// Variáveis globais para armazenar a distância e o ângulo recebidos do Arduino
float distancia = 0, angulo = 0;

// Resolução do heatmap (quanto maior, maiores os "pixels")
int resolution = 20; // Tamanho dos "pixels" do mapa
int cols, rows; // Colunas e linhas do grid
float[][] heatmap; // Armazena as intensidades de calor
int currentCol = -1, currentRow = -1; // Coordenadas do objeto detectado no momento atual

void setup() {
  size(800, 600);
  
  // Inicializa a comunicação serial
  myPort = new Serial(this, "COM4", 9600);
  myPort.bufferUntil('\n');
  
  // Inicializa o heatmap
  cols = width / resolution;
  rows = height / resolution;
  heatmap = new float[cols][rows];
}

void draw() {
  background(0);

  // Move a origem para o centro inferior
  translate(width / 2, height - 100);

  // Desenha o heatmap
  noStroke();
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      float intensity = heatmap[i][j];
      if (intensity > 0) {
        // Intensidade de cor no estilo "onda de calor"
        fill(intensity * 255, 0, 0, intensity * 200);
        rect(i * resolution - width / 2, -j * resolution - 100, resolution, resolution);
        heatmap[i][j] *= 0.98; // Fading mais lento para manter o calor visível
      }
    }
  }

  // Desenha os elementos do radar
  stroke(0, 255, 0);
  noFill();

  // Linhas do radar
  for (int i = 0; i <= 180; i += 30) {
    line(0, 0, 300 * cos(radians(i)), -300 * sin(radians(i)));
  }

  // Círculos concêntricos
  for (int r = 50; r <= 300; r += 50) {
    ellipse(0, 0, r * 2, r * 2);
  }

  // Linha do radar
  strokeWeight(2);
  line(0, 0, 300 * cos(radians(angulo)), -300 * sin(radians(angulo)));

  // Adiciona o calor no ponto detectado
  if (distancia > 0 && distancia < 300) {
    float x = distancia * cos(radians(angulo));
    float y = -distancia * sin(radians(angulo));

    int col = int((x + width / 2) / resolution);
    int row = int((-y + 100) / resolution);

    if (col >= 0 && col < cols && row >= 0 && row < rows) {
      // Atualiza o ponto mais recente
      currentCol = col;
      currentRow = row;

      // Incrementa o calor no mapa
      heatmap[col][row] = min(1.0, heatmap[col][row] + 0.3); 
    }
  }

  // Destaca o ponto atual em vermelho puro
  if (currentCol >= 0 && currentRow >= 0) {
    fill(255, 0, 0); // Vermelho puro
    rect(currentCol * resolution - width / 2, -currentRow * resolution - 100, resolution, resolution);
  }

  // Exibe informações de depuração
  fill(255);
  text("Angle: " + angulo + "°", -width / 2 + 10, -height + 150);
  text("Distance: " + distancia + " cm", -width / 2 + 10, -height + 10);
}

void serialEvent(Serial myPort) {
  String data = myPort.readStringUntil('\n');
  if (data != null) {
    data = trim(data);
    String[] values = split(data, ',');
    if (values.length == 2) {
      angulo = float(values[0]);
      distancia = float(values[1]);
      println(angulo, distancia);
    }
  }
}
