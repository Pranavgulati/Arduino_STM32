#include <ardCRC.h>
crc Crc;

void crc::begin()
{
  /* Enable CRC AHB clock interface */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

  /* DeInit CRC peripheral */
  CRC_DeInit();
  CRC_ResetDR();
  /* Init the INIT register */
  CRC_SetInitRegister(0xffffffff);
  /* Select 32-bit polynomial size */
  CRC_ReverseInputDataSelect(CRC_ReverseInputData_No);
  /* Set the polynomial coefficients */
  //works only for STM32f072 devices since changing poly is not available with 
  //03 05 series mcus
  }
void crc::begin(uint32_t poly)
{
  /* Enable CRC AHB clock interface */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
  /* DeInit CRC peripheral */
  CRC_DeInit();
  CRC_ResetDR();
  /* Init the INIT register */
  CRC_SetInitRegister(0xffffffff);
  /* Select 32-bit polynomial size */
  CRC_ReverseInputDataSelect(CRC_ReverseInputData_32bits);
  /* Set the polynomial coefficients */
  //works only for STM32f072 devices since changing poly is not available with 
  //03 05 series mcus
  CRC_SetPolynomial(poly);
}
void crc::stop(){
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, DISABLE);
  
}

/*Only 32 bit input data CRC is calculated so all data must be casted to 32bits */
unsigned long int   crc::calcBlockCRC(uint32_t *CRCBuffer,uint32_t size){
return CRC_CalcBlockCRC((uint32_t *)CRCBuffer, size);

}
/*Only 32 bit input data CRC is calculated so all data must be casted to 32bits */
unsigned long int  crc::calcCRC(uint32_t CRCbuffer){
return CRC_CalcCRC(CRCbuffer);

}