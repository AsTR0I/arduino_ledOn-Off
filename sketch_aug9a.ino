// Подключение необходимых библиотек
#include <Arduino.h>
// Определение пинов для светодиода и кнопки
const int ledPin = 9;
const int buttonPin = 2;

// Переменные для отслеживания состояний кнопки
bool lastButton = LOW;
bool currentButton = LOW;

// Флаг для отслеживания состояния светодиода
bool ledOn = false;

void setup() 
{
  Serial.begin(9600); // Инициализация последовательной связи с 9600 бод
  
  // Устанавливаем режимы пинов
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

// Функция для сглаживания дребезга контактов кнопки
bool debounce(bool last) {
  bool current = digitalRead(buttonPin);

  // Если состояние изменилось, делаем небольшую задержку и проверяем снова
  if (last != current) {
    delay(5); // Задержка для устранения дребезга
    current = digitalRead(buttonPin);
  }
    return current;
}

void loop() 
{
  // Получаем текущее состояние кнопки с использованием debounce
  currentButton = debounce(lastButton);

  // Если кнопка была нажата (переход с LOW на HIGH)
  if (lastButton == LOW && currentButton == HIGH) {
    ledOn = !ledOn; // Переключаем флаг состояния светодиода
    Serial.print("Состояние светодиода: ");
    Serial.println(ledOn ? "Включен" : "Выключен");
  }

  // Обновляем состояние последней кнопки для следующей итерации
  lastButton = currentButton;
  Serial.print("Текущее состояние кнопки: ");
  Serial.println(currentButton ? "HIGH" : "LOW");
  delay(1000);  

  // Включаем или выключаем светодиод в зависимости от флага
  digitalWrite(ledPin, ledOn);
}
