/* This is a Weather demo event handler sample for GUIX graphics framework. */

/***********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/
#include "gx_api.h"

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

static VOID UpdateForecast (void);

static VOID ForecastAnimationReset (GX_WINDOW * win);

/***********************************************************************************************************************
 * Private global variables
 ***********************************************************************************************************************/
static GX_CHAR demo_version[8] = "v1.1.0";

static int      target_temp     = 76;
static int      forecast_day    = 0;
static int      animation_step  = ANIMATION_ALPHA_STEP;
static GX_UBYTE animation_alpha = ANIMATION_ALPHA_MIN;
static int      cloud_offset    = CLOUD_OFFSET_START;
static int      cloud_step      = CLOUD_OFFSET_STEP;
static int      rain_step       = 0;

static GX_CHAR target_temp_string[10];
static char humidity_string[40];

static day_info_t forecast[3] =
{
    { "SAT", "Sunny",         "72", "84", "73", GX_PIXELMAP_ID_BG_SUNNY,  GX_PIXELMAP_ID_ANIME_SUN_SHINING,
      0                        },
    { "SUN", "Partly Cloudy", "50", "77", "67", GX_PIXELMAP_ID_BG_PARTLYCLOUDY, GX_PIXELMAP_ID_ANIME_SUN_ONCLOUD,
    		GX_PIXELMAP_ID_ANIME_CLOUD     },
    { "MON", "Rain",          "99", "68", "60", GX_PIXELMAP_ID_BG_RAINY,  GX_PIXELMAP_ID_ANIME_RAINING_2,
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
            if (target_temp < 85)
            {
                target_temp++;
                UpdateTargetTemp(widget);
            }
            break;

        case GX_SIGNAL(IDB_TEMP_DOWN, GX_EVENT_CLICKED):
            if (target_temp > 60)
            {
                target_temp--;
                UpdateTargetTemp(widget);
            }
            break;

        case GX_SIGNAL(IDB_FORECAST_SATURDAY, GX_EVENT_CLICKED):
            forecast_day = 0;
            UpdateForecast();
            break;

        case GX_SIGNAL(IDB_FORECAST_SUNDAY, GX_EVENT_CLICKED):
            forecast_day = 1;
            UpdateForecast();
            break;

        case GX_SIGNAL(IDB_FORECAST_MONDAY, GX_EVENT_CLICKED):
            forecast_day = 2;
            UpdateForecast();
            break;
        default:
            return gx_window_event_process(widget, event_ptr);
    }

    return 0;
}

static VOID UpdateTargetTemp (GX_WINDOW * window)
{
    GX_PROMPT   * prompt;
    gx_widget_find(window, ID_TARGET_TEMP, 3, (GX_WIDGET **) &prompt);

    if (prompt)
    {
        gx_utility_ltoa(target_temp, (GX_CHAR *)target_temp_string, 10);
        gx_prompt_text_set(prompt, (GX_CHAR *)target_temp_string);
    }
}

VOID ForecastAnimationDraw (GX_WINDOW * win)
{
    GX_PIXELMAP * map;
    GX_VALUE    xpos;
    GX_VALUE    ypos;
    GX_VALUE    width;
    GX_VALUE    height;

    /** draw the background image: */
    gx_widget_pixelmap_get(win, forecast[forecast_day].icon, &map);
    width  = (GX_VALUE)(win->gx_widget_size.gx_rectangle_right - win->gx_widget_size.gx_rectangle_left + 1);
    xpos   = (GX_VALUE)(win->gx_widget_size.gx_rectangle_left + ((width - map->gx_pixelmap_width) / 2));

    height = (GX_VALUE)(win->gx_widget_size.gx_rectangle_bottom - win->gx_widget_size.gx_rectangle_top + 1);
    ypos   = (GX_VALUE)(win->gx_widget_size.gx_rectangle_top + ((height - map->gx_pixelmap_height) / 2));

    switch (forecast[forecast_day].animation)
    {
        case 0:

            /** The sunny day graphic, just blend the background */
            gx_canvas_pixelmap_blend(xpos, ypos, map, animation_alpha);
            if (animation_step > 0)
            {
                if (animation_alpha <= ANIMATION_ALPHA_MAX - animation_step)
                {
                    animation_alpha += animation_step;
                }
                else
                {
                    animation_step = -animation_step;
                }
            }
            else
            {
                if (animation_alpha > ANIMATION_ALPHA_MIN)
                {
                    animation_alpha += animation_step;
                }
                else
                {
                    animation_step = -animation_step;
                }
            }

            break;

        case GX_PIXELMAP_ID_ANIME_CLOUD:
            gx_canvas_pixelmap_draw(xpos, ypos, map);

            gx_widget_pixelmap_get(win, forecast[forecast_day].animation, &map);
            xpos = win->gx_widget_size.gx_rectangle_left +  ((width - map->gx_pixelmap_width) / 2);
            ypos = win->gx_widget_size.gx_rectangle_bottom - map->gx_pixelmap_height;
            gx_canvas_pixelmap_draw((xpos + cloud_offset), ypos, map);

            cloud_offset += CLOUD_OFFSET_STEP;
            if (cloud_offset >= CLOUD_OFFSET_END)
            {
                gx_system_timer_stop(win, ANIMATION_TIMER);
            }

            break;

        case GX_PIXELMAP_ID_ANIME_RAINING_1:
        case GX_PIXELMAP_ID_ANIME_RAINING_2:
            if (rain_step)
            {
                gx_widget_pixelmap_get(win, forecast[forecast_day].animation, &map);
                xpos     += 6;

                rain_step = 0;
            }
            else
            {
                rain_step = 1;
            }

            gx_canvas_pixelmap_draw((GX_UBYTE)xpos, (GX_UBYTE)ypos, map);
            break;
    }
}

static void UpdateForecast ()
{
    int         day = forecast_day;

    gx_window_wallpaper_set(&main_screen, forecast[day].background, GX_FALSE);
    gx_prompt_text_set(&main_screen.main_screen_forecast_day, forecast[day].day_name);
    gx_prompt_text_set(&main_screen.main_screen_forecast_temp, forecast[day].hi_temp);
    gx_prompt_text_set(&main_screen.main_screen_forecast_summary, forecast[day].description);

    GX_STRCPY(humidity_string, forecast[day].humidity);
    GX_STRCAT(humidity_string, "% Humidity");
    gx_prompt_text_set(&main_screen.main_screen_humidity, humidity_string);
    ForecastAnimationReset(&main_screen.main_screen_animation_window);
}

static VOID ForecastAnimationReset (GX_WINDOW * win)
{
    if (forecast[forecast_day].animation == GX_PIXELMAP_ID_ANIME_RAINING_1)
    {
        gx_system_timer_start(win, ANIMATION_TIMER, RAIN_DELAY, RAIN_DELAY);
    }
    else
    {
        gx_system_timer_start(win, ANIMATION_TIMER, ANIMATION_DELAY, ANIMATION_DELAY);
    }

    animation_step  = ANIMATION_ALPHA_STEP;
    animation_alpha = ANIMATION_ALPHA_MIN;

    cloud_offset    = CLOUD_OFFSET_START;
    cloud_step      = CLOUD_OFFSET_STEP;

    rain_step       = 0;
}

UINT ForecastAnimationEvent (GX_WINDOW * win, GX_EVENT * event_ptr)
{
    switch (event_ptr->gx_event_type)
    {
        case GX_EVENT_TIMER:
            gx_system_dirty_mark(win);
            break;

        default:
            return gx_window_event_process(win, event_ptr);
    }

    return 0;
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
