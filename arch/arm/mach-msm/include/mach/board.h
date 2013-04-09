/* arch/arm/mach-msm/include/mach/board.h
 *
 * Copyright (C) 2007 Google, Inc.
 * Copyright (c) 2008-2010, Code Aurora Forum. All rights reserved.
 * Author: Brian Swetland <swetland@google.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __ASM_ARCH_MSM_BOARD_H
#define __ASM_ARCH_MSM_BOARD_H

#include <linux/types.h>
#include <linux/input.h>
#include <linux/usb.h>
#include <linux/leds-pmic8058.h>
#include <mach/msm_bus.h>

/* platform device data structures */
struct msm_acpu_clock_platform_data {
	uint32_t acpu_switch_time_us;
	uint32_t max_speed_delta_khz;
	uint32_t vdd_switch_time_us;
	unsigned int max_axi_khz;
	unsigned int max_vdd;
	int (*acpu_set_vdd) (int mvolts);
};

struct msm_camera_io_ext {
	uint32_t mdcphy;
	uint32_t mdcsz;
	uint32_t appphy;
	uint32_t appsz;
	uint32_t camifpadphy;
	uint32_t camifpadsz;
	uint32_t csiphy;
	uint32_t csisz;
	uint32_t csiirq;
};

struct msm_camera_io_clk {
	uint32_t mclk_clk_rate;
	uint32_t vfe_clk_rate;
};

struct msm_camera_device_platform_data {
	void (*camera_gpio_on) (void);
	void (*camera_gpio_off)(void);
	struct msm_camera_io_ext ioext;
	struct msm_camera_io_clk ioclk;
};
enum msm_camera_csi_data_format {
	CSI_8BIT,
	CSI_10BIT,
	CSI_12BIT,
};
struct msm_camera_csi_params {
	enum msm_camera_csi_data_format data_format;
	uint8_t lane_cnt;
	uint8_t lane_assign;
	uint8_t settle_cnt;
	uint8_t dpcm_scheme;
};

#ifdef CONFIG_SENSORS_MT9T013
struct msm_camera_legacy_device_platform_data {
	int sensor_reset;
	int sensor_pwd;
	int vcm_pwd;
	void (*config_gpio_on) (void);
	void (*config_gpio_off)(void);
};
#endif

#define MSM_CAMERA_FLASH_NONE 0
#define MSM_CAMERA_FLASH_LED  1

#define MSM_CAMERA_FLASH_SRC_PMIC (0x00000001<<0)
#define MSM_CAMERA_FLASH_SRC_PWM  (0x00000001<<1)
//Div6D1-CL-Camera-SensorInfo-00+{
#define MSM_CAMERA_SENSOR_ORIENTATION_0 0
#define MSM_CAMERA_SENSOR_ORIENTATION_90 1
#define MSM_CAMERA_SENSOR_ORIENTATION_180 2
#define MSM_CAMERA_SENSOR_ORIENTATION_270 3
//Div6D1-CL-Camera-SensorInfo-00+}
struct msm_camera_sensor_flash_pmic {
	uint8_t num_of_src;
	uint32_t low_current;
	uint32_t high_current;
	enum pmic8058_leds led_src_1;
	enum pmic8058_leds led_src_2;
	int (*pmic_set_current)(enum pmic8058_leds id, unsigned mA);
};

struct msm_camera_sensor_flash_pwm {
	uint32_t freq;
	uint32_t max_load;
	uint32_t low_load;
	uint32_t high_load;
	uint32_t channel;
};

struct msm_camera_sensor_flash_src {
	int flash_sr_type;

	union {
		struct msm_camera_sensor_flash_pmic pmic_src;
		struct msm_camera_sensor_flash_pwm pwm_src;
	} _fsrc;
};

struct msm_camera_sensor_flash_data {
	int flash_type;
	struct msm_camera_sensor_flash_src *flash_src;
};
//Div6D1-CL-Camera-SensorInfo-01+{
#define MAX_SENSOR_PARAMETERS 256

