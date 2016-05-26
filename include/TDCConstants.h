#ifndef TDCConstants_h
#define TDCConstants_h

#define TDC_NUM_CHANNELS      32
#define TDC_FIRMWARE_VERSION  0x8470DACE // for HPTDCv1.3

#define TDC_SETUP_BITS_NUM    647
#define TDC_CONTROL_BITS_NUM  40
#define TDC_BS_BITS_NUM       83
#define TDC_STATUS_BITS_NUM   62
#define TDC_ICT_BITS_NUM      749

#define FPGA_SETUP_ADDR       0x0
#define FPGA_CONTROL_ADDR     0x1
#define FPGA_STATUS_ADDR      0x2
#define FPGA_HPTDCID_ADDR     0x3

#endif
