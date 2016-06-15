/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Cpu.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z64VLK4
**     Component   : MKL25Z128LK4
**     Version     : Component 01.025, Driver 01.04, CPU db: 3.00.000
**     Datasheet   : KL25P80M48SF0RM, Rev.3, Sep 2012
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-09-30, 00:36, # CodeGen: 57
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         No public methods
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file Cpu.c
** @version 01.04
** @brief
**
*/         
/*!
**  @addtogroup Cpu_module Cpu module documentation
**  @{
*/         

/* MODULE Cpu. */

/* {Default RTOS Adapter} No RTOS includes */
#include "TPM1.h"
#include "CMP0.h"
#include "TPM2.h"
#include "WAIT1.h"
#include "PIT.h"
#include "PTB.h"
#include "PTD.h"
#include "CS1.h"
#include "TPM0.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Events.h"
#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 

/* Global variables */
volatile uint8_t SR_reg;               /* Current value of the FAULTMASK register */
volatile uint8_t SR_lock = 0x00U;      /* Lock */


/*
** ===================================================================
**     Method      :  Cpu_INT_LVD_LVWInterrupt (component MKL25Z128LK4)
**
**     Description :
**         This ISR services the 'Low-voltage' interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_INT_LVD_LVWInterrupt)
{
  uint8_t Reason = 0x00U;              /* Defines the source of Low voltage interrupt */

  if ((PMC_LVDSC1 & PMC_LVDSC1_LVDF_MASK) != 0x00U) {
    PMC_LVDSC1 |= PMC_LVDSC1_LVDACK_MASK;
    Reason |= LVDSRC_LVD;
  }
  if ((PMC_LVDSC2 & PMC_LVDSC2_LVWF_MASK) != 0x00U) {
    PMC_LVDSC2 |= PMC_LVDSC2_LVWACK_MASK;
    Reason |= LVDSRC_LVW;
  }
  Cpu_OnLowVoltageINT(Reason);
}

/*
** ===================================================================
**     Method      :  Cpu_INT_NMIInterrupt (component MKL25Z128LK4)
**
**     Description :
**         This ISR services the Non Maskable Interrupt interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_INT_NMIInterrupt)
{
  Cpu_OnNMIINT();
}

/*
** ===================================================================
**     Method      :  Cpu_INT_MCGInterrupt (component MKL25Z128LK4)
**
**     Description :
**         This ISR services the 'Loss of Lock' interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_INT_MCGInterrupt)
{
  /* MCG_S: LOLS0=1,LOCK0=0,PLLST=0,IREFST=0,CLKST=0,OSCINIT0=0,IRCST=0 */
  MCG_S = (MCG_S_LOLS0_MASK | MCG_S_CLKST(0x00)); /* Clear Loss of Lock status flag */
  Cpu_OnLossOfLockINT();
}

/*
** ===================================================================
**     Method      :  Cpu_INT_Hard_FaultInterrupt (component MKL25Z128LK4)
**
**     Description :
**         This ISR services the 'hard fault' interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_INT_Hard_FaultInterrupt)
{
  Cpu_OnHardFault();
}

/*
** ===================================================================
**     Method      :  Cpu_INT_SVCallInterrupt (component MKL25Z128LK4)
**
**     Description :
**         This ISR services the 'Supervisor call' interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_INT_SVCallInterrupt)
{
  Cpu_OnSupervisorCall();
}

/*
** ===================================================================
**     Method      :  Cpu_INT_PendableSrvReqInterrupt (component MKL25Z128LK4)
**
**     Description :
**         This ISR services the 'PendableService' interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_INT_PendableSrvReqInterrupt)
{
  Cpu_OnPendableService();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_Reserved4 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_Reserved4)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_Reserved5 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_Reserved5)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_Reserved6 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_Reserved6)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_Reserved7 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_Reserved7)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_Reserved8 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_Reserved8)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_Reserved9 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_Reserved9)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_Reserved10 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_Reserved10)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_Reserved12 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_Reserved12)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_Reserved13 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_Reserved13)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_SysTick (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_SysTick)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_DMA0 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_DMA0)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_DMA1 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_DMA1)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_DMA2 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_DMA2)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_DMA3 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_DMA3)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_Reserved20 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_Reserved20)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_FTFA (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_FTFA)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_LLW (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_LLW)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_I2C0 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_I2C0)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_I2C1 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_I2C1)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_SPI0 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_SPI0)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_SPI1 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_SPI1)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_UART0 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_UART0)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_UART1 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_UART1)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_UART2 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_UART2)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_ADC0 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_ADC0)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_TPM0 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_TPM0)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_RTC (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_RTC)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_RTC_Seconds (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_RTC_Seconds)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_Reserved39 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_Reserved39)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_USB0 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_USB0)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_DAC0 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_DAC0)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_TSI0 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_TSI0)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_LPTimer (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_LPTimer)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_Reserved45 (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_Reserved45)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_PORTA (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_PORTA)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}

/*
** ===================================================================
**     Method      :  Cpu_Cpu_ivINT_PORTD (component MKL25Z128LK4)
**
**     Description :
**         This ISR services an unused interrupt/exception vector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_ivINT_PORTD)
{
  /* This code can be changed using the CPU component property "Build Options / Unhandled int code" */
  PE_DEBUGHALT();
}


