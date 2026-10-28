/*
 * clocks_and_modes.c              Copyright NXP 2018
 * Description: Example clock and mode functions
 * 2015 Feb 22 S Mihalik/ O Romero - initial version
 * 2016 Oct 15 S.M. / O.R. - Updated PLL per S32K1XX data sheet rev 1
 *
 */

#include "S32K144.h"           /* include peripheral declarations S32K144 */
#include "clocks_and_modes.h"

void SOSC_init_interl(void)
{
  SCG->SOSCDIV=0x00000101;  /* SOSCDIV1 & SOSCDIV2 =1: divide by 1 */
  SCG->SOSCCFG = (2 << 4) | (1 << 2);  /* Range=2: High freq (SOSC > 8MHZ)*/
                            /* HGO=0:   Config xtal osc for low power */
                            /* EREFS=1: Input is interl osc */
  while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); /* Ensure SOSCCSR unlocked */
  SCG->SOSCCSR=0x00000001;  /* LK=0:          SOSCCSR can be written */
                            /* SOSCCMRE=0:    OSC CLK monitor IRQ if enabled */
                            /* SOSCCM=0:      OSC CLK monitor disabled */
                            /* SOSCERCLKEN=0: Sys OSC 3V ERCLK output clk disabled */
                            /* SOSCLPEN=0:    Sys OSC disabled in VLP modes */
                            /* SOSCSTEN=0:    Sys OSC disabled in Stop modes */
                            /* SOSCEN=1:      Enable oscillator */
  while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)); /* Wait for sys OSC clk valid */
}


void SOSC_init_8MHz(void)
{
  SCG->SOSCDIV=0x00000101;  /* SOSCDIV1 & SOSCDIV2 =1: divide by 1 */
  SCG->SOSCCFG=0x00000024;  /* Range=2: Medium freq (SOSC betw 1MHz-8MHz)*/
                            /* HGO=0:   Config xtal osc for low power */
                            /* EREFS=1: Input is external XTAL */
  while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); /* Ensure SOSCCSR unlocked */
  SCG->SOSCCSR=0x00000001;  /* LK=0:          SOSCCSR can be written */
                            /* SOSCCMRE=0:    OSC CLK monitor IRQ if enabled */
                            /* SOSCCM=0:      OSC CLK monitor disabled */
                            /* SOSCERCLKEN=0: Sys OSC 3V ERCLK output clk disabled */
                            /* SOSCLPEN=0:    Sys OSC disabled in VLP modes */
                            /* SOSCSTEN=0:    Sys OSC disabled in Stop modes */
                            /* SOSCEN=1:      Enable oscillator */
  while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)); /* Wait for sys OSC clk valid */
}

void SOSC_init_12MHz(void)
{
	SCG->SOSCDIV=0x00000101;  /* SOSCDIV1 & SOSCDIV2 =1: divide by 1 */
	SCG->SOSCCFG=0x00000024;  /* Range=2: Medium freq (SOSC betw 1MHz-8MHz)*/
							  /* HGO=0:   Config xtal osc for low power */
							  /* EREFS=1: Input is external XTAL */
	while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); /* Ensure SOSCCSR unlocked */
	SCG->SOSCCSR=0x00000001;  /* LK=0:			SOSCCSR can be written */
							  /* SOSCCMRE=0:	OSC CLK monitor IRQ if enabled */
							  /* SOSCCM=0:		OSC CLK monitor disabled */
							  /* SOSCERCLKEN=0: Sys OSC 3V ERCLK output clk disabled */
							  /* SOSCLPEN=0:	Sys OSC disabled in VLP modes */
							  /* SOSCSTEN=0:	Sys OSC disabled in Stop modes */
							  /* SOSCEN=1:		Enable oscillator */
	while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)); /* Wait for sys OSC clk valid */

}

void SPLL_init_160MHz_for_12MHz(void)
{
  while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
  SCG->SPLLCSR = 0x00000000;  /* SPLLEN=0: SPLL is disabled (default) */
  SCG->SPLLDIV = 0x00000301;  /* SPLLDIV1 divide by 2; SPLLDIV2 divide by 4 */
  SCG->SPLLCFG = 0x00180000;  /* PREDIV=0: Divide SOSC_CLK by 0+1=1 */
                              /* MULT=24:  Multiply sys pll by 4+24=40 */
                              /* SPLL_CLK = 8MHz / 1 * 40 / 2 = 160 MHz */
  while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
  SCG->SPLLCSR = 0x00000001; /* LK=0:        SPLLCSR can be written */
                             /* SPLLCMRE=0:  SPLL CLK monitor IRQ if enabled */
                             /* SPLLCM=0:    SPLL CLK monitor disabled */
                             /* SPLLSTEN=0:  SPLL disabled in Stop modes */
                             /* SPLLEN=1:    Enable SPLL */
  while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)); /* Wait for SPLL valid */
}




