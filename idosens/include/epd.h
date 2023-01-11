#ifndef EPD_H
#define EPD_H

#include "periph/rtc.h"

/**
 * Init EPD
 */
void epd_init(void);

/**
 * Draw default picture on EPD
 */
void epd_draw_default(void);

/**
 * Draw closed picture with reopen time
 */
void epd_draw_closed(struct tm* ot);

#endif
