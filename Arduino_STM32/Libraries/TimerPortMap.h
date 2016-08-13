 // you havee to select timer,then its clock from port and pin 

  TIM_TypeDef* portAtimMap[16]={
    TIM2,        //ch1          //conflicts with PA0,PA5,PA15
    TIM2,        //ch2          //conflicts with PA1,PB3
    TIM2,        //ch3          //conflicts with PA2,PB10
    TIM2,        //ch4          //conflicts with PA3,PB11
    TIM14,       //ch1
    TIM2,        //ch1          //conflicts with PA0,PA5,PA15
    TIM16,       //ch1          //conflicts with PA6,PB8
    TIM17,       //ch1          //conflicts with PA7,PB9
    TIM1,        //ch1
    TIM1,        //ch2
    TIM1,        //ch3
    TIM1,        //ch4
    0,           //ch etr
    0,
    0,
    TIM2,        //ch1          //conflicts with PA0,PA5,PA15
  };
  TIM_TypeDef* portBtimMap[16]={
    TIM3,        //ch3
    TIM3,        //ch4
    0,           //no timer
    TIM2,        //ch2          //conflicts with PA1,PB3
    TIM3,        //ch1
    TIM3,        //ch2
    0,           //ch1n
    0,           //ch1n
    TIM16,       //ch1          //conflicts with PA6,PB8
    TIM17,       //ch1          //conflicts with PA7,PB9
    TIM2,        //ch3          //conflicts with PA2,PB10
    TIM2,        //ch4          //conflicts with PA3,PB11
    0,           //ch bk1n
    0,           //ch1n
    TIM15,       //ch1
    TIM15        //ch2
  };
   unsigned int portAtimClkMap[16]={
    RCC_APB1Periph_TIM2,        //ch1
    RCC_APB1Periph_TIM2,        //ch2
    RCC_APB1Periph_TIM2,        //ch3
    RCC_APB1Periph_TIM2,        //ch4
    RCC_APB1Periph_TIM14,       //ch1
    RCC_APB1Periph_TIM2,        //ch1
    RCC_APB2Periph_TIM16,       //ch1
    RCC_APB2Periph_TIM17,       //ch1
    RCC_APB2Periph_TIM1,        //ch1
    RCC_APB2Periph_TIM1,        //ch2
    RCC_APB2Periph_TIM1,        //ch3
    RCC_APB2Periph_TIM1,        //ch4
    0,                          //ch etr
    0,
    0,
    RCC_APB1Periph_TIM2,        //ch1
  };
    unsigned int portBtimClkMap[16]={
    RCC_APB1Periph_TIM3,        //ch3
    RCC_APB1Periph_TIM3,        //ch4
    0,                          //no timer
    RCC_APB1Periph_TIM2,        //ch2
    RCC_APB1Periph_TIM3,        //ch1
    RCC_APB1Periph_TIM3,        //ch2
    0,                          //ch1n
    0,                          //ch1n
    RCC_APB2Periph_TIM16,       //ch1
    RCC_APB2Periph_TIM17,       //ch1
    RCC_APB1Periph_TIM2,        //ch3
    RCC_APB1Periph_TIM2,        //ch4
    0,                          //ch bk1n
    0,                          //ch1n
    RCC_APB2Periph_TIM15,       //ch1
    RCC_APB2Periph_TIM15        //ch2
  };

   unsigned int portAchMap[16]={
    1,        //ch1
    2,        //ch2
    3,        //ch3
    4,        //ch4
    1,       //ch1
    1,        //ch1
    1,       //ch1
    1,       //ch1
    1,        //ch1
    2,        //ch2
    3,        //ch3
    4,        //ch4
    0,        //ch etr
    0,
    0,
    1,        //ch1
  };
    unsigned int portBchMap[16]={
    3,        //ch3
    4,        //ch4
    0,        //no timer
    2,        //ch2
    1,        //ch1
    2,        //ch2
    0,       //ch1n
    0,       //ch1n
    1,       //ch1
    1,       //ch1
    3,        //ch3
    4,        //ch4
    0,        //ch bk1n
    0,        //ch1n
    1,       //ch1
    2        //ch2
  };
   unsigned int portAtimAFMap[16]={
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_4,
  GPIO_AF_2,
  GPIO_AF_5,
  GPIO_AF_5,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  0,
  0,
  0,
  GPIO_AF_2
  };
    unsigned int portBtimAFMap[16]={
  GPIO_AF_1,
  GPIO_AF_1,
  0,
  GPIO_AF_2,
  GPIO_AF_1,
  GPIO_AF_1,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_1,
  GPIO_AF_1,  
  };