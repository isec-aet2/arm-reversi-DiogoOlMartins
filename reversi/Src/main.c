/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stm32f769i_discovery_lcd.h"
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_ts.h"
#include "jogadas.h"
#include "logotipo.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TEMP_REFRESH_PERIOD   1000    /* Internal temperature refresh period */
#define MAX_CONVERTED_VALUE   4095    /* Max converted value */
#define AMBIENT_TEMP            25    /* Ambient Temperature */
#define VSENS_AT_AMBIENT_TEMP  760    /* VSENSE value (mv) at ambient temperature */
#define AVG_SLOPE               25    /* Avg_Solpe multiply by 10 */
#define VREF                   3300



/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

DMA2D_HandleTypeDef hdma2d;

DSI_HandleTypeDef hdsi;

LTDC_HandleTypeDef hltdc;

SD_HandleTypeDef hsd2;

TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

SDRAM_HandleTypeDef hsdram1;

/* USER CODE BEGIN PV */
volatile uint32_t ConvertedValue = 0;
volatile unsigned int segundos = 0;
volatile unsigned int TEMPFLAG = 0;
volatile unsigned int timeout = 20;
int timeoutCountPlayer1 = 3;
int timeoutCountPlayer2 = 3;
volatile unsigned int flagToca = 1;
volatile unsigned int fl_gamestart = 0;
volatile unsigned int japassouaqui = 0;
volatile unsigned int japassouaqui1 = 0; //fl_gamestart
volatile unsigned int japassouaqui2 = 0; //ja passou no mostrar as possiveis
int jogador = 1;
int aiFlag=0;
int tocouX = 0;
int tocouXAnterior = 0;
int tocouY = 0;
unsigned int minutos = 0;//minutos
unsigned int reset = 0;//flag de reset
char tempoAMostrar[SIZE];
char c[SIZE];
char d[SIZE];
int comecarTimoeut = 0;
unsigned int menuFlag = 1;
pfnode list = NULL;


fnode tabuleiro[TAMMATRIZ][TAMMATRIZ];
fnode poss_list[SIZE];
fnode poss_atual;
int indexPoss_list=0;

TS_StateTypeDef TS_State; //coordenadas do ts




/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_DMA2D_Init(void);
static void MX_DSIHOST_DSI_Init(void);
static void MX_FMC_Init(void);
static void MX_LTDC_Init(void);
static void MX_SDMMC2_SD_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM7_Init(void);
/* USER CODE BEGIN PFP */

void LCD_Config(void);
void showTime(void);
void touch_screen_config(void);
void temp(void);
void jogo(void);
void LCD_GameOn(void);
void fazerReset(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */




  /* USER CODE END 1 */
  

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_DMA2D_Init();
  MX_DSIHOST_DSI_Init();
  MX_FMC_Init();
  MX_LTDC_Init();
  MX_SDMMC2_SD_Init();
  MX_TIM4_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */
  //lcd enable
  LCD_Config();
  //adc enable
  HAL_ADC_Start(&hadc1);
  //ts enable
  touch_screen_config();
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim7);




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  //se tocou no ecrã delay
		if (flagToca == 1) {
			HAL_Delay(200);
			flagToca = 0;
		}
		//mostra o primeiro e o segundo ecrâ, faz tambem a cells selection recognition
		menuInicial();

		if (TEMPFLAG >= 2){//para mostrar de dois em dois segundos
			temp();
		}
			showTime();//mostra o tempo

		if (fl_gamestart == 1) {//depois de passar nos menus começa o jogo

			if (japassouaqui1 == 0) {//só passa aqui uma vez
				japassouaqui1 = 1;
				LCD_GameOn();//cria a matriz e mostra no ecrâ
				mostraJogador(2);//mostra quem está a jogar
				fl_gamestart = 0;//reset a flag
				comecarTimoeut=1;
				HAL_TIM_Base_Start_IT(&htim7);//para começar o timeout
			}


			if(aiFlag==1 && jogador==2){// se for para jogar contra o computador
				meteJogAI();
			}else
				jogo();//não deve ser preciso comentar

		}

		if (reset == 1) {//flag de reset
			HAL_Delay(200);
			fazerReset();

		}

	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC|RCC_PERIPHCLK_SDMMC2
                              |RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV2;
  PeriphClkInitStruct.PLLSAIDivQ = 1;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
  PeriphClkInitStruct.Sdmmc2ClockSelection = RCC_SDMMC2CLKSOURCE_CLK48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_DMA2D_Init(void)
{

  /* USER CODE BEGIN DMA2D_Init 0 */

  /* USER CODE END DMA2D_Init 0 */

  /* USER CODE BEGIN DMA2D_Init 1 */

  /* USER CODE END DMA2D_Init 1 */
  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  hdma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA;
  hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DMA2D_Init 2 */

  /* USER CODE END DMA2D_Init 2 */

}

