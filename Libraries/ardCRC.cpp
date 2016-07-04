#include <ardCRC.h>
crc Crc;

void crc::begin(uint32_t poly)
{
  /* Enable CRC AHB clock interface */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

  /* DeInit CRC peripheral */
  CRC_DeInit();
  
  /* Init the INIT register */
  CRC_SetInitRegister(0);
  
  /* Select 32-bit polynomial size */
  CRC_PolynomialSizeSelect(CRC_PolSize_32);
  
  /* Set the polynomial coefficients */
  CRC_SetPolynomial(poly);
}


unsigned long int   crc::calcBlockCRC(uint32_t *CRCBuffer,uint32_t size){
return CRC_CalcBlockCRC((uint32_t *)CRCBuffer, size);

}