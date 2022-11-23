/**
 * @file morse-tx.ino
 * @author Paulo Roberto (pauloxrms@gmail.com/pauloroberto.santos@edge.ufal.br)
 * @brief Sketch de base para as definições do morse em Arduino.
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

void setup() {
  pinMode(LED_PIN, OUTPUT); 
}

void loop() {
  
}