/**
  * @brief DSIHOST Initialization Function
  * @param None
  * @retval None
  */
static void MX_DSIHOST_DSI_Init(void)
{

  /* USER CODE BEGIN DSIHOST_Init 0 */

  /* USER CODE END DSIHOST_Init 0 */

  DSI_PLLInitTypeDef PLLInit = {0};
  DSI_HOST_TimeoutTypeDef HostTimeouts = {0};
  DSI_PHY_TimerTypeDef PhyTimings = {0};
  DSI_LPCmdTypeDef LPCmd = {0};
  DSI_CmdCfgTypeDef CmdCfg = {0};

  /* USER CODE BEGIN DSIHOST_Init 1 */

  /* USER CODE END DSIHOST_Init 1 */
  hdsi.Instance = DSI;
  hdsi.Init.AutomaticClockLaneControl = DSI_AUTO_CLK_LANE_CTRL_DISABLE;
  hdsi.Init.TXEscapeCkdiv = 4;
  hdsi.Init.NumberOfLanes = DSI_ONE_DATA_LANE;
  PLLInit.PLLNDIV = 20;
  PLLInit.PLLIDF = DSI_PLL_IN_DIV1;
  PLLInit.PLLODF = DSI_PLL_OUT_DIV1;
  if (HAL_DSI_Init(&hdsi, &PLLInit) != HAL_OK)
  {
    Error_Handler();
  }
  HostTimeouts.TimeoutCkdiv = 1;
  HostTimeouts.HighSpeedTransmissionTimeout = 0;
  HostTimeouts.LowPowerReceptionTimeout = 0;
  HostTimeouts.HighSpeedReadTimeout = 0;
  HostTimeouts.LowPowerReadTimeout = 0;
  HostTimeouts.HighSpeedWriteTimeout = 0;
  HostTimeouts.HighSpeedWritePrespMode = DSI_HS_PM_DISABLE;
  HostTimeouts.LowPowerWriteTimeout = 0;
  HostTimeouts.BTATimeout = 0;
  if (HAL_DSI_ConfigHostTimeouts(&hdsi, &HostTimeouts) != HAL_OK)
  {
    Error_Handler();
  }
  PhyTimings.ClockLaneHS2LPTime = 28;
  PhyTimings.ClockLaneLP2HSTime = 33;
  PhyTimings.DataLaneHS2LPTime = 15;
  PhyTimings.DataLaneLP2HSTime = 25;
  PhyTimings.DataLaneMaxReadTime = 0;
  PhyTimings.StopWaitTime = 0;
  if (HAL_DSI_ConfigPhyTimer(&hdsi, &PhyTimings) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DSI_ConfigFlowControl(&hdsi, DSI_FLOW_CONTROL_BTA) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DSI_SetLowPowerRXFilter(&hdsi, 10000) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DSI_ConfigErrorMonitor(&hdsi, HAL_DSI_ERROR_NONE) != HAL_OK)
  {
    Error_Handler();
  }
  LPCmd.LPGenShortWriteNoP = DSI_LP_GSW0P_DISABLE;
  LPCmd.LPGenShortWriteOneP = DSI_LP_GSW1P_DISABLE;
  LPCmd.LPGenShortWriteTwoP = DSI_LP_GSW2P_DISABLE;
  LPCmd.LPGenShortReadNoP = DSI_LP_GSR0P_DISABLE;
  LPCmd.LPGenShortReadOneP = DSI_LP_GSR1P_DISABLE;
  LPCmd.LPGenShortReadTwoP = DSI_LP_GSR2P_DISABLE;
  LPCmd.LPGenLongWrite = DSI_LP_GLW_DISABLE;
  LPCmd.LPDcsShortWriteNoP = DSI_LP_DSW0P_DISABLE;
  LPCmd.LPDcsShortWriteOneP = DSI_LP_DSW1P_DISABLE;
  LPCmd.LPDcsShortReadNoP = DSI_LP_DSR0P_DISABLE;
  LPCmd.LPDcsLongWrite = DSI_LP_DLW_DISABLE;
  LPCmd.LPMaxReadPacket = DSI_LP_MRDP_DISABLE;
  LPCmd.AcknowledgeRequest = DSI_ACKNOWLEDGE_DISABLE;
  if (HAL_DSI_ConfigCommand(&hdsi, &LPCmd) != HAL_OK)
  {
    Error_Handler();
  }
  CmdCfg.VirtualChannelID = 0;
  CmdCfg.ColorCoding = DSI_RGB888;
  CmdCfg.CommandSize = 640;
  CmdCfg.TearingEffectSource = DSI_TE_EXTERNAL;
  CmdCfg.TearingEffectPolarity = DSI_TE_RISING_EDGE;
  CmdCfg.HSPolarity = DSI_HSYNC_ACTIVE_LOW;
  CmdCfg.VSPolarity = DSI_VSYNC_ACTIVE_LOW;
  CmdCfg.DEPolarity = DSI_DATA_ENABLE_ACTIVE_HIGH;
  CmdCfg.VSyncPol = DSI_VSYNC_FALLING;
  CmdCfg.AutomaticRefresh = DSI_AR_ENABLE;
  CmdCfg.TEAcknowledgeRequest = DSI_TE_ACKNOWLEDGE_DISABLE;
  if (HAL_DSI_ConfigAdaptedCommandMode(&hdsi, &CmdCfg) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DSI_SetGenericVCID(&hdsi, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DSIHOST_Init 2 */

  /* USER CODE END DSIHOST_Init 2 */

}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};
  LTDC_LayerCfgTypeDef pLayerCfg1 = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 7;
  hltdc.Init.VerticalSync = 3;
  hltdc.Init.AccumulatedHBP = 14;
  hltdc.Init.AccumulatedVBP = 5;
  hltdc.Init.AccumulatedActiveW = 654;
  hltdc.Init.AccumulatedActiveH = 485;
  hltdc.Init.TotalWidth = 660;
  hltdc.Init.TotalHeigh = 487;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 0;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 0;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  pLayerCfg.Alpha = 0;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0;
  pLayerCfg.ImageWidth = 0;
  pLayerCfg.ImageHeight = 0;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg1.WindowX0 = 0;
  pLayerCfg1.WindowX1 = 0;
  pLayerCfg1.WindowY0 = 0;
  pLayerCfg1.WindowY1 = 0;
  pLayerCfg1.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  pLayerCfg1.Alpha = 0;
  pLayerCfg1.Alpha0 = 0;
  pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg1.FBStartAdress = 0;
  pLayerCfg1.ImageWidth = 0;
  pLayerCfg1.ImageHeight = 0;
  pLayerCfg1.Backcolor.Blue = 0;
  pLayerCfg1.Backcolor.Green = 0;
  pLayerCfg1.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

/**
  * @brief SDMMC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDMMC2_SD_Init(void)
{

  /* USER CODE BEGIN SDMMC2_Init 0 */

  /* USER CODE END SDMMC2_Init 0 */

  /* USER CODE BEGIN SDMMC2_Init 1 */

  /* USER CODE END SDMMC2_Init 1 */
  hsd2.Instance = SDMMC2;
  hsd2.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd2.Init.ClockBypass = SDMMC_CLOCK_BYPASS_DISABLE;
  hsd2.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd2.Init.BusWide = SDMMC_BUS_WIDE_1B;
  hsd2.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd2.Init.ClockDiv = 0;
  /* USER CODE BEGIN SDMMC2_Init 2 */

  /* USER CODE END SDMMC2_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 0;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 9999;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 9999;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 9999;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 9999;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/* FMC initialization function */
static void MX_FMC_Init(void)
{

  /* USER CODE BEGIN FMC_Init 0 */

  /* USER CODE END FMC_Init 0 */

  FMC_SDRAM_TimingTypeDef SdramTiming = {0};

  /* USER CODE BEGIN FMC_Init 1 */

  /* USER CODE END FMC_Init 1 */

  /** Perform the SDRAM1 memory initialization sequence
  */
  hsdram1.Instance = FMC_SDRAM_DEVICE;
  /* hsdram1.Init */
  hsdram1.Init.SDBank = FMC_SDRAM_BANK2;
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_32;
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_1;
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_DISABLE;
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 16;
  SdramTiming.ExitSelfRefreshDelay = 16;
  SdramTiming.SelfRefreshTime = 16;
  SdramTiming.RowCycleDelay = 16;
  SdramTiming.WriteRecoveryTime = 16;
  SdramTiming.RPDelay = 16;
  SdramTiming.RCDDelay = 16;

  if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
  {
    Error_Handler( );
  }

  /* USER CODE BEGIN FMC_Init 2 */

  /* USER CODE END FMC_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();

  /*Configure GPIO pin : PI13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : PI15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
void showTime(void){


	sprintf(tempoAMostrar,"Time:%02d:%02d",minutos,segundos);


if(segundos>59){
	minutos++;
	segundos=0;
}
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt(TAMLCDX-QUADRADO*3,(uint16_t)Font24.Height+10 ,(uint8_t *)tempoAMostrar, LEFT_MODE);
	BSP_LCD_SetFont(&Font24);

	if(comecarTimoeut==1){
		sprintf(d,"Timeout:%02d",timeout);
		BSP_LCD_SetFont(&Font16);
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_DisplayStringAt(QUADRADO * 11,QUADRADO * 5.25 ,(uint8_t *)d, LEFT_MODE);
		BSP_LCD_SetFont(&Font24);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		if (timeout == 0) {
			timeout = 20;
			if (jogador == 1) {
				timeoutCountPlayer1--;
				//jogador = 2;
			} else if (jogador == 2) {
				timeoutCountPlayer2--;
				//jogador = 1;
			}

		}


			sprintf(c,"Timeout's P1:%d",timeoutCountPlayer1);
			BSP_LCD_DisplayStringAt(QUADRADO * 11, QUADRADO * 4.75,(uint8_t *) c, LEFT_MODE);

			sprintf(c,"Timeout's P2:%d",timeoutCountPlayer2);
			BSP_LCD_DisplayStringAt(QUADRADO * 11, QUADRADO * 5.75,(uint8_t *) c, LEFT_MODE);


		if(timeoutCountPlayer1<=0){
			sendToSd(4,0,tempoAMostrar);
			fazerReset();
		}else
		if(timeoutCountPlayer2<=0){
			sendToSd(5,0,tempoAMostrar);
			fazerReset();
		}
	}

}

void temp(void) {

	long int JTemp;
	char desc[SIZE];


	HAL_StatusTypeDef status = HAL_ADC_PollForConversion(&hadc1, TEMP_REFRESH_PERIOD);
	if (status == HAL_OK) {
		ConvertedValue = HAL_ADC_GetValue(&hadc1); //get value
		JTemp = ((((ConvertedValue * VREF) / MAX_CONVERTED_VALUE)- VSENS_AT_AMBIENT_TEMP) * 10 / AVG_SLOPE) + AMBIENT_TEMP;

		/* Display the Temperature Value on the LCD */
		sprintf(desc, "Temp: %ld C", JTemp);

		BSP_LCD_SetFont(&Font16);
		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()-3*QUADRADO, TAMLCDY-QUADRADO, (uint8_t *) desc, LEFT_MODE);
		BSP_LCD_SetFont(&Font24);

	}
	TEMPFLAG=0;
}

