#include <obs-module.h>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("mac-capture-x", "en-US")
MODULE_EXPORT const char *obs_module_description(void)
{
	return "macOS display capture X (Mod by Sndav)";
}


extern bool is_screen_capture_available_x() WEAK_IMPORT_ATTRIBUTE;

bool obs_module_load(void)
{
	if (is_screen_capture_available_x()) {
		extern struct obs_source_info sck_video_capture_info;
		obs_register_source(&sck_video_capture_info);
	}
	return true;
}
