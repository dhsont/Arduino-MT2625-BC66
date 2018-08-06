/*
 * INO.c
 *  Created on: 12.07.2018
 *      Author: Georgi Angelov
 */

#include <Arduino.h>

/* TIMER TEST */
TimerHandle_t timer;
void timer_callback(TimerHandle_t xTimer) {
	TRACE("[API] timer_callback( %u ) %d", xTimer, millis());
}

/* TASK TEST */
TaskHandle_t WizIO_TaskHandle;
static portTASK_FUNCTION( WizIO_Task, pvParameters) {
	timer = xTimerCreate("WizIO TIMER", 1000 /* 10 sec */, 1, NULL, timer_callback);
	xTimerGenericCommand(timer, 1, 0, 0, 0);
	TRACE("[API] xTimerGenericCommand( %u )", timer);
	while (1) {
		TRACE("[API] pcTaskGetTaskName() %s", pcTaskGetTaskName(WizIO_TaskHandle));
		vTaskDelay(3000); // 30 sec
	}
}

String S;
void setup() {
	S = "Arduino ";
	S += "2018 Georgi Angelov";
	TRACE("[INO] %s", S.c_str());
	int r = xTaskGenericCreate(WizIO_Task, "WizIO TASK", 1024, NULL, TASK_PRIORITY_NORMAL, &WizIO_TaskHandle, NULL, NULL);
	TRACE("[API] xTaskGenericCreate( %d )", r);
	Serial.begin(115200);
	Serial.println(S);
	Serial.println("[INO] Quectel BC66 LTE NB-IoT");
	pinMode(LED, OUTPUT);
}

void loop() {
	static int count = 0;
	Serial.print("[INO] SERIAL TEST: ");
	Serial.println(millis());
	delay(500);
	digitalWrite(LED, count ^ 1);
	if (++count % 10) {
		TRACE("[APP] LOOP: %d", millis());
	}
}