void LCD_GameOn(void){

	int posicao=0;
	int x=0;
	int y=0;

	BSP_LCD_Clear(LCD_COLOR_BLUE);

	  for(int i=0;i<TAMMATRIZ ;i++){
		y=QUADRADO+i*QUADRADO;//
		for(int j=0;j<TAMMATRIZ ;j++){
			x=(BSP_LCD_GetXSize()/10)+j*QUADRADO;
			posicao++;
			tabuleiro[i][j].posicao=posicao;
			tabuleiro[i][j].posicaoX=x;
			tabuleiro[i][j].posicaoY=y;
			tabuleiro[i][j].jogador=0;
			tabuleiro[i][j].ja_jogada=false;
			tabuleiro[i][j].valida=false;

			BSP_LCD_SetTextColor(LCD_COLOR_DARKGREEN);	//colorChange
			BSP_LCD_FillRect(x, y, QUADRADO, QUADRADO);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_DrawRect(x, y, QUADRADO, QUADRADO);
			BSP_LCD_DrawRect(x, y, QUADRADO-1, QUADRADO-1);//fazer as linhas mais gordas
			BSP_LCD_DrawRect(x-1, y-1, QUADRADO, QUADRADO+1);//fazer as linhas mais gordas

		}
	  }

	  insereAs4inic(tabuleiro,jogador);
}

