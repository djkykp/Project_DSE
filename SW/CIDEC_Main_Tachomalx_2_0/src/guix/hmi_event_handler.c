/* This is a Weather demo event handler sample for GUIX graphics framework. */

/***********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/
#include "gx_api.h"
#include "pwm_thread0.h"
  #define CLOCK_A         0
  #define CLOCK_B         1
#if defined ( __GNUC__ )
#include "weather_GNU_resources.h"
#include "weather_GNU_specifications.h"
#elif defined ( __ICCARM__ )
#include "..\guix_gen\IAR\weather_IAR_resources.h"
#include "..\guix_gen\IAR\weather_IAR_specifications.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#define TIME_EVENT_TIMER     (100)
#define ANIMATION_TIMER      (1)
#define ANIMATION_ALPHA_STEP (8)
#define ANIMATION_ALPHA_MAX  (225)
#define ANIMATION_ALPHA_MIN  (127)

#define CLOUD_OFFSET_START   (-84)
#define CLOUD_OFFSET_END     (120+84)
#define CLOUD_OFFSET_STEP    (2)

#define ANIMATION_DELAY      (3)
#define RAIN_DELAY           (30)
#define SPLASH_TIMER         (100)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/
typedef struct st_day_info
{
    char            * day_name;
    char            * description;
    char            * humidity;
    char            * hi_temp;
    char            * lo_temp;
    GX_RESOURCE_ID  background;
    GX_RESOURCE_ID  icon;
    GX_RESOURCE_ID  animation;
} day_info_t;

/***********************************************************************************************************************
 * Private function prototypes
 ***********************************************************************************************************************/
static VOID UpdateTargetTemp (GX_WINDOW * window);

static UINT show_window(GX_WINDOW * p_new, GX_WIDGET * p_widget, bool detach_old);
/***********************************************************************************************************************
 * Private global variables
 ***********************************************************************************************************************/
static GX_CHAR demo_version[8] = "v1.1.0";

static int      target_temp     = 0;


static GX_CHAR target_temp_string[10];



static day_info_t forecast[3] =
{
    { "SAT", "Sunny",         "72", "84", "73", GX_PIXELMAP_ID_BG_SUNNY,  GX_PIXELMAP_ID_ANIME_SUN_SHINING,
      0                        },
    { "SUN", "Partly Cloudy", "50", "77", "67", GX_PIXELMAP_ID_BG_PARTLYCLOUDY, GX_PIXELMAP_ID_ANIME_SUN_ONCLOUD,
    		GX_PIXELMAP_ID_ANIME_CLOUD     },
    { "MON", "Rain",          "99", "68", "60", GX_PIXELMAP_ID_TACH1,  GX_PIXELMAP_ID_ANIME_RAINING_2,
    		GX_PIXELMAP_ID_ANIME_RAINING_1 }

};

/** Pointer to the Root window */
extern GX_WINDOW_ROOT * p_window_root;

/***********************************************************************************************************************
Functions
***********************************************************************************************************************/
/** Splash Screen Event Handler */
UINT SplashScreenEventHandler (GX_WINDOW * widget, GX_EVENT * event_ptr)
{
    switch (event_ptr->gx_event_type)
    {
        case GX_EVENT_SHOW:
            gx_prompt_text_set(&splash_screen.splash_screen_demo_version, demo_version);

            gx_system_timer_start(widget, TIME_EVENT_TIMER, 100 * 5, 0);
            return gx_window_event_process(widget, event_ptr);
            break;

        case GX_EVENT_TIMER:
        {
            /** create the thermometer screen */
            gx_studio_named_widget_create("main_screen", GX_NULL, GX_NULL);

        	gx_widget_delete(widget);
            if (p_window_root->gx_widget_first_child == GX_NULL)
            {
                gx_widget_attach(p_window_root, &main_screen);
            }
            break;
        }
        default:
            return gx_window_event_process(widget, event_ptr);
    }

    return 0;
}

/** Main Screen Event Handler */
UINT MainScreenEventHandler (GX_WINDOW * widget, GX_EVENT * event_ptr)
{
    switch (event_ptr->gx_event_type)
    {
        case GX_SIGNAL(IDB_TEMP_UP, GX_EVENT_CLICKED):
            if (target_temp < 90)
            {
                target_temp=target_temp+10;


                g_timer0.p_api->dutyCycleSet(g_timer0.p_ctrl, target_temp, TIMER_PWM_UNIT_PERCENT, CLOCK_B);
                UpdateTargetTemp(widget);

            }
            break;

        case GX_SIGNAL(IDB_TEMP_DOWN, GX_EVENT_CLICKED):
            if (target_temp > 0)
            {
                target_temp=target_temp-10;
                g_timer0.p_api->dutyCycleSet(g_timer0.p_ctrl, target_temp, TIMER_PWM_UNIT_PERCENT, CLOCK_B);
                UpdateTargetTemp(widget);
            }
            break;

        case GX_SIGNAL(IDB_FORECAST_SATURDAY, GX_EVENT_CLICKED):

		gx_studio_named_widget_create("window2", GX_NULL, GX_NULL); //create window2 widget
		        show_window((GX_WINDOW*)&window2, (GX_WIDGET*)widget, true);//shows window2
            				//forecast_day = 0;
            //UpdateForecast();
            break;

        case GX_SIGNAL(IDB_FORECAST_SUNDAY, GX_EVENT_CLICKED):

            		//forecast_day = 1;
            //UpdateForecast();
            break;

        case GX_FIRST_SIGNAL:

                        	gx_studio_named_widget_create("window2", GX_NULL, GX_NULL); //create window2 widget
                            show_window((GX_WINDOW*)&window2, (GX_WIDGET*)widget, true);//shows window2

                        break;



        case GX_SIGNAL(IDB_FORECAST_MONDAY, GX_EVENT_CLICKED):
		g_ioport.p_api->pinWrite(IOPORT_PORT_00_PIN_09, true);
			       // g_ioport.p_api->pinWrite(IOPORT_PORT_03_PIN_06, false);
			       // g_ioport.p_api->pinWrite(IOPORT_PORT_03_PIN_07, false);
           // forecast_day = 2;
            //UpdateForecast();
            break;
        default:
            return gx_window_event_process(widget, event_ptr);
    }

    return 0;
}


