#include <device.h>
#include <drivers/led_strip.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(underglow_init, LOG_LEVEL_INF);

#define STRIP_NODE DT_NODELABEL(led_strip)

static const struct led_rgb colors[5] = {
    { .r = 0x00, .g = 0xFF, .b = 0x00 }, // GREEN
    { .r = 0xFF, .g = 0x00, .b = 0x00 }, // RED
    { .r = 0xFF, .g = 0xFF, .b = 0x00 }, // YELLOW
    { .r = 0x00, .g = 0x00, .b = 0xFF }, // BLUE
    { .r = 0xFF, .g = 0x80, .b = 0x00 }, // ORANGE
};

static int set_static_colors(void)
{
    const struct device *strip = DEVICE_DT_GET(STRIP_NODE);
    if (!device_is_ready(strip)) {
        LOG_ERR("LED strip not ready");
        return -ENODEV;
    }

    int ret = led_strip_update_rgb(strip, colors, ARRAY_SIZE(colors));
    if (ret) {
        LOG_ERR("Failed to set LED colors (err %d)", ret);
    }

    return ret;
}

SYS_INIT(set_static_colors, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);