void LCD_Config(void)
{
  uint32_t  lcd_status = LCD_OK;

  /* Initialize the LCD */
  lcd_status = BSP_LCD_Init();
  while(lcd_status != LCD_OK);

  BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);

  /* Clear the LCD */
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /* Set LCD Example description */

  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  BSP_LCD_SetFont(&Font24);

}

void touch_screen_config(void){

	  BSP_TS_Init((uint16_t)BSP_LCD_GetXSize(),(uint16_t)BSP_LCD_GetYSize());
	  BSP_TS_ITConfig();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) { //comum para todos os timers

	if (htim->Instance == TIM6){
		TEMPFLAG++;
		segundos++;
	}

	if (htim->Instance == TIM7){
		timeout--;
	}

}

void redoMatriz(void){


	 for(int i=1;i<9;i++){
	         for(int j=1;j<9;j++){
	        	 inserePeca(tabuleiro[i][j].posicaoX,tabuleiro[i][j].posicaoY,tabuleiro[i][j].jogador);
	         }
		 }
}


void jogo(void){



	tocouX = TS_State.touchX[0];//guarda os pontos de contacto
	tocouY = TS_State.touchY[0];


	if(japassouaqui2==0){
		possible_move();//mostra as jogadas possiveis no ecrâ
		japassouaqui2=1;
	}
//se tocar dentro da matriz joga caso contrario not
	if (tocouX > LIMITE_ESQUERDO && tocouX < LIMITE_DIREITO && tocouY > LIMITE_SUPERIOR && tocouY < LIMITE_INFERIOR && tocouX!=tocouXAnterior){

		if(jogouValida(tocouX,tocouY,poss_list,indexPoss_list)==1){//só pode jogar nas validas
			poss_atual=getPosicao(tabuleiro,tocouX, tocouY);// guarda o lugar na matriz da jogada
			poss_array_erasor();//apaga as jogadas possiveis
			inserePecaNaMatriz();//insere a peça na matris mas não a imprime no ecrã
			tocouXAnterior=tocouX;//guarda a jogada anterior para
			mostraJogador(jogador);//mostra a "bola" do jogador
			place();//troca as peças consuante a jogada
			redoMatriz();//percorre o array e insere as bolas corretas no sitio correto


			japassouaqui2=0;
			//troca o jogador
			if(jogador==1)
				jogador=2;
			else if(jogador==2)
				jogador=1;
			checkIfGameEnded();//se o jogo acabou manda os dados para o sd e ativa a flag de reset
		}
	}
	else
		return;
}


