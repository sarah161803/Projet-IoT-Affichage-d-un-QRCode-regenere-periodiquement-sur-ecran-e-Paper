/*
 * Copyright (C) 2021-2022 LIG
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     app
 * @{
 *
 * @file
 * @brief       Drawing function for e-Paper Display
 *
 * @author      Germain Lemasson <germain.lemasson@univ-grenoble-alpes.fr>
 *
 * @}
 */
//Include time
#include <time.h>
#include <string.h>
#define DEFAULT_TM {0,0,0,1,0,121,0,0,0}

#include <inttypes.h>

#include <stdbool.h>
#include <stdint.h>

#include "hashes/aes128_cmac.h"
#include "crypto/ciphers.h"


// 1972 and 1976 have 366 days (DELTA_EPOCH_GPS is 315964800 seconds)
// GPS Epoch consists of a count of weeks and seconds of the week since 0 hours (midnight) Sunday 6 January 1980
#define DELTA_EPOCH_GPS ((365*8 + 366*2 + 5)*(24*60*60))

// The end-device responds by sending up to NbTransmissions AppTimeReq messages
// with the AnsRequired bit set to 0.
// The end-device stops re-transmissions of the AppTimeReq if a valid AppTimeAns is received.
// If the NbTransmissions field is 0, the command SHALL be silently discarded.
// The delay between consecutive transmissions of the AppTimeReq is application specific.
// TODO static unsigned int NbTransmissions = 0;


///////Include  Epaper
#include "epd_board.h"

#include "COG_FPL.h"
#include "BufferDraw.h"
#include "Arial24x23.h"
#include "Neu42x35.h"
#include "default_icon.h"
#include "door_closed_icon.h"
#include "liglab_icon.h"
#include "qrcode_campusiot.h"

#include "epd.h"

//AJOUTS DES INCLUDE DE RIOT
#include "qrcodegen.h"
#include "disp_dev.h"

//Definition size e paper screen
#define IMAGE_W (264)
#define IMAGE_H (176)
#define IMAGE_LEN (IMAGE_W*IMAGE_H/8)

//Two image buffer for EPD
static uint8_t image[IMAGE_LEN];
static uint8_t old_image[IMAGE_LEN];

//simple memcopy function
static void memcopy(const uint8_t * buffsource, uint8_t * buffdest, uint16_t len)
{
    for(uint16_t i =0; i<len; i++)
    {
        buffdest[i]=buffsource[i];
    }
}

//Give number epoch
unsigned int getTimeSinceEpoch(void) {
	struct tm current_time = DEFAULT_TM;
	// Read the RTC current time
#if MODULE_PERIPH_RTC == 1
	rtc_get_time(&current_time);
#endif
	//print_time("[clock] Current time: ", &current_time);
	time_t timeSinceEpoch = mktime(&current_time);
	// substract number of seconds between 6/1/1980 and 1/1/1970
	timeSinceEpoch -= DELTA_EPOCH_GPS;
	return timeSinceEpoch;
}

/**
 * Init EPD
 */
void epd_init(void)
{
    //Init buffer image
    BD_init( image, IMAGE_LEN, IMAGE_W, IMAGE_H, 0, 1);
    BD_clear();
    //BD_set_font(Courier_New19x36, Courier_New19x36_conf);
    BD_set_font(Arial24x23, NULL);
    //Init EPD
    spi_init(EPD_PARAM_SPI);
    EPD_display_hardware_init();
}

/**
 * Draw default picture on EPD
 */
 
 
void epd_draw_default(void)
{
	puts("Default");
	EPD_power_on(EPD_270, 18);
	puts("drive on");
	EPD_initialize_driver ();
	puts("drive init");

	//URL SANS CRYPTO
	char URL_TO_ENCODE[50];
	sprintf(URL_TO_ENCODE, "https://presence.com/%x", getTimeSinceEpoch());
	printf("%s", URL_TO_ENCODE);



	//URL AVEC CRYPTO
	char URL_TO_ENCODE_KEY[50];
	
	// AES128_CMAC_KEY and AES128_CMAC_KEY_VERSION can be set using downlink
	uint16_t AES128_CMAC_KEY_VERSION=1;
	const uint8_t AES128_CMAC_KEY[16] = {
	    0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
	    0x99, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66
	};

	// get the secure digest
	char A_ENCODER[50];
	sprintf(A_ENCODER, "%x/%x", getTimeSinceEpoch(), AES128_CMAC_KEY_VERSION);
	uint8_t digest[16];
	aes128_cmac_context_t ctx;
	aes128_cmac_init(&ctx, AES128_CMAC_KEY, 16);
	aes128_cmac_update(&ctx, A_ENCODER, 50);
	aes128_cmac_final(&ctx, digest);


	sprintf(URL_TO_ENCODE_KEY, "https://presence.com/%x/%x/%s", getTimeSinceEpoch(), AES128_CMAC_KEY_VERSION, digest);

	
	int ENCODER_VERSION = (sizeof(URL_TO_ENCODE) >> 3);
	
	
	uint8_t qr0[qrcodegen_BUFFER_LEN_FOR_VERSION(ENCODER_VERSION)];
	uint8_t buffer[qrcodegen_BUFFER_LEN_FOR_VERSION(ENCODER_VERSION)];

	
	//Generation of qr code
    	qrcodegen_encodeText(URL_TO_ENCODE,
                              buffer, qr0, qrcodegen_Ecc_MEDIUM,
                              qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX,
                              qrcodegen_Mask_AUTO, true);
    	
    	//Get size of qr code
	int size = qrcodegen_getSize(qr0);
	int square_size = IMAGE_H / size;		//Size min screen
	
	//Start after 0 to center the qr code
	int x0 = (IMAGE_W - size*square_size) / 2;
	int y0 = (IMAGE_H - size*square_size) / 2;
	
	
	//Drawing the image
	for (int j = 0; j < size; j++){
		x0 = (IMAGE_W - size*square_size) / 2;
	    	for (int i = 0; i < size; i++){
	    		if (qrcodegen_getModule(qr0, i, j)){
	    			BD_fillrect(x0, y0, x0+square_size, y0+square_size, 0); //Add square for each black pixel of qr code
	    		}
	    		
	    		x0 += square_size;
	    	}
		y0 += square_size;
	}
	    
	//e paper procedure to show the picture created
	EPD_display_from_array_prt ( old_image, image );
	puts("disp");
	memcopy(default_icon,old_image,IMAGE_LEN);
	EPD_power_off();
	spi_release(EPD_PARAM_SPI);
	puts("drive off");

}
/**
 * Draw closed picture with reopen time
 */
void epd_draw_closed(struct tm* ot)
{
    char buffer[32];

    //build image to draw
    BD_clear();
    BD_clip_image(door_closed,0,0,264,100);
    BD_locate(40,100);
    sprintf(buffer,"%02i-%02i-%04i",
             ot->tm_mday, ot->tm_mon + 1, ot->tm_year + 1900
           );
    puts(buffer);
    BD_puts(buffer);
    BD_locate(90,136);
    sprintf(buffer,"%02i:%02i",
            ot->tm_hour, ot->tm_min
          );
    BD_puts(buffer);
    
    //Draw image on EPD
    EPD_power_on(EPD_270, 18);
    EPD_initialize_driver ();
    EPD_display_from_array_prt ( old_image, image );
    memcopy(image,old_image,IMAGE_LEN);
    EPD_power_off();
    //EDP power use spi_aquire but you must use spi_release manualy
    spi_release(EPD_PARAM_SPI);
}
