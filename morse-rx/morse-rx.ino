/**
 * @file morse-rx.ino
 * @author Paulo Roberto (pauloxrms@gmail.com/pauloroberto.santos@edge.ufal.br)
 * @brief Sketch de exemplo em como implementar um decodificador morse em
 * Arduino.
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */

/**
 * @brief Tempo de duração do ponto, pode ser alterado para melhor visualizar o
 * código Morse.
 */
#define DOT_DELAY 300

/**
 * @brief Tempo de duração do traço, segundo o padrão internacional.
 */
#define DASH_DELAY 3 * DOT_DELAY

/**
 * @brief Padrões internacionais de tempo para os "espaços" em morse.
 */
#define IN_LETTER_SPACE_DELAY DOT_DELAY
#define OUT_LETTER_SPACE_DELAY 3 * DOT_DELAY
#define WORD_SPACE_DELAY 7 * DOT_DELAY

/**
 * @brief Qual pino vamos usar para conectar o ldr.
 */
#define LDR_PIN A0

/**
 * @brief Valor onde o ldr garante que está recebendo um sinal de luz 
 */
#define LDR_LIMIT_READ 300

/**
 * @brief enumera as letras para acessar o array mais fácilmente.
 */
typedef enum {
  A = 0,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,

  DOT,
  COMMA,
  QUESTION_MARK,
  SLASH,
  AT,

  _LETTERS_AMOUNT,
} letter_t;

/**
 * @brief Array com as strings de codificação em Morse.
 *
 */
char letters[_LETTERS_AMOUNT][7] = {

    ".-",   /*< A */
    "-...", /*< B */
    "-.-.", /*< C */
    "-..",  /*< D */
    ".",    /*< E */
    "..-.", /*< F */
    "--.",  /*< G */
    "....", /*< H */
    "..",   /*< I */
    ".---", /*< J */
    "-.-",  /*< K */
    ".-..", /*< L */
    "--",   /*< M */
    "-.",   /*< N */
    "---",  /*< O */
    ".--.", /*< P */
    "--.-", /*< Q */
    ".-.",  /*< R */
    "...",  /*< S */
    "-",    /*< T */
    "..-",  /*< U */
    "...-", /*< V */
    ".--",  /*< W */
    "-..-", /*< X */
    "-.--"  /*< Y */
    "--.."  /*< Z */

    ".-.-.-", /*< . */
    "--..--", /*< , */
    "..--..", /*< ? */
    "-..-.",  /*< / */
    ".--.-."  /*< @ */
};

unsigned long int time_now; /**< Variável para guardar o tempo atual. */
unsigned long int time_last; /**< Variável para guardar o tempo base.*/

unsigned long int on_time; /**< Variável para guardar o tempo que o LDR permanenceu 'ligado'.*/
unsigned long int off_time; /**< Variável para guardar o tempo que o LDR permanenceu 'desligado'.*/

unsigned int current_pos = 0; /**< Contador para escrever no nosso buffer. */
char received[10]; /**< Buffer para a string que será montada. */
char current_reading; /**< Caracter a ser escrito no buffer. */

const int time_adjust = 50; /**< Váriavel de ajuste na leitura dos tempos, pode ser alterada para melhorar a recepção. */

/**
 * @brief Confere se o LDR está recebendo luz.
 * 
 * @return true O LDR está recebendo luz.
 * @return false O LDR não está recebendo luz..
 */
bool is_led_on(void) {
    return (analogRead(LDR_PIN) > LDR_LIMIT_READ);
}

/**
 * @brief Transforma uma string em morse num caracter da tabela ASCII.
 * 
 * @param morse_letter string a ser descodificada.
 * @return char Caracter que representa a string.
 */
char received_letter(char* morse_letter) {
	for (unsigned int i = 0; i < _LETTERS_AMOUNT; i++) {
		
		if (strcmp(morse_letter, letters[i]) == 0) { /** Verifica a string montada */
			
			if (i < DOT) { /** Era letra */
				return i + 'A';
			}

			switch (i) { /** Era símbolo */
				case DOT:
				  	return '.';
				case COMMA:
					return ',';
				case QUESTION_MARK:
				  	return '?';
				case SLASH:
					return '/';
				case AT:
					return '@';
			}
		}
	}

	return '\0'; /** Não era algo reconhecível */
}

void setup() {
    Serial.begin(9600);
    time_last = time_now = millis();
}

void loop() {
    time_last = millis();

	/** Processa o tempo da luz apagada */
	{
    	while(!is_led_on()) { } /**< Espera a luz acender */
		
		time_now = millis();
		off_time = time_now - time_last; /** Tempo apagado lido */

		if (off_time > (WORD_SPACE_DELAY - time_adjust)) { /** Aconteceu um espaço */
			Serial.print(" ");
			current_pos = 0;
		} else if (off_time > (OUT_LETTER_SPACE_DELAY - time_adjust)) { /** Uma letra terminou de ser escrita */
			received[current_pos] = '\0';
			Serial.print(received_letter(received));
			current_pos = 0;
		}
	}

	/** Processa o tempo da luz acesa */
	{	
		while(is_led_on()) { } /**< Espera a luz apagar */
		
		time_now = millis();
		on_time = time_now - time_last; /** Tempo lido */
		
		if (on_time > (DOT_DELAY - time_adjust)) { /** Pode ser um .*/
			current_reading = '.';
			
			if (on_time > (DASH_DELAY - time_adjust)) { /** Na verdade era um - */
				current_reading = '-';
			}
		} 

		received[current_pos++] = current_reading; /** Salva no nosso buffer, e incrementa a posição de escrita */
	}

}