/*** !!! Here you can place your own code using property "User data declarations" on the build options tab. !!! ***/

/*lint -esym(765,__init_hardware) Disable MISRA rule (8.10) checking for symbols (__init_hardware). The function is linked to the EWL library */
/*lint -esym(765,Cpu_Interrupt) Disable MISRA rule (8.10) checking for symbols (Cpu_Interrupt). */
void __init_hardware(void)
{

  /*** !!! Here you can place your own code before PE initialization using property "User code before PE initialization" on the build options tab. !!! ***/

  /*** ### MKL25Z64VLK4 "Cpu" init code ... ***/
  /*** PE initialization code after reset ***/
  SCB_VTOR = (uint32_t)(&__vect_table); /* Set the interrupt vector table position */
  /* Disable the WDOG module */
  /* SIM_COPC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COPT=0,COPCLKS=0,COPW=0 */
  SIM_COPC = SIM_COPC_COPT(0x00);                                   

  /* System clock initialization */
  /* SIM_CLKDIV1: OUTDIV1=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,OUTDIV4=3,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SIM_CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(0x00) | SIM_CLKDIV1_OUTDIV4(0x03)); /* Set the system prescalers to safe value */
  /* SIM_SCGC5: PORTE=1,PORTD=1,PORTC=1,PORTA=1 */
  SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK |
               SIM_SCGC5_PORTD_MASK |
               SIM_SCGC5_PORTC_MASK |
               SIM_SCGC5_PORTA_MASK;   /* Enable clock gate for ports to enable pin routing */
  if ((PMC_REGSC & PMC_REGSC_ACKISO_MASK) != 0x0U) {
    /* PMC_REGSC: ACKISO=1 */
    PMC_REGSC |= PMC_REGSC_ACKISO_MASK; /* Release IO pads after wakeup from VLLS mode. */
  }
  /* SIM_CLKDIV1: OUTDIV1=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,OUTDIV4=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SIM_CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(0x01) | SIM_CLKDIV1_OUTDIV4(0x01)); /* Update system prescalers */
  /* SIM_SOPT2: PLLFLLSEL=1 */
  SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; /* Select PLL as a clock source for various peripherals */
  /* SIM_SOPT1: OSC32KSEL=3 */
  SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0x03); /* LPO 1kHz oscillator drives 32 kHz clock for various peripherals */
  /* SIM_SOPT2: TPMSRC=1 */
  SIM_SOPT2 = (uint32_t)((SIM_SOPT2 & (uint32_t)~(uint32_t)(
               SIM_SOPT2_TPMSRC(0x02)
              )) | (uint32_t)(
               SIM_SOPT2_TPMSRC(0x01)
              ));                      /* Set the TPM clock */
  /* PORTA_PCR18: ISF=0,MUX=0 */
  PORTA_PCR18 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));                                   
  /* PORTA_PCR19: ISF=0,MUX=0 */
  PORTA_PCR19 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));                                   
  /* Switch to FBE Mode */
  /* MCG_C2: LOCRE0=0,??=0,RANGE0=2,HGO0=1,EREFS0=1,LP=0,IRCS=0 */
  MCG_C2 = (MCG_C2_RANGE0(0x02) | MCG_C2_HGO0_MASK | MCG_C2_EREFS0_MASK);                                   
  /* OSC0_CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  OSC0_CR = OSC_CR_ERCLKEN_MASK;                                   
  /* MCG_C1: CLKS=2,FRDIV=4,IREFS=0,IRCLKEN=0,IREFSTEN=0 */
  MCG_C1 = (MCG_C1_CLKS(0x02) | MCG_C1_FRDIV(0x04));                                   
  /* MCG_C4: DMX32=0,DRST_DRS=0 */
  MCG_C4 &= (uint8_t)~(uint8_t)((MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS(0x03)));                                   
  /* MCG_C5: ??=0,PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=2 */
  MCG_C5 = MCG_C5_PRDIV0(0x02);                                   
  /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
  MCG_C6 = MCG_C6_VDIV0(0x00);                                   
  while((MCG_S & MCG_S_IREFST_MASK) != 0x00U) { /* Check that the source of the FLL reference clock is the external reference clock. */
  }
  while((MCG_S & 0x0CU) != 0x08U) {    /* Wait until external reference clock is selected as MCG output */
  }
  /* Switch to PBE Mode */
  /* MCG_C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=0 */
  MCG_C6 = (MCG_C6_PLLS_MASK | MCG_C6_VDIV0(0x00));                                   
  while((MCG_S & 0x0CU) != 0x08U) {    /* Wait until external reference clock is selected as MCG output */
  }
  while((MCG_S & MCG_S_LOCK0_MASK) == 0x00U) { /* Wait until locked */
  }
  /* Switch to PEE Mode */
  /* MCG_C1: CLKS=0,FRDIV=4,IREFS=0,IRCLKEN=0,IREFSTEN=0 */
  MCG_C1 = (MCG_C1_CLKS(0x00) | MCG_C1_FRDIV(0x04));                                   
  while((MCG_S & 0x0CU) != 0x0CU) {    /* Wait until output of the PLL is selected */
  }
  /* MCG_C6: CME0=1 */
  MCG_C6 |= MCG_C6_CME0_MASK;          /* Enable the clock monitor */
  /* MCG_C6: LOLIE0=1 */
  MCG_C6 |= MCG_C6_LOLIE0_MASK;        /* Enable the loss of lock interrupt */
  /*** End of PE initialization code after reset ***/

  /*** !!! Here you can place your own code after PE initialization using property "User code after PE initialization" on the build options tab. !!! ***/

}