void meteJogAI(void){

	HAL_Delay(200);

	possible_move();
	int jogada=0;

	jogada=randomizado(indexPoss_list);

	poss_atual=getPosicao(tabuleiro,poss_list[jogada].posicaoX, poss_list[jogada].posicaoY);
	poss_array_erasor();
	inserePecaNaMatriz();
	mostraJogador(jogador);
	place();
	redoMatriz();
	jogador=1;

}




void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){ // interrupção


	if (GPIO_Pin == GPIO_PIN_0){		//interrupt do botao
		reset=1;
	}

	 if(flagToca == 0) {
		flagToca = 1;
		if (GPIO_Pin == GPIO_PIN_13) {
			timeout=20;
			BSP_TS_GetState(&TS_State);
		}
	}

}


void menuInicial(void){
	char reversi [SIZE]={"REVERSI"};
	char gameStart[SIZE]={"START GAME"};
	char playerVSplayer[SIZE]={"2 PLAYERS"};
	char playerVSai[SIZE]={"VS AI"};

	tocouX = TS_State.touchX[0];
	tocouY = TS_State.touchY[0];


	// verifica se carregou no start game
	if (tocouX > CENTROX - QUADRADO * 2
			&& tocouX < CENTROX - QUADRADO * 2 + QUADRADO * 4
			&& tocouY > QUADRADO * 4 && tocouY < QUADRADO * 5
			&& flagToca == 0) {
		menuFlag=3;
	}else if (tocouX > QUADRADO && tocouX < QUADRADO * 4 && tocouY > QUADRADO*3 - 15
				&& tocouY < QUADRADO*3 - 15 + QUADRADO && flagToca == 0)	//verifica se carregou no 2 players
		{

			menuFlag=2;
			fl_gamestart=1;

		}else if(tocouX > TAMLCDX-QUADRADO*4 && tocouX < TAMLCDX-QUADRADO*4+QUADRADO*3 && tocouY > QUADRADO*3 - 15
				&& tocouY < QUADRADO*3 - 15 + QUADRADO && flagToca == 0){
			aiFlag=1;
			menuFlag=2;
			fl_gamestart=1;

		}


	switch(menuFlag){

	case 1:

		BSP_LCD_Clear(LCD_COLOR_BLUE);
		BSP_LCD_SetFont(&Font24);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_SetBackColor(LCD_COLOR_BLUE);


		BSP_LCD_DrawRect(CENTROX-QUADRADO*2-1, QUADRADO-15-1, QUADRADO*4+1, QUADRADO+1);
		BSP_LCD_DrawRect(CENTROX-QUADRADO*2-2, QUADRADO-15-2, QUADRADO*4+2, QUADRADO+2);
		BSP_LCD_DrawRect(CENTROX-QUADRADO*2+1, QUADRADO-15+1, QUADRADO*4-1, QUADRADO-1);
		BSP_LCD_DrawRect(CENTROX-QUADRADO*2+2, QUADRADO-15+2, QUADRADO*4-2, QUADRADO-2);
		BSP_LCD_DrawRect(CENTROX-QUADRADO*2, QUADRADO-15, QUADRADO*4, QUADRADO);

		BSP_LCD_DisplayStringAt(0,QUADRADO, (uint8_t *) reversi, CENTER_MODE);

		BSP_LCD_DrawRect(CENTROX-QUADRADO*2-1, QUADRADO*4-15-1, QUADRADO*4+1, QUADRADO+1);
		BSP_LCD_DrawRect(CENTROX-QUADRADO*2-2, QUADRADO*4-15-2, QUADRADO*4+2, QUADRADO+2);
		BSP_LCD_DrawRect(CENTROX-QUADRADO*2+1, QUADRADO*4-15+1, QUADRADO*4-1, QUADRADO-1);
		BSP_LCD_DrawRect(CENTROX-QUADRADO*2+2, QUADRADO*4-15+2, QUADRADO*4-2, QUADRADO-2);
		BSP_LCD_DrawRect(CENTROX-QUADRADO*2, QUADRADO*4-15, QUADRADO*4, QUADRADO);

		BSP_LCD_DisplayStringAt(0,QUADRADO*4, (uint8_t *) gameStart, CENTER_MODE);

		BSP_LCD_DrawRect(QUADRADO/2,QUADRADO/2,TAMLCDX-QUADRADO,TAMLCDY-QUADRADO);

		menuFlag=2;
		break;
	case 2:

		break;
	case 3:

		if(japassouaqui==0){
			japassouaqui=1;
		BSP_LCD_Clear(LCD_COLOR_BLUE);
		BSP_LCD_SetFont(&Font24);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_SetBackColor(LCD_COLOR_BLUE);


		BSP_LCD_DrawRect(QUADRADO+1, QUADRADO*3-15, QUADRADO*4, QUADRADO);
		BSP_LCD_DrawRect(QUADRADO+2, QUADRADO*3-15, QUADRADO*4, QUADRADO);
		BSP_LCD_DrawRect(QUADRADO-1, QUADRADO*3-15, QUADRADO*4, QUADRADO);
		BSP_LCD_DrawRect(QUADRADO-2, QUADRADO*3-15, QUADRADO*4, QUADRADO);
		BSP_LCD_DrawRect(QUADRADO, QUADRADO*3-15, QUADRADO*4, QUADRADO);

		BSP_LCD_DisplayStringAt(QUADRADO+15,QUADRADO*3, (uint8_t *) playerVSplayer, LEFT_MODE);


		BSP_LCD_DrawBitmap(TAMLCDX/2-50,TAMLCDY/2-50,(uint8_t *)stlogo);

		BSP_LCD_DrawRect(TAMLCDX-QUADRADO*4+1, QUADRADO*3-15, QUADRADO*3, QUADRADO);
		BSP_LCD_DrawRect(TAMLCDX-QUADRADO*4+2, QUADRADO*3-15, QUADRADO*3, QUADRADO);
		BSP_LCD_DrawRect(TAMLCDX-QUADRADO*4-1, QUADRADO*3-15, QUADRADO*3, QUADRADO);
		BSP_LCD_DrawRect(TAMLCDX-QUADRADO*4-2, QUADRADO*3-15, QUADRADO*3, QUADRADO);
		BSP_LCD_DrawRect(TAMLCDX-QUADRADO*4, QUADRADO*3-15, QUADRADO*3, QUADRADO);

		BSP_LCD_DisplayStringAt(TAMLCDX-QUADRADO*4+15,QUADRADO*3, (uint8_t *) playerVSai, LEFT_MODE);

		menuFlag=2;
		break;
		}
	}

}

