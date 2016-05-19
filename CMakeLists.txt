file(GLOB tdc_sources src/TDC*.cpp)

add_library(mb_lib SHARED ${tdc_sources})
set_property(TARGET mb_lib PROPERTY LINK_FLAGS "-L${QUSB_LIB_LOCATION} -lquickusb -Wl,-R${QUSB_LIB_LOCATION}")
