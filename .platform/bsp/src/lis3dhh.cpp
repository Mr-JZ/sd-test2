#include "stm32l4xx_hal.h"

/* --Check if SPI is enabled. */
#ifdef HAL_SPI_MODULE_ENABLED
#include "lis3dhh.h"
#include "cmsis_os.h"

#ifdef DEBUG
#include <cstdio>
#endif


#define SETBIT(reg, bit)   do {(reg) |=  (bit);} while(0)
#define CLEARBIT(reg, bit) do {(reg) &= ~(bit);} while(0)

// CTRL_REG1
#define NORM_MOD_EN   (0x01 << 7)
#define IF_ADD_INC    (0x01 << 6)
#define BOOT          (0x01 << 3)
#define SW_RESET      (0x01 << 2)
#define DRDY_PULSE    (0x01 << 1)
#define BDU           (0x01 << 0)


// CTRL_REG4
#define MUST4         (0x01 << 0)
#define FIFO_EN       (0x01 << 1)
#define PP_OD_INT1    (0x01 << 2)
#define PP_OD_INT2    (0x01 << 3)
#define ST(x)         (((x) & 0x03) << 4)  // SelfTest
#define DSP_BW_SEL    (0x01 << 6)
#define DSP_LP_TYPE   (0x01 << 7)



