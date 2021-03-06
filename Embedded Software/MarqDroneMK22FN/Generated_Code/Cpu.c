/** ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Cpu.c
**     Project     : MarqDroneMK22FN
**     Processor   : MK22FN512VLH12
**     Component   : MK22FN512LH12
**     Version     : Component 01.048, Driver 01.00, CPU db: 3.00.000
**     Repository  : Kinetis
**     Datasheet   : K22P121M120SF7RM, Rev. 1, March 24, 2014
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-04-07, 01:47, # CodeGen: 50
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         EnableInt  - void Cpu_EnableInt(void);
**         DisableInt - void Cpu_DisableInt(void);
**
**     (c) Freescale Semiconductor, Inc.
**     2004 All Rights Reserved
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Cpu.c
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup Cpu_module Cpu module documentation
**  @{
*/         

/* MODULE Cpu. */

/* {Default RTOS Adapter} No RTOS includes */
#include "Cpu.h"
#include "Events.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
** ===================================================================
**     Method      :  Common_Init (component MK22FN512LH12)
**     Description :
**         Initialization of registers for that there is no 
**         initialization component.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if CPU_COMMON_INIT
void Common_Init(void)
{
  /* Common initialization of registers which initialization is required 
     for proper functionality of components in the project but initialization
     component which would be configuring these registers is missing 
     in the project. 
     Add associated initialization component to the project to avoid 
     initialization of registers in the Common_Init().
     Also, after reset value optimization property affects initialization of 
     registers in this method (see active generator configuration 
     Optimizations\Utilize after reset values property or enabled processor 
     component Common settings\Utilize after reset values property) */
  /* Enable clock gate of peripherals initialized in Common_Init() */
  /* SIM_SCGC5: PORTD=1,PORTC=1,PORTB=1,PORTA=1 */
  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK |
               SIM_SCGC5_PORTC_MASK |
               SIM_SCGC5_PORTB_MASK |
               SIM_SCGC5_PORTA_MASK;

  /* SIM_CLKDIV2: USBDIV=4,USBFRAC=1 */
  SIM_CLKDIV2 = (uint32_t)((SIM_CLKDIV2 & (uint32_t)~(uint32_t)(
                 SIM_CLKDIV2_USBDIV(0x03)
                )) | (uint32_t)(
                 SIM_CLKDIV2_USBDIV(0x04) |
                 SIM_CLKDIV2_USBFRAC_MASK
                ));
  /* SIM_SCGC4: USBOTG=1,UART0=1 */
  SIM_SCGC4 |= (SIM_SCGC4_USBOTG_MASK | SIM_SCGC4_UART0_MASK);
  /* SIM_SCGC5: PORTD=1,PORTC=1 */
  SIM_SCGC5 |= (SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTC_MASK);
  /* SIM_SCGC6: ADC0=1,FTM2=1,FTM1=1,FTM0=1,SPI1=1,SPI0=1,FTM3=1 */
  SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK |
               SIM_SCGC6_FTM2_MASK |
               SIM_SCGC6_FTM1_MASK |
               SIM_SCGC6_FTM0_MASK |
               SIM_SCGC6_SPI1_MASK |
               SIM_SCGC6_SPI0_MASK |
               SIM_SCGC6_FTM3_MASK;
  /* SIM_SOPT2: USBSRC=1 */
  SIM_SOPT2 |= SIM_SOPT2_USBSRC_MASK;
  /* SIM_SOPT4: FTM1CH0SRC=0 */
  SIM_SOPT4 &= (uint32_t)~(uint32_t)(SIM_SOPT4_FTM1CH0SRC(0x03));
  /* SIM_SOPT5: UART0TXSRC=0 */
  SIM_SOPT5 &= (uint32_t)~(uint32_t)(SIM_SOPT5_UART0TXSRC(0x03));
  /* NVICIP26: PRI26=0 */
  NVICIP26 = NVIC_IP_PRI26(0x00);
  /* NVICIP27: PRI27=0 */
  NVICIP27 = NVIC_IP_PRI27(0x00);
  /* NVICIP31: PRI31=0x10 */
  NVICIP31 = NVIC_IP_PRI31(0x10);
  /* NVICIP32: PRI32=0 */
  NVICIP32 = NVIC_IP_PRI32(0x00);
  /* NVICIP39: PRI39=0 */
  NVICIP39 = NVIC_IP_PRI39(0x00);
  /* NVICIP42: PRI42=0 */
  NVICIP42 = NVIC_IP_PRI42(0x00);
  /* NVICIP43: PRI43=0x10 */
  NVICIP43 = NVIC_IP_PRI43(0x10);
  /* NVICIP44: PRI44=0x30 */
  NVICIP44 = NVIC_IP_PRI44(0x30);
  /* NVICIP53: PRI53=0 */
  NVICIP53 = NVIC_IP_PRI53(0x00);
  /* NVICIP61: PRI61=0x80 */
  NVICIP61 = NVIC_IP_PRI61(0x80);
  /* NVICIP62: PRI62=0x80 */
  NVICIP62 = NVIC_IP_PRI62(0x80);
  /* NVICIP71: PRI71=0x10 */
  NVICIP71 = NVIC_IP_PRI71(0x10);
  /* NVICISER0: SETENA|=0x80000000 */
  NVICISER0 |= NVIC_ISER_SETENA(0x80000000);
  /* NVICISER1: SETENA|=0x60001C00 */
  NVICISER1 |= NVIC_ISER_SETENA(0x60001C00);
  /* NVICISER2: SETENA|=0x80 */
  NVICISER2 |= NVIC_ISER_SETENA(0x80);
  /* PORTA_PCR12: ISF=0,MUX=3 */
  PORTA_PCR12 = (uint32_t)((PORTA_PCR12 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x04)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x03)
                ));
  /* PORTA_PCR13: ISF=0,MUX=3 */
  PORTA_PCR13 = (uint32_t)((PORTA_PCR13 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x04)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x03)
                ));
  /* PORTB_PCR16: ISF=0,MUX=3 */
  PORTB_PCR16 = (uint32_t)((PORTB_PCR16 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x04)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x03)
                ));
  /* PORTB_PCR17: ISF=0,MUX=3 */
  PORTB_PCR17 = (uint32_t)((PORTB_PCR17 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x04)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x03)
                ));
  /* PORTC_PCR1: ISF=0,MUX=4 */
  PORTC_PCR1 = (uint32_t)((PORTC_PCR1 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x03)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x04)
               ));
  /* PORTC_PCR2: ISF=0,MUX=4 */
  PORTC_PCR2 = (uint32_t)((PORTC_PCR2 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x03)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x04)
               ));
  /* PORTC_PCR3: ISF=0,MUX=4 */
  PORTC_PCR3 = (uint32_t)((PORTC_PCR3 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x03)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x04)
               ));
  /* PORTC_PCR4: ISF=0,IRQC=0,LK=0,MUX=4 */
  PORTC_PCR4 = (uint32_t)((PORTC_PCR4 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_IRQC(0x0F) |
                PORT_PCR_LK_MASK |
                PORT_PCR_MUX(0x03)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x04)
               ));
  /* PORTC_PCR5: ISF=0,MUX=2 */
  PORTC_PCR5 = (uint32_t)((PORTC_PCR5 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x05)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x02)
               ));
  /* PORTC_PCR6: ISF=0,MUX=2 */
  PORTC_PCR6 = (uint32_t)((PORTC_PCR6 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x05)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x02)
               ));
  /* PORTC_PCR7: ISF=0,MUX=2 */
  PORTC_PCR7 = (uint32_t)((PORTC_PCR7 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x05)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x02)
               ));
  /* PORTC_PCR8: ISF=0,IRQC=0,LK=0,MUX=1 */
  PORTC_PCR8 = (uint32_t)((PORTC_PCR8 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_IRQC(0x0F) |
                PORT_PCR_LK_MASK |
                PORT_PCR_MUX(0x06)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x01)
               ));
  /* PORTD_DFCR: CS=0 */
  PORTD_DFCR &= (uint32_t)~(uint32_t)(PORT_DFCR_CS_MASK);
  /* PORTD_DFWR: FILT=0 */
  PORTD_DFWR &= (uint32_t)~(uint32_t)(PORT_DFWR_FILT(0x1F));
  /* PORTD_PCR3: ISF=0,IRQC=0x0A,LK=0,MUX=1 */
  PORTD_PCR3 = (uint32_t)((PORTD_PCR3 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_IRQC(0x05) |
                PORT_PCR_LK_MASK |
                PORT_PCR_MUX(0x06)
               )) | (uint32_t)(
                PORT_PCR_IRQC(0x0A) |
                PORT_PCR_MUX(0x01)
               ));
  /* PORTD_PCR4: ISF=0,IRQC=0,LK=0 */
  PORTD_PCR4 &= (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_IRQC(0x0F) |
                 PORT_PCR_LK_MASK
                );
  /* PORTD_PCR5: ISF=0,MUX=7 */
  PORTD_PCR5 = (uint32_t)((PORTD_PCR5 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK
               )) | (uint32_t)(
                PORT_PCR_MUX(0x07)
               ));
  /* PORTD_PCR6: ISF=0,MUX=7 */
  PORTD_PCR6 = (uint32_t)((PORTD_PCR6 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK
               )) | (uint32_t)(
                PORT_PCR_MUX(0x07)
               ));
  /* PORTD_PCR7: ISF=0,MUX=7 */
  PORTD_PCR7 = (uint32_t)((PORTD_PCR7 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK
               )) | (uint32_t)(
                PORT_PCR_MUX(0x07)
               ));

  /* Disable clock gate of peripherals initialized in Common_Init() */
  /* SIM_SCGC5: PORTB=0,PORTA=0 */
  SIM_SCGC5 &= (uint32_t)~(uint32_t)(
                SIM_SCGC5_PORTB_MASK |
                SIM_SCGC5_PORTA_MASK
               );
}

#endif /* CPU_COMMON_INIT */

/*
** ===================================================================
**     Method      :  Components_Init (component MK22FN512LH12)
**     Description :
**         Initialization of components (with exception for Peripheral
**         Initialization Components which are initialized in 
**         Peripherals_Init() method).
**         For example, if automatic initialization feature 
**         is enabled in LDD component then its Init method call 
**         is executed in Components_Init() method.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if CPU_COMPONENTS_INIT
void Components_Init(void)
{
  /* ### CriticalSection "CS1" init code ... */
  /* ### RingBuffer "Tx1" init code ... */
  Tx1_Init();
  /* ### RingBuffer "Rx1" init code ... */
  Rx1_Init();
  /* ### RingBuffer "RNG1" init code ... */
  RNG1_Init();
  /* ### IntFLASH "IFsh1" init code ... */
  IFsh1_Init();
}
#endif /* CPU_COMPONENTS_INIT */

/*
** ===================================================================
**     Method      :  Cpu_INT_NMIInterrupt (component MK22FN512LH12)
**
**     Description :
**         This ISR services the Non Maskable Interrupt interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_INT_NMIInterrupt)
{
  Cpu_OnNMI();
}


#ifdef __cplusplus
}
#endif

/* END Cpu. */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
