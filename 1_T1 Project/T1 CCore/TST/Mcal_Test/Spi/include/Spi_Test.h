/*
 * Spi_Test.h
 *
 *  Created on: 2023��8��10��
 *      Author: june
 */

#ifndef SPI_TEST_H_
#define SPI_TEST_H_


#define DSPI0_TCF_INTPRI        INTR_PRI_15
#define DSPI1_TCF_INTPRI        INTR_PRI_15
#define DSPI2_TCF_INTPRI        INTR_PRI_15
#define DSPI3_TCF_INTPRI        INTR_PRI_15
#define DSPI4_TCF_INTPRI        INTR_PRI_15
#define DSPI5_TCF_INTPRI        INTR_PRI_15
#define DSPI6_TCF_INTPRI        INTR_PRI_15
#define DSPI12_TCF_INTPRI       INTR_PRI_15


#define DSPI0_TCF_IntID          INTR_ID_262
#define DSPI1_TCF_IntID          INTR_ID_271
#define DSPI2_TCF_IntID          INTR_ID_280
#define DSPI3_TCF_IntID          INTR_ID_289
#define DSPI4_TCF_IntID          INTR_ID_298
#define DSPI5_TCF_IntID          INTR_ID_307
#define DSPI6_TCF_IntID          INTR_ID_316
#define DSPI12_TCF_IntID         INTR_ID_370


typedef void (*Spifunc)(void);
typedef struct _SpifuncMachine
{
    char *name;
    Spifunc spifunc;
}SpifuncMachine;

void spi_de_init(void);
void spi0_port_init(void);
void spi0_intc_init(void);

void spi_test(void);
void spi_0023(void);
void spi_0024(void);
void spi_0025(void);
void spi_0026(void);
void spi_0027(void);
void spi_0028(void);
void spi_0029(void);
void spi_0030(void);
void spi_0031(void);
void spi_0032(void);
void spi_0033(void);
void spi_0034(void);
void spi_0035(void);
void spi_0036(void);
void spi_0037(void);
void spi_0038(void);
void spi_0039(void);
void spi_0040(void);
void spi_0041(void);
void spi_0042(void);
void spi_0043(void);
void spi_0044(void);
void spi_0045(void);
void spi_0046(void);
void spi_0047(void);
void spi_0048(void);
void spi_0049(void);
void spi_0050(void);
void spi_0051(void);
void spi_0052(void);
void spi_0053(void);
void spi_0054(void);
void spi_0055(void);
void spi_0056(void);
void spi_0057(void);
void spi_0058(void);
void spi_0059(void);
void spi_0060(void);
void spi_0061(void);
void spi_0062(void);
void spi_0063(void);
void spi_0064(void);
void spi_0065(void);
void spi_0066(void);
void spi_0067(void);
void spi_0068(void);
void spi_0069(void);
void spi_0070(void);
void spi_0071(void);
void spi_0072(void);
void spi_0073(void);
void spi_0074(void);
void spi_0075(void);
void spi_0076(void);
void spi_0077(void);
void spi_0078(void);
void spi_0079(void);
void spi_0080(void);
void spi_0081(void);
void spi_0082(void);
void spi_0083(void);
void spi_0084(void);
void spi_0085(void);
void spi_0086(void);
void spi_0087(void);
void spi_0088(void);
void spi_0089(void);
void spi_0090(void);
void spi_0091(void);
void spi_0092(void);
void spi_0093(void);
void spi_0094(void);
void spi_0095(void);
void spi_0096(void);
void spi_0097(void);
void spi_0098(void);
void spi_0099(void);
void spi_0100(void);
void spi_0101(void);
void spi_0102(void);
void spi_0103(void);

void EnableSpiInterrupt(void);
#endif /* SPI_TEST_H_ */