namespace Platform {

namespace BSP {

LIS3DHH::LIS3DHH(SPI_HandleTypeDef* intf, Platform::BSP::PortPin select):
		SSPDevice(intf,select)
{
    /* Enable SPI peripheral */
//    __HAL_SPI_ENABLE(interface);
    uint8_t whoami = 0;
    ctrl(Register::WHO_AM_I, whoami);
#ifdef DEBUG
    printf("ACC Sensor ID: %d\n", (int)whoami);
#endif

}


bool LIS3DHH::reset() const
{
	uint8_t ctrl_reg1 = 0;
	SETBIT(ctrl_reg1, SW_RESET);
	bool ret = cmd(Register::CTRL_REG1, ctrl_reg1);
	return ret;
}

bool LIS3DHH::control(Mode m, GRange gr) const {

	bool ret = true;
	/* --Get current mode. */
	uint8_t ctrl_reg1 = 0;
	uint8_t ctrl_reg4 = 1;

	 if (ret) ret = ctrl(Register::CTRL_REG1, ctrl_reg1);
    // if (ret) ret = ctrl(Register::CTRL_REG4, ctrl_reg4);
	 ctrl_reg1 = 0;

    // Default:
	SETBIT(ctrl_reg1, NORM_MOD_EN);
	SETBIT(ctrl_reg1, IF_ADD_INC);
	SETBIT(ctrl_reg1, BOOT);
	CLEARBIT(ctrl_reg1, SW_RESET);
	CLEARBIT(ctrl_reg1, DRDY_PULSE);
	SETBIT(ctrl_reg1, BDU);


	SETBIT(ctrl_reg4, MUST4);
	CLEARBIT(ctrl_reg4, FIFO_EN);
	SETBIT(ctrl_reg4, PP_OD_INT1);
	SETBIT(ctrl_reg4, PP_OD_INT2);
	CLEARBIT(ctrl_reg4, ST(3));
	CLEARBIT(ctrl_reg4, DSP_BW_SEL);
	CLEARBIT(ctrl_reg4, DSP_LP_TYPE);

	/* --Ok? */
	if (ret) {
//		/* --Set mode  bits in CTRL_REG1[3] and CTRL_REG4[3] */
//		switch (m) {
//		case Mode::LOWPOWER:
//			SETBIT(ctrl_reg1, LPen);
//			CLEARBIT(ctrl_reg4, HR);
//			break;
//		case Mode::NORMAL:
//			CLEARBIT(ctrl_reg1, LPen);
//			CLEARBIT(ctrl_reg4, HR);
//			break;
//		case Mode::HighRes:
//			CLEARBIT(ctrl_reg1, LPen);
//			SETBIT(ctrl_reg4, HR);
//			break;
//		default: // switch to normal mode
//			CLEARBIT(ctrl_reg1, LPen);
//			CLEARBIT(ctrl_reg4, HR);
//
//		}
//		/* --Set g-range CTRL_REG4[4:5] 2 bits. */
//		CLEARBIT(ctrl_reg4, FS(3));  // clear bits
//		SETBIT(ctrl_reg4, FS(static_cast<uint8_t>(gr)));  // clear bits
//
		if (ret)  ret = cmd(Register::CTRL_REG1, ctrl_reg1);
		if (ret)  ret = cmd(Register::CTRL_REG4, ctrl_reg4);
//
//		if (ret)  ret = setTiming(Timing::NORMAL_10);
	}

	/* --Done. */
	return ret;
}

bool LIS3DHH::setTiming(Timing t) const
{
	/* --Get current mode. */
	uint8_t ctrl_reg1 = 0;
	bool ret = ctrl(Register::CTRL_REG1, ctrl_reg1);
	if(ret)
	{
		uint8_t val = static_cast<uint8_t>(t); // Timing contains bit pattern for ODR
		(void) val;
//		CLEARBIT(ctrl_reg1, ODR(0xF));  // clear bits
//	    SETBIT(ctrl_reg1, ODR(val));  // set CTRL_REG1[4:7] ODR0-ODR3
//		ret = cmd(Register::CTRL_REG1, ctrl_reg1);
	}
	return ret;
}




uint8_t LIS3DHH::status() const {
	uint8_t value=0xff;
	bool success = ctrl(Register::STATUS_REG,value);
	return success?value: 0x00;
}

bool LIS3DHH::raw(int16_t& x, int16_t& y, int16_t& z) const {
	/* --Check if new data is available. */
//	while ((status()&0x40)==0);

	bool ret = true;
	uint32_t len=7;
	uint8_t buffer[7]; // 2 bytes per channel + register
	buffer[0]=static_cast<uint8_t>(Register::OUT_X_L);
	buffer[0] |= 0x80;  // set read mode!
	//buffer[0] |= 0x40;  // set multiple reads!
	len = sizeof(buffer);
	ret = read(buffer, len);
	if(ret)
	{
		x = buffer[1] + (buffer[2] << 8);
		y = buffer[3] + (buffer[4] << 8);
		z = buffer[5] + (buffer[6] << 8);
	}
	return ret;
}


bool LIS3DHH::getXacc(int16_t&x) const
{
	uint8_t buffer[2] = {0}; // 2 bytes per channel + register

	bool    ret = ctrl(Register::OUT_X_L, buffer[0]);
	if(ret) ret = ctrl(Register::OUT_X_H, buffer[1]);
	x = buffer[0] +((uint16_t)buffer[1] << 8 );
	return ret;
}

bool LIS3DHH::getYacc(int16_t&y) const
{
	uint8_t buffer[2] = {0}; // 2 bytes per channel + register

	bool    ret = ctrl(Register::OUT_Y_L, buffer[0]);
	if(ret) ret = ctrl(Register::OUT_Y_H, buffer[1]);
	y = buffer[0] +((uint16_t)buffer[1] << 8 );
	return ret;
}

bool LIS3DHH::getZacc(int16_t&z) const
{
	uint8_t buffer[2] = {0}; // 2 bytes per channel + register

	bool    ret = ctrl(Register::OUT_Z_L, buffer[0]);
	if(ret) ret = ctrl(Register::OUT_Z_H, buffer[1]);
	z = buffer[0] +((uint16_t)buffer[1] << 8 );
	return ret;
}




template<typename T>
bool LIS3DHH::cmd(T cmd, uint8_t value) const{
	uint32_t len=2;
	uint8_t buffer[len];
	buffer[0]=static_cast<uint8_t>(cmd);
	buffer[1]=value;
	/* --Write 2 bytes at once. */

	bool ret =  write(buffer,len);
	osDelay(100);
	return ret;
}

template<typename T>
bool LIS3DHH::ctrl(T ctrl, uint8_t& value) const
{
	bool ret = true;
	uint32_t len=2;
	uint8_t buffer[sizeof(value) + 1];
	buffer[0]=static_cast<uint8_t>(ctrl);
	buffer[0] |= 0x80;  // set read mode!
	ret = read((buffer), len);
	if(ret)
	{
	   value = buffer[1];
	}

	return ret;
}

template<typename T>
bool LIS3DHH::ctrl(T ctrl, uint16_t& value) const
{
	bool ret = true;
	uint32_t len=3;
	uint8_t buffer[sizeof(value) + 1];
	buffer[0]=static_cast<uint8_t>(ctrl);
	buffer[0] |= 0x80;  // set read mode!
	buffer[0] |= 0x40;  // set multiple reads!
	ret = read(buffer, len); // send read command
	if (ret)
	{
		value = buffer[1] + (buffer[2] << 8);
	}
	return ret;
}




void LIS3DHH::openTemp() const
{
    uint8_t config5 = 0x40;
    (void)config5;
    		//LIS3DHHTR_REG_TEMP_ADC_PD_ENABLED |
            //          LIS3DHHTR_REG_TEMP_TEMP_EN_ENABLED;

//    cmd(Register::TEMP_CFG_REG, config5);
//    osDelay(100);
}


void LIS3DHH::closeTemp() const
{
    uint8_t config5 = 0x80;
    (void)config5;
//                      LIS3DHHTR_REG_TEMP_TEMP_EN_DISABLED;

//    cmd(Register::TEMP_CFG_REG, config5);
//    osDelay(100);
}


int16_t LIS3DHH::getTemperature(void) const
{
	uint16_t result = 0;
	bool ret = true;
	(void) ret; // prevent comiler warning
    ret = ctrl(Register::OUT_TEMP_L, result); // / 256;
    // result += 25;
    return result;
}



}

}
#endif
