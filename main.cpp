//#include <iostream>
#include <cstdio>

// Default buttons states (LOW/HIGH)
#define buttonOneDefaultState false
#define buttonTwoDefaultState false

// DeepSleep timer (mks)
#define deepSleepTime 30

// Last value
bool buttonOneLastState = false;
bool buttonTwoLastState = false;

void DeepSleep()
{
    //ESP.deepSleep(deepSleepTime);
    
    printf("Я ушел спать\n\n");
}

/*------------------------------------------------------------------------------------------*/

void StartupSettings()
{
    // Enable pin and setting pinMode
    //pinMode(2, INPUT); // Enable pin for first button
    //pinMode(4, INPUT); // Enable pin for second button
    printf("Я запустился\n");
    printf("Я включил пины\n");
    printf("Я выключил wifi и ble\n");
    printf("-----------------------------\n\n");
    //Serial.begin(9600);
}

void setup()
{
    StartupSettings();
}

int ButtonChanges(){
    int buttonOneState = false;
    int buttonTwoState = false;

    if (buttonOneState == true) {
        if (buttonTwoState == true) {
        return 2;
        } else {
        return 1;
        }
    } else if (buttonTwoState == true) return 2;
    else return 0;
}

int main()
{
    setup();
    char buttonState = 0; //ButtonChanges(); // для иммитации считывания с кнопки
    for (int i = 0; i<3; i++){ 
        //char buttonState = ButtonChanges(); // для считывания изменений с кнопки
        buttonState = buttonState + 1; // для иммитации считывания с кнопки
        if (buttonState != 0){
            if (buttonState == 1 && buttonOneLastState == false){
                printf("Итерация %d\n", buttonState); // для иммитации считывания с кнопки
                printf("Бак заполнен на 40%%\n");
                printf("-----------------------------\n");
                printf("Данные отправлены на сервер\n");
                printf("-----------------------------\n");
                buttonOneLastState = true;
            }
            if (buttonState == 2 && buttonTwoLastState == false){
                printf("Итерация %d\n", buttonState); // для иммитации считывания с кнопки
                printf("Бак заполнен на 70%%\n");
                printf("-----------------------------\n");
                printf("Данные отправлены на сервер\n");
                printf("-----------------------------\n");
                buttonTwoLastState = true;
            }
        } else {
            buttonOneLastState = false; // Для записи в файл для очистки
            buttonTwoLastState = false;
        }
        
        DeepSleep();
    } // Цикл для иммитации нескольких проверок работы
}