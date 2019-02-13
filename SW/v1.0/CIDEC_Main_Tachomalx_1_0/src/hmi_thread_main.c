/* HMI Thread entry function */

#include "hmi_thread.h"
#include "gx_api.h"

#if defined ( __GNUC__ )
#include "weather_GNU_resources.h"
#include "weather_GNU_specifications.h"
#elif defined ( __ICCARM__ )
#include "..\guix_gen\IAR\weather_IAR_resources.h"
#include "..\guix_gen\IAR\weather_IAR_specifications.h"
#endif

#if defined(BSP_BOARD_S7G2_SK)||defined(BSP_BOARD_S5D9_PK)
 
#if defined ( __GNUC__ )
#include "lcd.h"
#elif defined ( __ICCARM__ )
#include "..\guix\lcd.h"
#endif
#endif

GX_WINDOW_ROOT * p_window_root;

#if defined(BSP_BOARD_S7G2_SK)||defined(BSP_BOARD_S5D9_PK)
void g_lcd_spi_callback(spi_callback_args_t * p_args);
#endif
void hmi_thread_main(void);
static void hmi_send_touch_message(sf_touch_panel_payload_t * p_payload);

void hmi_thread_main(void)
{
    ssp_err_t err;
    UINT      status = TX_SUCCESS;
    sf_message_header_t * p_message = NULL;

    /* Initializes GUIX. */
    status = gx_system_initialize();
    if(TX_SUCCESS != status)
    {
        while(1)
           {;}
    }

    /* Initializes GUIX drivers. */
    err = g_sf_el_gx0.p_api->open (g_sf_el_gx0.p_ctrl, g_sf_el_gx0.p_cfg);
    if(SSP_SUCCESS != err)
    {
        while(1)
            {;}
    }

    gx_studio_display_configure ( MAIN_DISPLAY,
                                  g_sf_el_gx0.p_api->setup,
                                  LANGUAGE_ENGLISH,
                                  MAIN_DISPLAY_THEME_1,
                                  &p_window_root );

    err = g_sf_el_gx0.p_api->canvasInit(g_sf_el_gx0.p_ctrl, p_window_root);
    if(SSP_SUCCESS != err)
    {
        while(1)
        {;}
    }

    /* Creates the primary screen. */
    status = gx_studio_named_widget_create("splash_screen",
                                           (GX_WIDGET *)p_window_root, GX_NULL);
    if(TX_SUCCESS != status)
    {
        while(1)
        {;}
    }

    /* Shows the root window to make it and patients screen visible. */
    status = gx_widget_show(p_window_root);
    if(TX_SUCCESS != status)
    {
        while(1)
        {;}
    }

    /* Lets GUIX run. */
    status = gx_system_start();
    if(TX_SUCCESS != status)
    {
        while(1)
        {;}
    }

#if defined(BSP_BOARD_S7G2_PE_HMI1)
    /* Controls the GPIO pin for LCD ON. */
    err = g_ioport.p_api->pinWrite(IOPORT_PORT_10_PIN_03, IOPORT_LEVEL_HIGH);
    if (err)
    {
        while(1)
        {;}
    }
#elif defined(BSP_BOARD_S7G2_DK)
    /* Controls the GPIO pin for LCD ON. */
    err = g_ioport.p_api->pinWrite(IOPORT_PORT_07_PIN_10, IOPORT_LEVEL_HIGH);
    if (err)
    {
        while(1)
        {;}
    }
#elif defined(BSP_BOARD_S7G2_SK)||defined(BSP_BOARD_S5D9_PK)
    /** Open the SPI driver to initialize the LCD **/
    err = g_spi_lcdc.p_api->open(g_spi_lcdc.p_ctrl, (spi_cfg_t *)g_spi_lcdc.p_cfg);

    /** Setup the ILI9341V **/
    ILI9341V_Init();
#endif

#if defined(BSP_BOARD_S7G2_PE_HMI1) || defined(BSP_BOARD_S7G2_DK)
    /* Opens PWM driver and controls the TFT panel back light. */
    err = g_pwm_backlight.p_api->open(g_pwm_backlight.p_ctrl, g_pwm_backlight.p_cfg);
    if (err)
    {
        while(1)
        {;}
    }
#endif

    while (1)
    {
        g_sf_message.p_api->pend(g_sf_message.p_ctrl, &hmi_thread_message_queue, (sf_message_header_t **) &p_message, TX_WAIT_FOREVER);
        switch (p_message->event_b.class_code)
        {
        case SF_MESSAGE_EVENT_CLASS_TOUCH:
            if (SF_MESSAGE_EVENT_NEW_DATA == p_message->event_b.code)
            {
                sf_touch_panel_payload_t * p_touch_message = (sf_touch_panel_payload_t *) p_message;

                /** Translate a touch event into a GUIX event */
                hmi_send_touch_message(p_touch_message);
            }
            break;
        default:
            break;
        }

        /** Message is processed, so release buffer. */
        err = g_sf_message.p_api->bufferRelease(g_sf_message.p_ctrl, (sf_message_header_t *) p_message, SF_MESSAGE_RELEASE_OPTION_NONE);
        if (err)
        {
            while(1)
            {;}
        }
    }
}

/*******************************************************************************************************************//**
 * @brief  Sends a touch event to GUIX internal thread to call the GUIX event handler function
 *
 * @param[in] p_payload Touch panel message payload
***********************************************************************************************************************/
static void hmi_send_touch_message(sf_touch_panel_payload_t * p_payload)
{
    bool send_event = true;
    GX_EVENT gxe;

    switch (p_payload->event_type)
    {
    case SF_TOUCH_PANEL_EVENT_DOWN:
        gxe.gx_event_type = GX_EVENT_PEN_DOWN;
        break;
    case SF_TOUCH_PANEL_EVENT_UP:
        gxe.gx_event_type = GX_EVENT_PEN_UP;
        break;
    case SF_TOUCH_PANEL_EVENT_HOLD:
    case SF_TOUCH_PANEL_EVENT_MOVE:
        gxe.gx_event_type = GX_EVENT_PEN_DRAG;
        break;
    case SF_TOUCH_PANEL_EVENT_INVALID:
        send_event = false;
        break;
    default:
        break;
    }

    if (send_event)
    {
        /** Send event to GUI */
        gxe.gx_event_sender         = GX_ID_NONE;
        gxe.gx_event_target         = 0;  /* the event to be routed to the widget that has input focus */
        gxe.gx_event_display_handle = 0;

        gxe.gx_event_payload.gx_event_pointdata.gx_point_x = p_payload->x;
#if defined(BSP_BOARD_S7G2_SK)||defined(BSP_BOARD_S5D9_PK)
        gxe.gx_event_payload.gx_event_pointdata.gx_point_y = (GX_VALUE)(320 - p_payload->y);
#else
        gxe.gx_event_payload.gx_event_pointdata.gx_point_y = p_payload->y;
#endif

        gx_system_event_send(&gxe);
    }
}

#if defined(BSP_BOARD_S7G2_SK)||defined(BSP_BOARD_S5D9_PK)
void g_lcd_spi_callback(spi_callback_args_t * p_args)
{
    if (p_args->event == SPI_EVENT_TRANSFER_COMPLETE)
        tx_semaphore_ceiling_put(&g_hmi_semaphore_lcdc, 1);

}
#endif