/*
** ===================================================================
**     Method      :  PE_low_level_init (component MKL25Z128LK4)
**
**     Description :
**         Initializes beans and provides common register initialization. 
**         The method is called automatically as a part of the 
**         application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PE_low_level_init(void)
{
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
      /* Initialization of the SIM module */
  /* SIM_SCGC7: DMA=1 */
  SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;                                   
  /* SIM_SCGC4: SPI1=0,SPI0=0,CMP=1,USBOTG=0,UART2=0,UART1=0,UART0=0,I2C1=0,I2C0=0 */
  SIM_SCGC4 = (uint32_t)((SIM_SCGC4 & (uint32_t)~(uint32_t)(
               SIM_SCGC4_SPI1_MASK |
               SIM_SCGC4_SPI0_MASK |
               SIM_SCGC4_USBOTG_MASK |
               SIM_SCGC4_UART2_MASK |
               SIM_SCGC4_UART1_MASK |
               SIM_SCGC4_UART0_MASK |
               SIM_SCGC4_I2C1_MASK |
               SIM_SCGC4_I2C0_MASK
              )) | (uint32_t)(
               SIM_SCGC4_CMP_MASK
              ));                                  
  /* SIM_SCGC5: PORTE=1,PORTD=1,PORTC=1,PORTB=0,PORTA=1,TSI=0,LPTMR=0 */
  SIM_SCGC5 = (uint32_t)((SIM_SCGC5 & (uint32_t)~(uint32_t)(
               SIM_SCGC5_PORTB_MASK |
               SIM_SCGC5_TSI_MASK |
               SIM_SCGC5_LPTMR_MASK
              )) | (uint32_t)(
               SIM_SCGC5_PORTE_MASK |
               SIM_SCGC5_PORTD_MASK |
               SIM_SCGC5_PORTC_MASK |
               SIM_SCGC5_PORTA_MASK
              ));                                  
  /* SIM_SCGC6: DAC0=0,RTC=0,ADC0=0,TPM2=1,TPM1=1,TPM0=1,PIT=0,DMAMUX=0,FTF=1 */
  SIM_SCGC6 = (uint32_t)((SIM_SCGC6 & (uint32_t)~(uint32_t)(
               SIM_SCGC6_DAC0_MASK |
               SIM_SCGC6_RTC_MASK |
               SIM_SCGC6_ADC0_MASK |
               SIM_SCGC6_PIT_MASK |
               SIM_SCGC6_DMAMUX_MASK
              )) | (uint32_t)(
               SIM_SCGC6_TPM2_MASK |
               SIM_SCGC6_TPM1_MASK |
               SIM_SCGC6_TPM0_MASK |
               SIM_SCGC6_FTF_MASK
              ));                                  
        /* Initialization of the FTFL_FlashConfig module */
      /* Initialization of the PMC module */
  /* PMC_LVDSC1: LVDACK=1,LVDIE=1,LVDRE=1,LVDV=0 */
  PMC_LVDSC1 = (uint8_t)((PMC_LVDSC1 & (uint8_t)~(uint8_t)(
                PMC_LVDSC1_LVDV(0x03)
               )) | (uint8_t)(
                PMC_LVDSC1_LVDACK_MASK |
                PMC_LVDSC1_LVDIE_MASK |
                PMC_LVDSC1_LVDRE_MASK
               ));                                  
  /* PMC_LVDSC2: LVWACK=1,LVWIE=1,LVWV=0 */
  PMC_LVDSC2 = (uint8_t)((PMC_LVDSC2 & (uint8_t)~(uint8_t)(
                PMC_LVDSC2_LVWV(0x03)
               )) | (uint8_t)(
                PMC_LVDSC2_LVWACK_MASK |
                PMC_LVDSC2_LVWIE_MASK
               ));                                  
  /* PMC_REGSC: BGEN=1,ACKISO=0,BGBE=1 */
  PMC_REGSC = (uint8_t)((PMC_REGSC & (uint8_t)~(uint8_t)(
               PMC_REGSC_ACKISO_MASK
              )) | (uint8_t)(
               PMC_REGSC_BGEN_MASK |
               PMC_REGSC_BGBE_MASK
              ));                                  
  /* SMC_PMPROT: ??=0,??=0,AVLP=0,??=0,ALLS=0,??=0,AVLLS=0,??=0 */
  SMC_PMPROT = 0x00U;                  /* Setup Power mode protection register */
  /* Common initialization of the CPU registers */
  /* NVIC_ISER: SETENA|=0x08450040 */
  NVIC_ISER |= NVIC_ISER_SETENA(0x08450040);                                   
  /* NVIC_IPR4: PRI_19=0x80,PRI_18=0x40,PRI_17=0,PRI_16=0 */
  NVIC_IPR4 = NVIC_IP_PRI_19(0x80) |
              NVIC_IP_PRI_18(0x40) |
              NVIC_IP_PRI_17(0x00) |
              NVIC_IP_PRI_16(0x00);       
  /* PORTC_PCR6: ISF=0,MUX=0 */
  PORTC_PCR6 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));                                   
  /* PORTC_PCR7: ISF=0,MUX=0 */
  PORTC_PCR7 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));                                   
  /* PORTE_PCR30: ISF=0,MUX=0 */
  PORTE_PCR30 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));                                   
  /* PORTE_PCR29: ISF=0,MUX=0 */
  PORTE_PCR29 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));                                   
  /* NVIC_IPR5: PRI_22=0 */
  NVIC_IPR5 &= (uint32_t)~(uint32_t)(NVIC_IP_PRI_22(0xFF));                                   
  /* PORTD_PCR1: ISF=0,MUX=4 */
  PORTD_PCR1 = (uint32_t)((PORTD_PCR1 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x03)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x04)
               ));                                  
  /* PORTD_PCR2: ISF=0,MUX=4 */
  PORTD_PCR2 = (uint32_t)((PORTD_PCR2 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x03)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x04)
               ));                                  
  /* PORTC_PCR8: ISF=0,MUX=3 */
  PORTC_PCR8 = (uint32_t)((PORTC_PCR8 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x04)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x03)
               ));                                  
  /* NVIC_IPR1: PRI_6=0 */
  NVIC_IPR1 &= (uint32_t)~(uint32_t)(NVIC_IP_PRI_6(0xFF));                                   
  /* NVIC_IPR6: PRI_27=0 */
  NVIC_IPR6 &= (uint32_t)~(uint32_t)(NVIC_IP_PRI_27(0xFF));                                   
  /* SCB_SHPR2: PRI_11=0 */
  SCB_SHPR2 &= (uint32_t)~(uint32_t)(SCB_SHPR2_PRI_11(0xFF));                                   
  /* SCB_SHPR3: PRI_14=0 */
  SCB_SHPR3 &= (uint32_t)~(uint32_t)(SCB_SHPR3_PRI_14(0xFF));                                   
  /* ### Init_TPM "TPM1" init code ... */
  /* ### Call "TPM1_Init();" init method in a user code, i.e. in the main code */

  /* ### Note:   To enable automatic calling of the "TPM1" init code here,
                 the 'Call Init method' property must be set to 'yes'.
   */
  /* ### Init_HSCMP "CMP0" init code ... */
  /* ### Call "CMP0_Init();" init method in a user code, i.e. in the main code */

  /* ### Note:   To enable automatic calling of the "CMP0" init code here,
                 the 'Call Init method' property must be set to 'yes'.
   */
  /* ### Init_TPM "TPM2" init code ... */
  /* ### Call "TPM2_Init();" init method in a user code, i.e. in the main code */

  /* ### Note:   To enable automatic calling of the "TPM2" init code here,
                 the 'Call Init method' property must be set to 'yes'.
   */
  /* ### Init_PIT "PIT" init code ... */
  /* ### Call "PIT_Init();" init method in a user code, i.e. in the main code */

  /* ### Note:   To enable automatic calling of the "PIT" init code here,
                 the 'Call Init method' property must be set to 'yes'.
   */
  /* ### Init_GPIO "PTB" init code ... */
  PTB_Init();
  /* ### Init_GPIO "PTD" init code ... */
  PTD_Init();
  /* ### CriticalSection "CS1" init code ... */
  /* ### Init_TPM "TPM0" init code ... */
  TPM0_Init();
  __EI();
}
  /* Flash configuration field */
  __attribute__ ((section (".cfmconfig"))) const uint8_t _cfm[0x10] = {
   /* NV_BACKKEY3: KEY=0xFF */
    0xFFU,
   /* NV_BACKKEY2: KEY=0xFF */
    0xFFU,
   /* NV_BACKKEY1: KEY=0xFF */
    0xFFU,
   /* NV_BACKKEY0: KEY=0xFF */
    0xFFU,
   /* NV_BACKKEY7: KEY=0xFF */
    0xFFU,
   /* NV_BACKKEY6: KEY=0xFF */
    0xFFU,
   /* NV_BACKKEY5: KEY=0xFF */
    0xFFU,
   /* NV_BACKKEY4: KEY=0xFF */
    0xFFU,
   /* NV_FPROT3: PROT=0xFF */
    0xFFU,
   /* NV_FPROT2: PROT=0xFF */
    0xFFU,
   /* NV_FPROT1: PROT=0xFF */
    0xFFU,
   /* NV_FPROT0: PROT=0xFF */
    0xFFU,
   /* NV_FSEC: KEYEN=1,MEEN=3,FSLACC=3,SEC=2 */
    0x7EU,
   /* NV_FOPT: ??=1,??=1,FAST_INIT=1,LPBOOT1=1,RESET_PIN_CFG=0,NMI_DIS=0,??=1,LPBOOT0=1 */
    0xF3U,
    0xFFU,
    0xFFU
  };

/* END Cpu. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/