void deinit_SOSC(void)
{

	SCG->SOSCDIV=0x00000000;  /* Reset Value */
	SCG->SOSCCFG=0x00000010;  /* Reset Value */
	SCG->SOSCCSR=0x00000000;  /* Reset Value */
}

void SPLL_init_160MHz(void)
{
  while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
  SCG->SPLLCSR = 0x00000000;  /* SPLLEN=0: SPLL is disabled (default) */
  SCG->SPLLDIV = 0x00000302;  /* SPLLDIV1 divide by 2; SPLLDIV2 divide by 4 */
  SCG->SPLLCFG = 0x00180000;  /* PREDIV=0: Divide SOSC_CLK by 0+1=1 */
                              /* MULT=24:  Multiply sys pll by 4+24=40 */
                              /* SPLL_CLK = 8MHz / 1 * 40 / 2 = 160 MHz */
  while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
  SCG->SPLLCSR = 0x00000001; /* LK=0:        SPLLCSR can be written */
                             /* SPLLCMRE=0:  SPLL CLK monitor IRQ if enabled */
                             /* SPLLCM=0:    SPLL CLK monitor disabled */
                             /* SPLLSTEN=0:  SPLL disabled in Stop modes */
                             /* SPLLEN=1:    Enable SPLL */
  while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)); /* Wait for SPLL valid */
}

void deinit_SPLL(void)
{
	while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
	SCG->SPLLCSR = 0x00000000;  /* SPLLEN=0: SPLL is disabled (default) */
	SCG->SPLLDIV = 0x00000000;
	SCG->SPLLCFG = 0x00000000;
	//while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)); /* Wait for SPLL valid */
}

void NormalRUNmode_80MHz (void) 
{
	/* Change to normal RUN mode with 8MHz SOSC, 80 MHz PLL*/
  SCG->RCCR=SCG_RCCR_SCS(6)      /* PLL as clock source*/
    |SCG_RCCR_DIVCORE(1)      /* DIVCORE= 2, Core clock = 160/2 MHz = 80 MHz*/
    |SCG_RCCR_DIVBUS(1)       /* DIVBUS = 2, bus clock = 40 MHz*/
    |SCG_RCCR_DIVSLOW(2);     /* DIVSLOW = 4, SCG slow, flash clock= 20 MHz*/
  if ((SCG->CSR & SCG_CSR_SCS_MASK >> SCG_CSR_SCS_SHIFT ) != 6)
  {

  }                                 
	/* Wait for sys clk src = SPLL */
}

void NormalRUNmode_48MHz(void)
{
	/* Change to normal RUN mode with 48MHz FIRC*/
  SCG->RCCR=SCG_RCCR_SCS(3)      /* FIRC as clock source*/
    |SCG_RCCR_DIVCORE(0)      /* DIVCORE=1 */
    |SCG_RCCR_DIVBUS(0)       /* DIVBUS = 1*/
    |SCG_RCCR_DIVSLOW(1);     /* DIVSLOW = 2*/

	while ((SCG->CSR & SCG_CSR_SCS_MASK >> SCG_CSR_SCS_SHIFT ) != 6)
	{

	}
    /* Wait for sys clk src = SPLL */
}