struct msm_parameters_data {
    //Div6D1-CL-Camera-SensorInfo-02*{
    uint32_t autoexposure;
    uint32_t effects;
    uint32_t wb;
    uint32_t antibanding;
    uint32_t flash;
    uint32_t focus;
    uint32_t ISO;
    uint32_t lensshade;
    uint32_t scenemode;
    uint32_t continuous_af;
    uint32_t touchafaec;
    uint32_t frame_rate_modes;
    //Div6D1-CL-Camera-SensorInfo-02*}
    int8_t  max_brightness;
    int8_t  max_contrast;
    int8_t  max_saturation;
    int8_t  max_sharpness;
    int8_t  min_brightness;
    int8_t  min_contrast;
    int8_t  min_saturation;
    int8_t  min_sharpness;

};
//Div6D1-CL-Camera-SensorInfo-01+}
struct msm_camera_sensor_strobe_flash_data {
	int flash_charge; /* pin for charge */
	uint32_t flash_recharge_duration;
	uint32_t irq;
	spinlock_t spin_lock;
	spinlock_t timer_lock;
};

struct msm_camera_sensor_info {
        const char *sensor_name;
        int sensor_reset;
        int sensor_pwd;
        int sensor_Orientation;//Div6D1-CL-Camera-SensorInfo-00+
        int vcm_pwd;
        int vcm_enable;
        int mclk;
        int flash_type;

        /* Declare for camea pins */
        int MCLK_PIN;
        int mclk_sw_pin;
        int pwdn_pin;
        int rst_pin;
        int standby_pin;
        int vga_pwdn_pin;
        int vga_rst_pin;
        int vga_power_en_pin;
        int GPIO_FLASHLED;
        int GPIO_FLASHLED_DRV_EN;

        /* Declare for camera power */
        int AF_pmic_en_pin;
        int cam_v2p8_en_pin;
        const char *cam_vreg_vddio_id;
        const char *cam_vreg_acore_id;
        
        //SW5-Multimedia-TH-FlashModeSetting-01+{
        /* Flash LED setting */
        int flash_target_addr;
        int flash_target;
        int flash_bright;
        int flash_main_waittime;
        int flash_main_starttime;
        int flash_second_waittime;
        int preflash_light;//Div2-SW6-MM-CL-FB3LED-00+
        //SW5-Multimedia-TH-FlashModeSetting-01+}
        
        //SW5-Multimedia-TH-MT9P111ReAFTest-00+{
        int fast_af_retest_target;
        //SW5-Multimedia-TH-MT9P111ReAFTest-00+}
        int torch_light;//Div2-SW6-MM-CL-FB3LED-00+
        struct msm_camera_device_platform_data *pdata;
        struct resource *resource;
        uint8_t num_resources;
        struct msm_camera_sensor_flash_data *flash_data;
        int csi_if;
        struct msm_camera_csi_params csi_params;
        struct msm_camera_sensor_strobe_flash_data *strobe_flash_data;
        struct msm_parameters_data *parameters_data;//Div6D1-CL-Camera-SensorInfo-01+
};

struct clk;

struct snd_endpoint {
	int id;
	const char *name;
};

struct msm_snd_endpoints {
	struct snd_endpoint *endpoints;
	unsigned num;
};

#define MSM_MAX_DEC_CNT 14
/* 7k target ADSP information */
/* Bit 23:0, for codec identification like mp3, wav etc *
 * Bit 27:24, for mode identification like tunnel, non tunnel*
 * bit 31:28, for operation support like DM, DMA */
enum msm_adspdec_concurrency {
	MSM_ADSP_CODEC_WAV = 0,
	MSM_ADSP_CODEC_ADPCM = 1,
	MSM_ADSP_CODEC_MP3 = 2,
	MSM_ADSP_CODEC_REALAUDIO = 3,
	MSM_ADSP_CODEC_WMA = 4,
	MSM_ADSP_CODEC_AAC = 5,
	MSM_ADSP_CODEC_RESERVED = 6,
	MSM_ADSP_CODEC_MIDI = 7,
	MSM_ADSP_CODEC_YADPCM = 8,
	MSM_ADSP_CODEC_QCELP = 9,
	MSM_ADSP_CODEC_AMRNB = 10,
	MSM_ADSP_CODEC_AMRWB = 11,
	MSM_ADSP_CODEC_EVRC = 12,
	MSM_ADSP_CODEC_WMAPRO = 13,
	MSM_ADSP_MODE_TUNNEL = 24,
	MSM_ADSP_MODE_NONTUNNEL = 25,
	MSM_ADSP_MODE_LP = 26,
	MSM_ADSP_OP_DMA = 28,
	MSM_ADSP_OP_DM = 29,
};

struct msm_adspdec_info {
	const char *module_name;
	unsigned module_queueid;
	int module_decid; /* objid */
	unsigned nr_codec_support;
};

/* Carries information about number codec
 * supported if same codec or different codecs
 */