UINT window2_handler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process(widget, event_ptr);

    switch (event_ptr->gx_event_type){
        case GX_EVENT_PEN_UP:
            show_window((GX_WINDOW*)&main_screen, (GX_WIDGET*)widget, true);
            break;
        default:
            result = gx_window_event_process(widget, event_ptr);
            break;
    }
    return result;
}



static VOID UpdateTargetTemp (GX_WINDOW * window){
    GX_PROMPT   * prompt;

    gx_widget_find(window, ID_TARGET_TEMP, 3, (GX_WIDGET **) &prompt);


    if (prompt)
    {
        gx_utility_ltoa(target_temp, (GX_CHAR *)target_temp_string, 10);
        gx_prompt_text_set(prompt, (GX_CHAR *)target_temp_string);

    }
    gx_widget_find(window, ID_CURRENT_DAY, 3, (GX_WIDGET **) &prompt);

       if (prompt)
           {
               gx_utility_ltoa(target_temp, (GX_CHAR *)target_temp_string, 10);
               gx_prompt_text_set(prompt, (GX_CHAR *)target_temp_string);

           }

}









VOID TempRangeDraw (GX_PROMPT * prompt)
{
    GX_VALUE    width = 0;
    GX_VALUE    space;
    GX_VALUE    xpos;
    int         day = 0;
    GX_FONT     * font;
    GX_PIXELMAP * map;
    GX_VALUE    s1_width;
    GX_VALUE    s2_width;
    GX_VALUE    s3_width;

    switch (prompt->gx_widget_parent->gx_widget_id)
    {
        case IDB_FORECAST_SATURDAY:
            break;

        case IDB_FORECAST_SUNDAY:
            day = 1;
            break;

        case IDB_FORECAST_MONDAY:
            day = 2;
            break;
    }

    gx_widget_font_get(prompt, GX_FONT_ID_MEDIUM, &font);
    gx_system_string_width_get(font, forecast[day].hi_temp, -1, &s1_width);
    width += s1_width;
    gx_system_string_width_get(font, forecast[day].lo_temp, -1, &s2_width);
    width += s2_width;
    gx_system_string_width_get(font, "/", -1, &s3_width);
    width += s3_width;

    gx_widget_pixelmap_get(prompt, GX_PIXELMAP_ID_SYMBOL_DEG, &map);
    width += map->gx_pixelmap_width * 2;

    space  = prompt->gx_widget_size.gx_rectangle_right - prompt->gx_widget_size.gx_rectangle_left + 1;
    space -= width;
    space /= 2;
    xpos   = prompt->gx_widget_size.gx_rectangle_left + space;

    gx_context_font_set(GX_FONT_ID_MEDIUM);
    gx_context_line_color_set(GX_COLOR_ID_TEXT_INPUT_TEXT);

    gx_canvas_text_draw(xpos, prompt->gx_widget_size.gx_rectangle_top, forecast[day].hi_temp, -1);
    xpos += s1_width;

    gx_canvas_pixelmap_draw(xpos, prompt->gx_widget_size.gx_rectangle_top, map);
    xpos += map->gx_pixelmap_width;

    gx_canvas_text_draw(xpos, prompt->gx_widget_size.gx_rectangle_top, "/", -1);
    xpos += s3_width;

    gx_canvas_text_draw(xpos, prompt->gx_widget_size.gx_rectangle_top, forecast[day].lo_temp, -1);
    xpos += s2_width;

    gx_canvas_pixelmap_draw(xpos, prompt->gx_widget_size.gx_rectangle_top, map);
}

static UINT show_window(GX_WINDOW * p_new, GX_WIDGET * p_widget, bool detach_old)
{
    UINT err = GX_SUCCESS;

    if (!p_new->gx_widget_parent)
    {
        err = gx_widget_attach(p_window_root, p_new);
    }
    else
    {
        err = gx_widget_show(p_new);
    }

    gx_system_focus_claim(p_new);

    GX_WIDGET * p_old = p_widget;
    if (p_old && detach_old)
    {
        if (p_old != (GX_WIDGET*)p_new)
        {
            gx_widget_detach(p_old);
        }
    }

    return err;
}