void NormalRUNmode_40MHz(void)
{
	SCG->RCCR=SCG_RCCR_SCS(6)   // SPLL做为系统时钟源
	|SCG_RCCR_DIVCORE(3)     // DIVCORE=3, 分频/4: Core clock = 160/4 MHz = 40 MHz
	|SCG_RCCR_DIVBUS(3)      // DIVBUS=3, 分频/4: bus clock = 160/4 MHz = 40 MHz
	|SCG_RCCR_DIVSLOW(7);   // DIVSLOW=7, 分频/8: SCG slow, flash clock= 160/8 MHz = 20MHZ
	while (((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) != 6) {}//等待系统时钟源成功选择SPLL
}


void clock_out_pin(void)
{
/**
27-24
SCG Clkout Select
Selects the SCG system clock.
0000 SCG SLOW Clock
0001 System OSC (SOSC_CLK)
0010 Slow IRC (SIRC_CLK)
0011 Fast IRC (FIRC_CLK)
0100 Reserved
0101 Reserved
0110 System PLL (SPLL_CLK)
0111 Reserved
1111 Reserved
*/
	SCG->CLKOUTCNFG = 1 << 24;

	SIM->CHIPCTL &= ~SIM_CHIPCTL_CLKOUTEN_MASK; // disable CLKOUT
	SIM->CHIPCTL &= ~SIM_CHIPCTL_CLKOUTSEL_MASK; // clear CLKOUT
	SIM->CHIPCTL |= SIM_CHIPCTL_CLKOUTSEL(7); // select CLKOUT source = clkoutsel
	SIM->CHIPCTL |= SIM_CHIPCTL_CLKOUTEN_MASK; // enable CLKOUT    
}

void clock_hsrun_mode_for_8mhz(void)
{
    SCG->SOSCCFG = SCG_SOSCCFG_EREFS_MASK |     /* Selects the output of the OSC logic (crystal is used) */
            SCG_SOSCCFG_RANGE(0x03);    /* Range is very high frequency crystal (8MHz) */

    SCG->SOSCCSR &= ~SCG_SOSCCSR_LK_MASK;       /* Unlock the register */

    SCG->SOSCCSR |= SCG_SOSCCSR_SOSCEN_MASK;    /* Enable System Oscillator */

    while (0 == (SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)) { };  /* Wait until SOSC is enabled */

    SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV1(0) |    /* Disable SOSC_DIV1 and SOSC_DIV2 */
            SCG_SOSCDIV_SOSCDIV2(0);

	//PLL
	    /* PLL output = ((OSC_value) / (prediv + 1) * (mult + 16) ) / 2 */
    /* PLL output = ((8MHz) / (0 + 1) * (12 + 16) ) / 2 = 112 MHz */
    /* Configure SPLL dividers to get 112 MHz output */
    SCG->SPLLCFG = SCG_SPLLCFG_MULT(12) |
            SCG_SPLLCFG_PREDIV(0);
    /* Enable System PLL */
    SCG->SPLLCSR |= SCG_SPLLCSR_SPLLEN_MASK;
    /* Wait until SPLL is enabled */
    while (0 == (SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)) { };

    SCG->SPLLDIV = SCG_SPLLDIV_SPLLDIV1(4) |    /* SPLL_DIV1 set to 14 MHz (112MHz / 8) */
            SCG_SPLLDIV_SPLLDIV2(3);            /* SPLL_DIV2 set to 28 MHz (112MHz / 4) */

	/* Set DIVCORE value for HSRUN */
	SCG->RCCR = SCG_CSR_SCS(6) |		/* Select PLL */
			SCG_CSR_DIVCORE(0) |	/* PLL output divided by 1 to generate Core clock 112 MHz (112 MHz / 1) */
			SCG_CSR_DIVBUS(1) | 	/* Core clock divided by 2 to generate Bus clock 56 MHz (112 MHz / 2) */
			SCG_CSR_DIVSLOW(3); 	/* Core clock divided by 4 to generate Flash clock 28 MHz (112 MHz / 4) */

	/* Wait until PLL is selected to generate core, bus and flash clocks */
	while (6 != ((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT)) {}
}



//外部晶振初始化
CLOCK_CFG_ERR ext_osi_init(void)
{
	unsigned int timeout = 0;
																/* ---- INITIALIZE SYSTEM OSC. FOR 12 MHZ. CRYSTAL ----- */
	SCG->SOSCDIV = 0x00000101u; 								/* SOSCDIV1 & SOSCDIV2 =1: divide by 1					*/
	SCG->SOSCCFG = 0x00000034u; 								/* Range = 3: High freq. (SOSC > 8MHz)	   */
																/* HGO	 = 0: Configure xtal osc. for low power 		*/
																/* EREFS = 1: Input is external XTAL					*/

	//while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK);				/* Ensure SOSCCSR unlocked								*/

	SCG->SOSCCSR = 0x00000001u; 								/* LK		   = 0: SOSCCSR can be written				*/
																/* SOSCCMRE    = 0: OSC CLK monitor IRQ if enabled		*/
																/* SOSCCM	   = 0: OSC CLK monitor disabled			*/
																/* SOSCERCLKEN = 0: Sys OSC 3V ERCLK output clk disabled*/
																/* SOSCLPEN    = 0: Sys OSC disabled in VLP modes		*/
																/* SOSCSTEN    = 0: Sys OSC disabled in Stop modes		*/
																/* SOSCEN	   = 1: Enable oscillator					*/

																/* Wait for sys OSC clk valid							*/
	while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK))
	{
		timeout++;
		if (timeout >= 0x0EFFF)				//超时 外部晶振起振失败
		{
			return CLOCK_ERR_WAIT_EXTERN_OSI;
		}
	}
	return CLOCK_ERR_NONE;
}


