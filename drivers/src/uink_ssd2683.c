#include "../../drivers/inc/uink_ssd2683.h"

sl_status_t ssd2683_init(void)
{
	sl_status_t status;

	status = ssd_init();
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_init\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_init\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_reset();
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_reset\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_reset\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_send_command(0x00);
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_send_command\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_send_command\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_wait_busy();
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_wait_busy\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_wait_busy\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_send_data(0x2F);
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_send_data\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_send_data\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_send_data(0x29);
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_send_data\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_send_data\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_send_command(0x50);
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_send_command\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_send_command\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_wait_busy();
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_wait_busy\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_wait_busy\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_send_data(0x37);
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_send_data\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_send_data\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_send_command(0xE9);
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_send_command\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_send_command\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_wait_busy();
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_wait_busy\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_wait_busy\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_send_data(0x01);
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_send_data\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_send_data\r\n");
	}
#endif

	return status;
}

sl_status_t ssd2683_power_on(void)
{
	sl_status_t status;

	status = ssd_send_command(0x04);
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_send_command\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_send_command\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_wait_busy();
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_wait_busy\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_wait_busy\r\n");
	}
#endif

	return status;
}

sl_status_t ssd2683_power_off(void)
{
	sl_status_t status;

	status = ssd_send_command(0x02);
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_send_command\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_send_command\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_send_data(0x00);
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_send_data\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_send_data\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_wait_busy();
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_wait_busy\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_wait_busy\r\n");
	}
#endif

	return status;
}

void ssd2683_refresh(void)
{
	//sl_status_t status;

	ssd2683_power_on();


	ssd_send_command(0x12);
	ssd_send_data(0x00);
	ssd_wait_busy();

	ssd2683_power_off();
}

void ssd2683_display_image(const uint8_t *img)
{
	ssd_send_command(0x10);
	ssd_wait_busy();

	ssd_send_datas(img, SSD2683_DISPLAY_BYTE_SIZE);
	ssd2683_refresh();
}

void ssd2683_display_clear(ssd2683_color_t ssd2683_color)
{
	uint16_t i;

	ssd_send_command(0x10);
	ssd_wait_busy();

	for (i = 0; i < SSD2683_DISPLAY_BYTE_SIZE; i++){
		switch (ssd2683_color){
			case SSD2683_BLACK:
				ssd_send_data(0x00);
				break;
			case SSD2683_WHITE:
				ssd_send_data(0x55);
				break;
			case SSD2683_YELLOW:
				ssd_send_data(0xAA);
				break;
			case SSD2683_RED:
				ssd_send_data(0xFF);
				break;
			default:
				break;
		}
	}

	ssd2683_refresh();
}
