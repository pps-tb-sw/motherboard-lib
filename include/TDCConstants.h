#ifndef TDCConstants_h
#define TDCConstants_h

#define TDC_NUM_CHANNELS      32
#define TDC_FIRMWARE_VERSION  0x8470DACE // for HPTDCv1.3

#define TDC_SETUP_BITS_NUM    647
#define TDC_CONTROL_BITS_NUM  40
#define TDC_BS_BITS_NUM       83
#define TDC_STATUS_BITS_NUM   62

#define FPGA_SET_SETUP_HDR    0x50
#define FPGA_GET_SETUP_HDR    0x51
#define FPGA_GET_CONTROL_HDR  0x52
#define FPGA_GET_STATUS_HDR   0x54

#endif