CLOCK_CFG_ERR clock_run_mode_for_12mhz(void)
{
	unsigned int timeout = 0;
	CLOCK_CFG_ERR ret = CLOCK_ERR_NONE;

	ret = ext_osi_init();
	if (ret != CLOCK_ERR_NONE)
	{
		//return ret;
	}

																/* ---- INITIALIZE SPLL TO 111 MHZ WITH 12 MHZ SOSC ---- */
	//while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK);					/* Ensure SPLLCSR unlocked								*/
	SCG->SPLLCSR = 0x00000000u; 								/* SPLLEN	=  0: SPLL is disabled (default)			*/
	//SCG->SPLLDIV = 0x00000302u; 								/* SPLLDIV1 divide by 2; SPLLDIV2 divide by 4			*/
	SCG->SPLLDIV = SCG_SPLLDIV_SPLLDIV1(4) |	 /* SPLL_DIV1 set to 14 MHz (111MHz / 8) */
				SCG_SPLLDIV_SPLLDIV2(6);			/* SPLL_DIV2 set to 28 MHz (111MHz / 64) */

	//SCG->SPLLCFG = (1 << 8) | (0x09 << 16);

	SCG->SPLLCFG = (1 << 8) | (0x15 << 16); 					/* PREDIV	=  1: Divide SOSC_CLK by 0+1=1				*/
																/* MULT 	= 21: Multiply sys pll by 21=21+16=37		*/
																/* SPLL_CLK =  12 MHz / 2 * 37 / 2 = 111 MHz 			*/
																/* SPLL_CLK = 外部晶振 / 分频 * 倍频 / 2 */

	//while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK);					/* Ensure SPLLCSR unlocked								*/
	SCG->SPLLCSR = 0x00000001u; 								/* LK		= 0: SPLLCSR can be written 				*/
																/* SPLLCMRE = 0: SPLL CLK monitor IRQ if enabled		*/
																/* SPLLCM	= 0: SPLL CLK monitor disabled				*/
																/* SPLLSTEN = 0: SPLL disabled in Stop modes			*/
																/* SPLLEN	= 1: Enable SPLL							*/

																/* Wait for SPLL valid									*/
	while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK))
	{
		timeout++;
		if (timeout >= 0x1FFFF)
		{
			//return CLOCK_ERR_WAIT_SPLL;
		}
	}

#if 1
																/* INIT CLOCKS: 111 MHZ SYSCLK, 40 MHZ BUS, 20 MHZ FLASH */
	SCG->RCCR = SCG_RCCR_SCS(6) 								/* PLL as clock source									*/
			  | SCG_RCCR_DIVCORE(0) 						 /* DIVCORE = 1: Core clock = 111 MHz		 */
			  | SCG_RCCR_DIVBUS(1)							 /* DIVBUS	= 2: Bus clock = 56 MHz 					 */
			  | SCG_RCCR_DIVSLOW(3);						 /* DIVSLOW = 4: SCG slow, flash clock= 28 MHz		 */

#else
															/* INIT CLOCKS: 111 MHZ SYSCLK, 40 MHZ BUS, 20 MHZ FLASH */
SCG->HCCR = SCG_HCCR_SCS(6) 								/* PLL as clock source									*/
		  | SCG_HCCR_DIVCORE(0) 						 /* DIVCORE = 1: Core clock = 111 MHz		 */
		  | SCG_HCCR_DIVBUS(1)							 /* DIVBUS	= 2: Bus clock = 56 MHz 					 */
		  | SCG_HCCR_DIVSLOW(3);						 /* DIVSLOW = 4: SCG slow, flash clock= 28 MHz		 */

#endif


#if 1
	/* Wait for sys clck src = SPLL 						*/
	timeout = 0;
	while (6 != ((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT))
	{
		timeout++;
		if (timeout >= 0x1FFFF)
		{
			//return CLOCK_ERR_WAIT_SYS_SRC;
		}
	}
#endif
	return CLOCK_ERR_NONE;
}


