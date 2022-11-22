/**
 * @file morse-tx.ino
 * @author Paulo Roberto (pauloxrms@gmail.com/pauloroberto.santos@edge.ufal.br)
 * @brief Sketch de exemplo em como implementar um codificador morse em Arduino.
 * @version 0.1
 * @date 2022-11-22
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
 * @brief Qual pino vamos usar para conectar o led.
 */
#define LED_PIN LED_BUILTIN

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

    ".-",     /*< A */
    "-...",   /*< B */
    "-.-.",   /*< C */
    "-..",    /*< D */
    ".",      /*< E */
    "..-.",   /*< F */
    "--.",    /*< G */
    "....",   /*< H */
    "..",     /*< I */
    ".---",   /*< J */
    "-.-",    /*< K */
    ".-..",   /*< L */
    "--",     /*< M */
    "-.",     /*< N */
    "---",    /*< O */
    ".--.",   /*< P */
    "--.-",   /*< Q */
    ".-.",    /*< R */
    "...",    /*< S */
    "-",      /*< T */
    "..-",    /*< U */
    "...-",   /*< V */
    ".--",    /*< W */
    "-..-",   /*< X */
    "-.--"    /*< Y */
    "--.."    /*< Z */

    ".-.-.-", /*< . */
    "--..--", /*< , */
    "..--..", /*< ? */
    "-..-.",  /*< / */
    ".--.-."  /*< @ */
};

/**
 * @brief Função que dada uma string em morse, repete o padrão no led.
 *
 * @param letter string com pontos e traços que representa a letra a ser
 * transmitida.
 */
void transmit_from_str(char *letter) {
  int i = 0;

  while (letter[i] != '\0') { /** Enquanto a string não acabou... */

    digitalWrite(LED_PIN, HIGH); /** Liga o LED */

    if (letter[i] == '.') { /** Escolhe o tempo para o ponto ou o traço. */
      delay(DOT_DELAY);
    } else if (letter[i] == '-') {
      delay(DASH_DELAY);
    }

    digitalWrite(LED_PIN, LOW);   /** Desliga o LED */
    delay(IN_LETTER_SPACE_DELAY); /** Dá o tempo necessário entre pontos e
                                     traços de uma letra. */

    i++;
  }
}

/**
 * @brief Camada de abstração da função de transmição.
 *
 * @param letter Letra enumerada a ser transmitida.
 * @param is_last Indica se esta letra é o fim de uma palavra.
 */
void transmit_letter(letter_t letter, bool is_last) {
  transmit_from_str(letters[letter]);
  if (is_last) {
    delay(WORD_SPACE_DELAY); /** Caso seja a última letra, dá o tempo de um fim
                                de palavra*/
  } else {
    delay(OUT_LETTER_SPACE_DELAY); /** Caso seja uma letra interna da palavra*/
  }
}

/**
 * @brief Exemplo de função que envia uma palavra.
 *
 */
void transmit_sos() {
  transmit_letter(S, false);
  transmit_letter(O, false);
  transmit_letter(S, true);
}

void setup() { pinMode(LED_PIN, OUTPUT); }

void loop() {
  transmit_from_str(letters[S]);
  delay(OUT_LETTER_SPACE_DELAY);

  transmit_from_str(letters[O]);
  delay(OUT_LETTER_SPACE_DELAY);

  transmit_from_str(letters[S]);
  delay(WORD_SPACE_DELAY);

  transmit_sos();
}