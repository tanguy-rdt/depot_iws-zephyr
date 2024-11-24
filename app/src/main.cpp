#ifdef ZEPHYR
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#define LOG_LEVEL LOG_LEVEL_DBG
LOG_MODULE_REGISTER(main);
#endif

#include "log.h"

#include "hal.h"
#include "proxy/proxy.h"
#include "gui.h"

#include "lvgl.h"
#include <unistd.h>

using namespace proxy;
using namespace gui;

int main() {    
   lv_init();

   #ifdef DEBUG
      Log::level(LogLevel::Debug);
   #else
      Log::level(LogLevel::Info);
   #endif

   Hal hal;
   hal.init();

   Proxy proxy(&hal);

   Gui gui(&proxy);
   gui.init();

   while (true) {
      uint32_t ms_delay = lv_timer_handler();
      usleep(ms_delay * 1000);
   }
   
   return 0;
}