CLOCK_CFG_ERR clock_hsrun_mode_for_12mhz(void)
{
	unsigned int timeout = 0;
	CLOCK_CFG_ERR ret = CLOCK_ERR_NONE;

	ret = ext_osi_init();
	if (ret != CLOCK_ERR_NONE)
	{
		//return ret;
	}

																/* ---- INITIALIZE SPLL TO 111 MHZ WITH 12 MHZ SOSC ---- */
	//while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK);					/* Ensure SPLLCSR unlocked								*/
	SCG->SPLLCSR = 0x00000000u; 								/* SPLLEN	=  0: SPLL is disabled (default)			*/
	//SCG->SPLLDIV = 0x00000302u; 								/* SPLLDIV1 divide by 2; SPLLDIV2 divide by 4			*/
	SCG->SPLLDIV = SCG_SPLLDIV_SPLLDIV1(4) |	 /* SPLL_DIV1 set to 14 MHz (111MHz / 8) */
				SCG_SPLLDIV_SPLLDIV2(6);			/* SPLL_DIV2 set to 28 MHz (111MHz / 64) */

	//SCG->SPLLCFG = (1 << 8) | (0x09 << 16);

	SCG->SPLLCFG = (1 << 8) | (0x15 << 16); 					/* PREDIV	=  1: Divide SOSC_CLK by 0+1=1				*/
																/* MULT 	= 21: Multiply sys pll by 21=21+16=37		*/
																/* SPLL_CLK =  12 MHz / 2 * 37 / 2 = 111 MHz 			*/
																/* SPLL_CLK = 外部晶振 / 分频 * 倍频 / 2 */

	//while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK);					/* Ensure SPLLCSR unlocked								*/
	SCG->SPLLCSR = 0x00000001u; 								/* LK		= 0: SPLLCSR can be written 				*/
																/* SPLLCMRE = 0: SPLL CLK monitor IRQ if enabled		*/
																/* SPLLCM	= 0: SPLL CLK monitor disabled				*/
																/* SPLLSTEN = 0: SPLL disabled in Stop modes			*/
																/* SPLLEN	= 1: Enable SPLL							*/

																/* Wait for SPLL valid									*/
	while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK))
	{
		timeout++;
		if (timeout >= 0x1FFFF)
		{
			//return CLOCK_ERR_WAIT_SPLL;
		}
	}

	SMC->PMPROT |= 1 << 7;	//允许进入HRUN模式
	SMC->PMCTRL |= 3 << 5;	//进入HRUN模式


#if 0
																/* INIT CLOCKS: 111 MHZ SYSCLK, 40 MHZ BUS, 20 MHZ FLASH */
	SCG->RCCR = SCG_RCCR_SCS(6) 								/* PLL as clock source									*/
			  | SCG_RCCR_DIVCORE(0) 						 /* DIVCORE = 1: Core clock = 111 MHz		 */
			  | SCG_RCCR_DIVBUS(1)							 /* DIVBUS	= 2: Bus clock = 56 MHz 					 */
			  | SCG_RCCR_DIVSLOW(3);						 /* DIVSLOW = 4: SCG slow, flash clock= 28 MHz		 */

#else
															/* INIT CLOCKS: 111 MHZ SYSCLK, 40 MHZ BUS, 20 MHZ FLASH */
SCG->HCCR = SCG_HCCR_SCS(6) 								/* PLL as clock source									*/
		  | SCG_HCCR_DIVCORE(0) 						 /* DIVCORE = 1: Core clock = 111 MHz		 */
		  | SCG_HCCR_DIVBUS(1)							 /* DIVBUS	= 2: Bus clock = 56 MHz 					 */
		  | SCG_HCCR_DIVSLOW(3);						 /* DIVSLOW = 4: SCG slow, flash clock= 28 MHz		 */

#endif


#if 1
	/* Wait for sys clck src = SPLL 						*/
	timeout = 0;
	while (6 != ((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT))
	{
		timeout++;
		if (timeout >= 0x1FFFF)
		{
			//return CLOCK_ERR_WAIT_SYS_SRC;
		}
	}
#endif
	return CLOCK_ERR_NONE;
}

void normal_run_mode_80mhz_for_8mhz(void)
{

}

