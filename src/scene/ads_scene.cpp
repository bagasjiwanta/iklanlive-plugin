//
// Created by bayus on 26/05/22.
//

#include "plugin-macros.generated.h"
#include "types.h"
#include <util/util.hpp>
#include "util.h"
#include "obs-properties.h"
#include "../exception/AuthException.h"
#include "../exception/LivestreamException.h"

static const char *ads_source_getname(void *unused)
{
	UNUSED_PARAMETER(unused);
	return "Iklanlive Ads";
}

static void ads_source_update(void *data, obs_data_t *settings)
{
	auto *ctx = static_cast<ads *>(data);
	int height = (uint32_t)obs_data_get_int(settings, "height");
	int width = (uint32_t)obs_data_get_int(settings, "width");
	livestream_session l;

	try {
		l = getClosestLivestream();
	} catch (LivestreamException *e) {
	} catch (AuthException *e) {
	}
	ctx->stream_id = l.stream_id;
	ctx->url = get_url_string(l.stream_id);
	update_browser_source(ctx->source, ctx->url, width, height);
}

static void *ads_source_create(obs_data_t *settings, obs_source_t *source)
{
	blog(LOG_INFO, "Creating new source");
	auto *ctx = static_cast<ads *>(bzalloc(sizeof(struct ads)));
	ctx->stream_id = obs_data_get_int(settings, "stream_id");

	livestream_session l;

	int height = (uint32_t)obs_data_get_int(settings, "height");
	int width = (uint32_t)obs_data_get_int(settings, "width");

	try {
		l = getClosestLivestream();
	} catch (LivestreamException *e) {
	} catch (AuthException *e) {
	}

	// blog(LOG_INFO, "stream id : %d", ctx->stream_id);
	ctx->url = get_url_string(l.stream_id);
	ctx->source = create_browser_source(ctx->url, width, height);
	ctx->main_source = source;
	blog(LOG_INFO, "Success creating new source");

	return ctx;
}

static void ads_source_destroy(void *data)
{
	auto *ctx = static_cast<ads *>(data);

	obs_source_release(ctx->source);

	bfree(ctx);
}

static obs_properties_t *ads_source_properties(void *unused)
{
	UNUSED_PARAMETER(unused);
	obs_properties_t *props = obs_properties_create();

	obs_properties_add_int(props, "height", "height", 0, 4000, 1);
	obs_properties_add_int(props, "width", "width", 0, 4000, 1);

	return props;
}

static void ads_source_activate(void *data)
{
	auto *ctx = static_cast<ads *>(data);
	obs_source_add_active_child(ctx->main_source, ctx->source);
}

static void ads_source_deactivate(void *data)
{
	auto *ctx = static_cast<ads *>(data);
	obs_source_remove_active_child(ctx->main_source, ctx->source);
}

static uint32_t ads_source_getwidth(void *data)
{
	auto *ctx = static_cast<ads *>(data);
	return obs_source_get_width(ctx->source);
}

static uint32_t ads_source_getheight(void *data)
{
	auto *ctx = static_cast<ads *>(data);
	return obs_source_get_height(ctx->source);
}

static void ads_source_render(void *data, gs_effect_t *effect)
{
	auto *ctx = static_cast<ads *>(data);
	auto source = obs_source_get_ref(ctx->source);

	if (source) {
		obs_source_video_render(source);
	}

	UNUSED_PARAMETER(effect);
}

static void ads_source_defaults(obs_data_t *settings)
{
	obs_data_set_default_int(settings, "width", 800);
	obs_data_set_default_int(settings, "height", 600);
}

struct obs_source_info ads_info = {
	.id = "iklanlive_ads",
	.type = OBS_SOURCE_TYPE_INPUT,
	.output_flags = OBS_SOURCE_VIDEO | OBS_SOURCE_CUSTOM_DRAW,
	.get_name = ads_source_getname,
	.create = ads_source_create,
	.destroy = ads_source_destroy,
	.get_width = ads_source_getwidth,
	.get_height = ads_source_getheight,
	.get_defaults = ads_source_defaults,
	.get_properties = ads_source_properties,
	.update = ads_source_update,
	.activate = ads_source_activate,
	.deactivate = ads_source_deactivate,
	.video_render = ads_source_render,
	.icon_type = OBS_ICON_TYPE_IMAGE,
};