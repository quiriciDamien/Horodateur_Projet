/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "i2c.h"
#include <stdio.h>
#include <stdlib.h>
#include "decim_to_bin.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

//Déclarations des mask
#define MASQUE_UNITE 0b00001111
#define MASK_DIZ_HMSA 0b01110000
#define MASK_DIZ_DATE 0b00110000
#define MASK_DIZ_MOIS 0b00010000

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern UART_HandleTypeDef huart2;
ADC_HandleTypeDef hadc1;

//Décalage de 1 bit sur l'adresse slave
int I2c_adress = 0b1101000<<1;

//Declaration de la variable qui va recevoir la touche appuyer
int appui_touche;

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void Reglage(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, Reglage, osPriorityNormal, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
	uint8_t aTxBuffer[10];
	uint8_t aRxBuffer[10];

	//Initialisation de la clock
	HAL_I2C_Master_Transmit(&hi2c1,I2c_adress, (uint8_t*)aTxBuffer, 8, 10000);

	aTxBuffer[0] = 0b00000000; // pointeur sur le début du registre RTC
	aTxBuffer[1] = 0b00000000; // intitalisation de l'oscillateur

	/* Infinite loop */
	  for(;;)
	  {
		  if (mode_reglage == 0)
		  {
			  printf("mode normal\n");
			  HAL_I2C_Master_Transmit(&hi2c1,I2c_adress, (uint8_t*)aTxBuffer, 1, 10000);
			  HAL_I2C_Master_Receive(&hi2c1, I2c_adress, (uint8_t*)aRxBuffer, 7, 10000);

			  //application des mask sur les secondes
			  secondes = ((aRxBuffer[0]&MASK_DIZ_HMSA)>>4) *10 +(aRxBuffer[0]&MASQUE_UNITE);

			  //application des mask sur les minutes
			  minutes = ((aRxBuffer[1]&MASK_DIZ_HMSA)>>4) *10 +(aRxBuffer[1]&MASQUE_UNITE);

			  //application des mask sur les heures
			  heures = ((aRxBuffer[2]&MASK_DIZ_HMSA)>>4) *10 +(aRxBuffer[2]&MASQUE_UNITE);

			  //affichage heures, minutes, secondes
			  printf("%dH, %dM, %dS\n", heures, minutes, secondes);
		  }
		  osDelay(1000);
	  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Reglage */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Reglage */
void Reglage(void const * argument)
{
  /* USER CODE BEGIN Reglage */
	int temp;
	int temp2;
	int champ = 1;
	int sens = 1;
	uint8_t aTxBuffer_reglage[64];
  /* Infinite loop */
  for(;;)
  {
		if (mode_reglage == 1)
		{
			printf("mode reglage\n");
			switch (g_appui_touche)
			{
				case TOUCHE_GAUCHE:
				{
					printf("changement sens\n");
					g_appui_touche = 0;
					if(sens == 1){
						sens = -1;
					}
					else{
						sens = 1;
					}
					break;
				}
				case TOUCHE_MI_GAUCHE:
				{
					printf("champ suivant\n");
					g_appui_touche = 0;
					champ ++;
					if (champ > 3)
					{
						champ = 1;
					}
					break;
				}
				case TOUCHE_MI_DROITE:
				{
					printf("changements enregistrés\n");
					g_appui_touche = 0;
					//pointeur
					aTxBuffer_reglage[0] = 0b00000000;
					//sec
					temp = secondes % 10;
					aTxBuffer_reglage[1] = temp;
					temp2 = secondes / 10;
					aTxBuffer_reglage[1] += (temp2 << 4);
					//min
					temp = minutes % 10;
					aTxBuffer_reglage[2] = temp;
					temp2 = minutes / 10;
					aTxBuffer_reglage[2] += (temp2 << 4);
					//heure
					temp = heures % 10;
					aTxBuffer_reglage[3] = temp;
					temp2 = heures / 10;
					aTxBuffer_reglage[3] += (temp2 << 4);
					//envoi
					HAL_I2C_Master_Transmit(&hi2c1, I2c_adress, (uint8_t *)aTxBuffer_reglage, 4, 100);
					mode_reglage = 0;
					break;
				}
				case APPUI_BOUTON:
				{
					printf("valeur ++\n");
					g_appui_touche = 0;
					switch (champ)
					{
						case 1:
						{
							heures += sens;
							if((heures > 23)&&(sens == 1)){
								heures = 0;
							}
							if((heures == 255)&&(sens == -1)){
								heures = 23;
							}
							break;
						}
						case 2:
						{
							minutes += sens;
							if((minutes > 59)&&(sens == 1)){
								minutes = 0;
							}
							if((minutes == 255)&&(sens == -1)){
								minutes = 59;
							}
							break;
						}
						case 3:
						{
							secondes += sens;
							if((secondes > 59)&&(sens == 1)){
								secondes = 0;
							}
							if((secondes == 255)&&(sens == -1)){
								secondes = 59;
							}
							break;
						}
					}
					break;
				}
				default:
				{
					break;
				}
			}
			printf("%dH, %dM, %dS\n", heures, minutes, secondes);

		}
    osDelay(1000);
  }
  /* USER CODE END Reglage */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