void normal_run_mode_80mhz_for_12mhz(void)
{
																/* ---- INITIALIZE SYSTEM OSC. FOR 12 MHZ. CRYSTAL ----- */
	SCG->SOSCDIV = 0x00000101u;                                 /* SOSCDIV1 & SOSCDIV2 =1: divide by 1                  */
	SCG->SOSCCFG = 0x00000034u;                                 /* Range = 3: High freq. (SOSC > 8MHz)     */
	                                                            /* HGO   = 0: Configure xtal osc. for low power         */
	                                                            /* EREFS = 1: Input is external XTAL                    */

	while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK);                  /* Ensure SOSCCSR unlocked                              */

	SCG->SOSCCSR = 0x00000001u;                                 /* LK          = 0: SOSCCSR can be written              */
	                                                            /* SOSCCMRE    = 0: OSC CLK monitor IRQ if enabled      */
	                                                            /* SOSCCM      = 0: OSC CLK monitor disabled            */
	                                                            /* SOSCERCLKEN = 0: Sys OSC 3V ERCLK output clk disabled*/
	                                                            /* SOSCLPEN    = 0: Sys OSC disabled in VLP modes       */
	                                                            /* SOSCSTEN    = 0: Sys OSC disabled in Stop modes      */
	                                                            /* SOSCEN      = 1: Enable oscillator                   */

	while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK));          /* Wait for sys OSC clk valid                           */
#if 0
	                                                            /* ---- INITIALIZE SPLL TO 160 MHZ WITH 8 MHZ SOSC ---- */
	while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK);                  /* Ensure SPLLCSR unlocked                              */
	SCG->SPLLCSR = 0x00000000u;                                 /* SPLLEN   =  0: SPLL is disabled (default)            */
	SCG->SPLLDIV = 0x00000302u;                                 /* SPLLDIV1 divide by 2; SPLLDIV2 divide by 4           */
	SCG->SPLLCFG = 0x00180000u;                                 /* PREDIV   =  0: Divide SOSC_CLK by 0+1=1              */
	                                                            /* MULT     = 24: Multiply sys pll by 24=24+16=40       */
	                                                            /* SPLL_CLK =  8 MHz / 1 * 40 / 2 = 160 MHz             */

	while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK);                  /* Ensure SPLLCSR unlocked                              */
	SCG->SPLLCSR = 0x00000001u;                                 /* LK       = 0: SPLLCSR can be written                 */
	                                                            /* SPLLCMRE = 0: SPLL CLK monitor IRQ if enabled        */
	                                                            /* SPLLCM   = 0: SPLL CLK monitor disabled              */
	                                                            /* SPLLSTEN = 0: SPLL disabled in Stop modes            */
	                                                            /* SPLLEN   = 1: Enable SPLL                            */

	while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK));          /* Wait for SPLL valid                                  */
#endif
	                                                            /* INIT CLOCKS: 80 MHZ SYSCLK, 40 MHZ BUS, 20 MHZ FLASH */
    SCG->RCCR = SCG_RCCR_SCS(1)                                 /* PLL as clock source                                  */
	          | SCG_RCCR_DIVCORE(0)                          /* DIVCORE = 1: Core clock = 160/2 MHz = 80 MHz         */
	          | SCG_RCCR_DIVBUS(0)                           /* DIVBUS  = 1: Bus clock = 40 MHz                      */
	          | SCG_RCCR_DIVSLOW(0);                         /* DIVSLOW = 2: SCG slow, flash clock= 26 2/3 MHz       */

                                                                /* Wait for sys clck src = SPLL                         */
    //while (DEF_BIT_IS_CLR(SCG->CSR, BSP_CLK_BIT_SCG_CSR_SCS_SPLL));

}

void normal_run_mode_48mhz_for_firc(void)
{
	SCG->FIRCDIV = (1 << 8) | (1 << 0);
	
	SCG->FIRCCSR = (1 << 25) | (1 << 24) | (1 << 3) | (1 << 0);

	/* Change to normal RUN mode with 48MHz FIRC*/
	SCG->RCCR=SCG_RCCR_SCS(3)	   /* FIRC as clock source*/
	  |SCG_RCCR_DIVCORE(0)		/* DIVCORE=1 */
	  |SCG_RCCR_DIVBUS(0)		/* DIVBUS = 1*/
	  |SCG_RCCR_DIVSLOW(1); 	/* DIVSLOW = 2*/
}

void view_clock_reg(void)
{

}


