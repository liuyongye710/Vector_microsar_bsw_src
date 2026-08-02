#include "CCFC3007PT.h"
#include "eDma_LLDriver.h"
 void Sysclk_Init_Firc(void)
 {
 	//if(MFSPR(SPR_PIR)==2)
 	MC_CGM.AC3_SC.B.SELCTL = 0x00;   //connect FIRC to the PLL0 input
 	MC_CGM.AC4_SC.B.SELCTL = 0x03;	 //connect PLL01 to the PLL1 input

    //MFD  8---127  RFDPHI1(4--15) RFDPHI(1---63)  PREDIV(1--7)
 	// Set PLL0_PHI1 to 40 MHz with 16MHz FIRC reference
 	// MFD = 30, PREDIV =  2, RFDPHI = 1, RFDPHI1 = 6
 	//PLLO_PHI = 16*30/2/1 = 240M(4762000 -> 400000000)
 	//PLL0_PHI1 = 16*30/2/6=40M(20000000 -> 78000000)
 	//PLL0_VCO =16*30*2/2 = 480M(400000000 -> 1250000000)
 	PLLDIG.PLL0DV.R = 0x3001201E;

 	// Set PLL1 to 600 MHz with 40MHz PLL0_PHI1 reference
 	PLLDIG.PLL1DV.R = 0x0001001E;	 // MFD = 30, RFDPHI = 1
     MC_ME.DRUN_MC.R = 0X00130010;    // DRUN cfg: PLL1OFF PLL00FF XOSCOFF,IRCON, syclk=IRC <-----DEFAULT
 	MC_ME.RUN_MC[0].R = 0x00130010;	 // RUN0 cfg: PLL1OFF PLL00FF XOSCOFF,IRCON, syclk=IRC

 	// Mode Transition to enter DRUN mode:Just to update PLL DIV
 	MC_ME.MCTL.R = 0x30005AF0;		    // Enter DRUN Mode & Key
 	MC_ME.MCTL.R = 0x3000A50F;		    // Enter DRUN Mode & Inverted Key
 	while (MC_ME.GS.B.S_MTRANS) {};		// Wait for mode transition to complete
 	while(MC_ME.GS.B.S_CURRENT_MODE != 3) {};

 	MC_ME.RUN_PC[0].R = 0x0000001E;	// enable peripherals run in RUN0 DRUN0 SAFE TEST
 	MC_ME.RUN_MC[0].R = 0x001300D4; // RUN0 cfg: PLL1ON PLL0ON XOSCOOFF,IRCON, syclk=PLL1(second primary PLL)

 	//MC_ME.PCTL[15] = 0; //configure PCTL15 register to 0 EBI_0 SIUL

 	/*! System clock divider ratios will change with next update.
 	 *  Not required for Cut 1.*/
 	MC_CGM.SC_DIV_RC.R = 0x00000001;
 	/*! System clock divider ratios updated on writing MC_CGM.DIV_UPD_TRIG.
 	 * Not required for Cut 1. */
 	MC_CGM.DIV_UPD_TYPE.R = 0x80000000;

 	// PBRIDGEA/PBRIDGEB_CLK at syst clk div by 12 ... (50 MHz)
 	MC_CGM.SC_DC2.R = 0x800B0000;
 	// SXBAR_CLK at syst clk div by 6 ... (100 MHz)
 	MC_CGM.SC_DC1.R = 0x80050000;
 	// FXBAR_CLK, BD_CLK, IOP_CLK at syst clk div by 3 ... (200 MHz)
 	MC_CGM.SC_DC0.R = 0x80020000;
 	// COMP/CHKR_CLK at syst clk div by 2 ... (300 MHz)
 	MC_CGM.SC_DC3.R = 0x80010000;
 	// CLKOUT at syst clk div by 11 ... (54.55 MHz)
 	MC_CGM.SC_DC4.R = 0x800A0000;
 	//! System clock divider ratio updates triggered.  Not required for Cut 1.
 	MC_CGM.DIV_UPD_TRIG.R = 0xfeedface;
 	//! Wait for System Clock Divider Update Status == 0. Not required for Cut 1.
 	while (MC_CGM.DIV_UPD_STAT.B.SYS_UPD_STAT == 1)
 	{

 	}
 	// Mode Transition to enter RUN0 mode:
 	MC_ME.MCTL.R = 0x40005AF0;		    // Enter RUN0 Mode & Key
 	MC_ME.MCTL.R = 0x4000A50F;		    // Enter RUN0 Mode & Inverted Key
 	while (MC_ME.GS.B.S_MTRANS) {};		// Wait for mode transition to complete
 	while(MC_ME.GS.B.S_CURRENT_MODE != 4)  // Verify RUN0 is the current mode
 	{};
 }