void fazerReset(void){
/*	ConvertedValue = 0;
	segundos = 0;
	TEMPFLAG = 0;
	timeout = 20;
	timeoutCountPlayer1 = 3;
	timeoutCountPlayer2 = 3;

	flagToca = 0;
	fl_gamestart = 0;
	japassouaqui = 0;
	japassouaqui1 = 0;
	jogador = 1;
	//tocouX = 0;
	tocouXAnterior = 0;
	//tocouY = 0;
	minutos = 0;
	reset = 0;

	comecarTimoeut = 0;
	menuFlag = 1;
	free(list);
	list = NULL;*/

	NVIC_SystemReset();//mais engraçado assim
}







 void possible_move(void){



    int e;
    if(jogador==1)
    	e=2;
    else if(jogador==2)
    	e=1;

    indexPoss_list=0;
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if((tabuleiro[i][j].ja_jogada==false)&&(tabuleiro[i-1][j-1].jogador==e || tabuleiro[i-1][j].jogador==e || tabuleiro[i-1][j+1].jogador==e ||tabuleiro[i][j-1].jogador==e ||
            		tabuleiro[i][j+1].jogador== e || tabuleiro[i+1][j-1].jogador==e || tabuleiro[i+1][j].jogador==e || tabuleiro[i+1][j+1].jogador==e)){


				poss_capt_h(e,jogador,i,j);
                poss_capt_v(e,jogador,i,j);
                poss_capt_dp(e,jogador,i,j);
                poss_capt_ds(e,jogador,i,j);
            }
        }
    }
    poss_array_printer();
}

 void poss_capt_h(int e,int p,int i,int j){


     int m,val,poss= i*10+j;

     for(m=j+2; m<9; m++){
         if(tabuleiro[i][j+1].jogador==e && tabuleiro[i][m].jogador==p){
             val=check_reps(poss);
             if(val==0){
                poss_list[indexPoss_list]=tabuleiro[i][j];
                indexPoss_list++;
                break;
             }
         } else if(tabuleiro[i][m].ja_jogada==false){
                break;
         }
     }

    for(m=j-2; m>0; m--){
         if(tabuleiro[i][j-1].jogador==e && tabuleiro[i][m].jogador==p){
             val=check_reps(poss);
             if(val==0){
                poss_list[indexPoss_list]=tabuleiro[i][j];
                indexPoss_list++;
                break;
             }
         } else if(tabuleiro[i][m].ja_jogada==false){
                break;
         }
     }


 }


 void poss_capt_v(int e,int p,int i,int j){

	    int m,val,poss= i*10+j;

	     for(m=i+2; m<9; m++){
	         if(tabuleiro[i+1][j].jogador==e && tabuleiro[m][j].jogador==p){
	             val=check_reps(poss);
	             if(val==0){
	                poss_list[indexPoss_list]=tabuleiro[i][j];
	                indexPoss_list++;
	                break;
	             }
	         } else if(tabuleiro[m][j].ja_jogada==false){
	                break;
	         }
	     }

	    for(m=i-2; m>0; m--){
	         if(tabuleiro[i-1][j].jogador==e && tabuleiro[m][j].jogador==p){
	             val=check_reps(poss);
	             if(val==0){
	                poss_list[indexPoss_list]=tabuleiro[i][j];
	                indexPoss_list++;
	                break;
	             }
	         } else if(tabuleiro[m][j].ja_jogada==false){
	                break;
	         }
	     }
 }

 void poss_capt_dp(int e,int p,int i,int j){



     int m,n,val,poss= i*10+j;

     for(m=i+2, n=j+2 ; m<9 || n<9; m++, n++){
         if(tabuleiro[i+1][j+1].jogador==e  && tabuleiro[m][n].jogador==p){
             val=check_reps(poss);
             if(val==0){
                poss_list[indexPoss_list]=tabuleiro[i][j];
                indexPoss_list++;
                break;
             }
         } else if(tabuleiro[m][n].ja_jogada==false){
             break;
             }
     }

     for(m=i-2, n=j-2 ; m<0 || n<0; m--, n--){  //0 par test
         if(tabuleiro[i-1][j-1].jogador==e  && tabuleiro[m][n].jogador==p){
             val=check_reps(poss);
             if(val==0){
                poss_list[indexPoss_list]=tabuleiro[i][j];
                indexPoss_list++;
                break;
             }
         } else if(tabuleiro[m][n].ja_jogada==false){
             break;
             }
     }
 }

 void poss_capt_ds(int e,int p,int i,int j){

	    int m,n,val,poss= i*10+j;

	     for(m=i+2, n=j-2 ; m<9 || n>0; m++, n--){
	         if(tabuleiro[i+1][j-1].jogador==e  && tabuleiro[m][n].jogador==p){
	             val=check_reps(poss);
	             if(val==0){
	                poss_list[indexPoss_list]=tabuleiro[i+1][j-1];
	                indexPoss_list++;
	                break;
	             }
	         } else if(tabuleiro[i][m].ja_jogada==false){
	             break;
	             }
	     }

	     for(m=i-2, n=j+2 ; m>0 || n<9; m--, n++){
	         if(tabuleiro[i-1][j+1].jogador==e  && tabuleiro[m][n].jogador==p){
	             val=check_reps(poss);
	             if(val==0){
	                poss_list[indexPoss_list]=tabuleiro[i-1][j+1];
	                indexPoss_list++;
	                break;
	             }
	         } else if(tabuleiro[i][m].ja_jogada==false){
	             break;
	             }
	     }
 }


 void poss_array_printer(void){

	 for(int i=0;i<indexPoss_list;i++){
		 inserePosicaoPossivel(poss_list[i].posicaoX,poss_list[i].posicaoY,poss_list[i].jogador);
	 }

 }

 void poss_array_erasor(void){

 	 for(int i=0;i<indexPoss_list;i++){
 		limpaPosicaoPossivel(poss_list[i].posicaoX,poss_list[i].posicaoY);
 	 }
  }


 int check_reps(int jog){


     for(int i=0;i<TAMMATRIZ;i++){
         if(poss_list[i].posicao== jog){
             return 1;
         }
     }

     return 0;
 }




 void inserePecaNaMatriz(void){
	for(int i=1;i<9;i++){
		for(int j=1;j<9;j++){
			if(poss_atual.posicao==tabuleiro[i][j].posicao){
				tabuleiro[i][j].jogador=jogador;
				tabuleiro[i][j].ja_jogada=true;
				//inserePeca(tabuleiro[i][j].posicaoX,tabuleiro[i][j].posicaoY,jogador);
			}
		}
	}
 }



 void place(void){


	    int enemy;
	    if(jogador==1)
	    	enemy=2;
	    else if(jogador==2)
	    	enemy=1;

	 for(int i=1;i<9;i++){
	         for(int j=1;j<9;j++){
	        	 if(poss_atual.posicao==tabuleiro[i][j].posicao){
						 piece_changer_h(enemy,jogador,i,j);
						 piece_changer_v(enemy,jogador,i,j);
						 piece_changer_dp(enemy,jogador,i,j);
						 piece_changer_ds(enemy,jogador,i,j);
	        	 }
	         }
	 }
 }






 void piece_changer_h(int e,int p,int linha, int coluna){

  int i;

	 for(i=0;i<8;i++){
		 if(tabuleiro[linha][i+1].jogador==e){
			 if(tabuleiro[linha][i].jogador==0)
				 return;
		 	 tabuleiro[linha][i].jogador=p;
		 }
	 }

	 for(i=8;i>0;i--){
		 if(tabuleiro[linha][i-1].jogador==e){
			 if(tabuleiro[linha][i].jogador==0)
				 return;
		 	 tabuleiro[linha][i].jogador=p;
		 }
	 }

 }


 void piece_changer_v(int e,int p,int linha, int coluna){

	 int i;
	 for(i=0;i<8;i++){
	 		 if(tabuleiro[i+1][coluna].jogador==e){
	 			if(tabuleiro[i][coluna].jogador==0)
	 				return;
	 		 	 tabuleiro[i][coluna].jogador=p;
	 		 }
	 	 }

	 	 for(i=8;i>0;i--){
	 		 if(tabuleiro[i-1][coluna].jogador==e){
		 			if(tabuleiro[i][coluna].jogador==0)
		 				return;
	 			 tabuleiro[i][coluna].jogador=p;
	 		 }
	 	 }

 }

 void piece_changer_dp(int e,int p,int i, int j){

     int m,n,limiter,marker=0;

     for(m=i+2, n=j+2 ; m<9 || n<9; m++, n++){
         if(tabuleiro[i+1][j+1].jogador==e && tabuleiro[m][n].jogador==p){
             limiter=m;
             marker++;
             break;
         } else if(tabuleiro[m][n].ja_jogada==false){
                break;
         }
     }

     if(marker>0){
    	 for(m=i+2, n=j+2 ; m<limiter+2 || n<limiter+2; m++, n++){
        	 inserePeca(tabuleiro[m][n].posicaoX,tabuleiro[m][n].posicaoY,e);
        	 tabuleiro[m][n].jogador=e;

         }
     }

     marker=0;
     for(m=i-2, n=j-2 ; m<0 || n<0; m--, n--){//0 par test
         if(tabuleiro[i+1][j+1].jogador==e && tabuleiro[m][n].jogador==p){
             limiter=m;
             marker++;
             break;
         } else if(tabuleiro[m][n].ja_jogada==false){
                break;
         }
     }

     if(marker>0){
    	 for(m=i-2, n=j-2 ; m<limiter || n<limiter; m++, n++){
        	 inserePeca(tabuleiro[m][n].posicaoX,tabuleiro[m][n].posicaoY,e);
        	 tabuleiro[m][n].jogador=e;

         }
     }

 }


 void piece_changer_ds(int e,int p,int i, int j){



 }


 void checkIfGameEnded(void){

 	int count=0;
 	int countplayer1=0;
 	int countplayer2=0;

 	for (int i = 1; i < 9; i++) {
 		for (int j = 1; j < 9; j++) {

 			if (tabuleiro[i][j].ja_jogada == true)
 				count++;
 			if (tabuleiro[i][j].jogador == 1)
 				countplayer1++;
 			if (tabuleiro[i][j+1].jogador == 2)
 				countplayer2++;
 		}
 	}
 		//count=60;
 		//countplayer1=10;
 		//countplayer2=11;
 		if(count>=60){

 			if(countplayer2>countplayer1){
 				sendToSd(2,countplayer2,tempoAMostrar);
 			}else if(countplayer2<countplayer1){
 				sendToSd(1,countplayer1,tempoAMostrar);
 			}else
 				sendToSd(0,countplayer1,tempoAMostrar);
 			fazerReset();

 		}


 	}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