struct dec_instance_table {
	uint8_t max_instances_same_dec;
	uint8_t max_instances_diff_dec;
};

struct msm_adspdec_database {
	unsigned num_dec;
	unsigned num_concurrency_support;
	unsigned int *dec_concurrency_table; /* Bit masked entry to *
					      *	represents codec, mode etc */
	struct msm_adspdec_info  *dec_info_list;
	struct dec_instance_table *dec_instance_list;
};

struct msm_panel_common_pdata {
	uintptr_t hw_revision_addr;
	int gpio;
	int (*backlight_level)(int level, int max, int min);
	int (*pmic_backlight)(int level);
	int (*panel_num)(void);
	void (*panel_config_gpio)(int);
	int *gpio_num;
	int mdp_core_clk_rate;
};

struct lcdc_platform_data {
	int (*lcdc_gpio_config)(int on);
	int (*lcdc_power_save)(int);
};

struct tvenc_platform_data {
	int (*pm_vid_en)(int on);
};

struct mddi_platform_data {
	int (*mddi_power_save)(int on);
	int (*mddi_sel_clk)(u32 *clk_rate);
	int (*mddi_client_power)(u32 client_id);
};

struct mipi_dsi_platform_data {
	int (*dsi_power_save)(int on);
};

struct msm_fb_platform_data {
	int (*detect_client)(const char *name);
	int mddi_prescan;
	int (*allow_set_offset)(void);
};

struct msm_hdmi_platform_data {
	int irq;
	int (*cable_detect)(int insert);
/* FIHTDC, Div2-SW2-BSP SungSCLee, HDMI { */	
	int (*intr_detect)(void);
	void (*setup_int_power)(int);	
/* } FIHTDC, Div2-SW2-BSP SungSCLee, HDMI */	
};

struct msm_i2c_platform_data {
	int clk_freq;
	uint32_t rmutex;
	const char *rsl_id;
	uint32_t pm_lat;
	int pri_clk;
	int pri_dat;
	int aux_clk;
	int aux_dat;
	const char *clk;
	const char *pclk;
	int src_clk_rate;
	void (*msm_i2c_config_gpio)(int iface, int config_type);
};

enum msm_ssbi_controller_type {
	MSM_SBI_CTRL_SSBI = 0,
	MSM_SBI_CTRL_SSBI2,
	MSM_SBI_CTRL_PMIC_ARBITER,
};

struct msm_ssbi_platform_data {
	const char *rsl_id;
	enum msm_ssbi_controller_type controller_type;
};

/* common init routines for use by arch/arm/mach-msm/board-*.c */

void __init msm_add_devices(void);
void __init msm_map_common_io(void);
void __init msm_map_qsd8x50_io(void);
void __init msm_map_msm8x60_io(void);
void __init msm_map_msm7x30_io(void);
void __init msm_map_comet_io(void);
void __init msm_init_irq(void);
void __init msm_clock_init(struct clk *clock_tbl, unsigned num_clocks);
void __init msm_acpu_clock_init(struct msm_acpu_clock_platform_data *);

struct mmc_platform_data;
int __init msm_add_sdcc(unsigned int controller,
		struct mmc_platform_data *plat);

struct msm_usb_host_platform_data;
int __init msm_add_host(unsigned int host,
		struct msm_usb_host_platform_data *plat);
#if defined(CONFIG_USB_FUNCTION_MSM_HSUSB) \
	|| defined(CONFIG_USB_MSM_72K) || defined(CONFIG_USB_MSM_72K_MODULE)
void msm_hsusb_set_vbus_state(int online);
#else
static inline void msm_hsusb_set_vbus_state(int online) {}
#endif

void __init msm_snddev_init(void);
void __init msm_snddev_init_timpani(void);
void msm_snddev_poweramp_on(void);
void msm_snddev_poweramp_off(void);
void msm_snddev_hsed_voltage_on(void);
void msm_snddev_hsed_voltage_off(void);
void msm_snddev_tx_route_config(void);
void msm_snddev_tx_route_deconfig(void);
void msm_snddev_rx_route_config(void);
void msm_snddev_rx_route_deconfig(void);
void msm_snddev_enable_amic_power(void);
void msm_snddev_disable_amic_power(void);
void msm_snddev_enable_dmic_power(void);
void msm_snddev_disable_dmic_power(void);

extern unsigned int msm_shared_ram_phys; /* defined in arch/arm/mach-msm/io.c */


#endif