void Sysclk_Init_Reback(void)
{
 	MC_ME.RUN_PC[0].R = 0x00000000;// Disable peripherals run in all modes
 	MC_ME.RUN_MC[0].R = 0x00130010;// RUN0 cfg: PLL1OFF PLL00FF XOSCOFF,IRCON, syclk=IRC

 	// Mode Transition to enter RUN0 mode: Just to close PLL0/1 XOSC keep IRC0SC ON
 	MC_ME.MCTL.R = 0x40005AF0;		    // Enter RUN0 Mode & Key
 	MC_ME.MCTL.R = 0x4000A50F;		    // Enter RUN0 Mode & Inverted Key
 	while (MC_ME.GS.B.S_MTRANS) {};		// Wait for mode transition to complete
 	while(MC_ME.GS.B.S_CURRENT_MODE != 4)  // Verify RUN0 is the current mode
 	{};

 	/*! System clock divider ratios will change with next update.
 	 *  Not required for Cut 1.*/
 	MC_CGM.SC_DIV_RC.R = 0x00000001;
 	/*! System clock divider ratios updated on writing MC_CGM.DIV_UPD_TRIG.
 	 * Not required for Cut 1. */
 	MC_CGM.DIV_UPD_TYPE.R = 0x80000000;

 	MC_CGM.SC_DC2.R = 0x80000000;
 	MC_CGM.SC_DC1.R = 0x80000000;
 	MC_CGM.SC_DC0.R = 0x80000000;
 	MC_CGM.SC_DC3.R = 0x80000000;
 	MC_CGM.SC_DC4.R = 0x80000000;
 	//! System clock divider ratio updates triggered.  Not required for Cut 1.
 	MC_CGM.DIV_UPD_TRIG.R = 0xfeedface;
 	//! Wait for System Clock Divider Update Status == 0. Not required for Cut 1.
 	while (MC_CGM.DIV_UPD_STAT.B.SYS_UPD_STAT == 1)
 	{
 	}

 	MC_CGM.AC3_SC.B.SELCTL = 0x00;   //connect IRCOSC to the PLL0 input
 	MC_CGM.AC4_SC.B.SELCTL = 0x01;	 //connect XOSC to the PLL1 input

 	// RFDPHI1 = 0, RFDPHI = 0 PREDIV =  0, MFD = 8,
 	PLLDIG.PLL0DV.R = 0x00000008;
 	PLLDIG.PLL1DV.R = 0x00000010;	     // RFDPHI = 0 MFD = 10,

 	// Mode Transition to enter DRUN mode:
 	MC_ME.MCTL.R = 0x30005AF0;		    // Enter RUN0 Mode & Key
 	MC_ME.MCTL.R = 0x3000A50F;		    // Enter RUN0 Mode & Inverted Key
 	while (MC_ME.GS.B.S_MTRANS) {};		// Wait for mode transition to complete
 	while(MC_ME.GS.B.S_CURRENT_MODE != 3) {};
}

extern uint32_t __DATA_SRAM_ADDR[];
extern uint32_t __DATA_ROM_ADDR[];
extern uint32_t __DATA_SIZE;
void data_ram_copy_dma(void)
{
	if(((uint32_t)&__DATA_SIZE)>0)
	{
	DMA_0_P->TCD[0].SADDR.R = (uint32_t)__DATA_ROM_ADDR;
	DMA_0_P->TCD[0].ATTR.R = 0x0202;
	DMA_0_P->TCD[0].SOFF.R = 4;
	DMA_0_P->TCD[0].DOFF.R = 4;
	DMA_0_P->TCD[0].NBYTES.MLNO.R = (uint32_t)&__DATA_SIZE;
	DMA_0_P->TCD[0].SLAST.R = 0;
	DMA_0_P->TCD[0].DLASTSGA.R = 0;
	DMA_0_P->TCD[0].DADDR.R = (uint32_t)__DATA_SRAM_ADDR;
	DMA_0_P->TCD[0].CITER.ELINKNO.R = 0x01;
	DMA_0_P->TCD[0].BITER.ELINKNO.R = 0x01;
	DMA_0_P->TCD[0].CSR.R = 0x0;

	DMA_0_P->SERQ.R = 0;

	DMA_0_P->TCD[0].CSR.R |= 0x1;
	while((DMA_0_P->TCD[0].CSR.R & 0x80) != 0x80);
	DMA_0_P->CERQ.R = 0;
	}

}