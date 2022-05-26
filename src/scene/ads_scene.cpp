//
// Created by bayus on 26/05/22.
//

#include "ads_scene.h"
#include "types.h"
#include <util/util.hpp>
#include "util.h"

static const char *ads_source_getname(void* unused) {
  UNUSED_PARAMETER(unused);
  return "Iklanlive Ads";
}

static void ads_source_update(void* data, obs_data_t* settings) {
  auto* ctx = static_cast<ads *>(data);

  ctx->stream_id = obs_data_get_int(settings, "stream_id");
  ctx->url = get_url_string(ctx->stream_id);
  update_browser_source(ctx->source, ctx->url);
}

static void* ads_source_create(obs_data_t *settings, obs_source_t *source){
  UNUSED_PARAMETER(source);

  struct ads *ctx = static_cast<ads *>(bzalloc(sizeof(struct ads)));

  ctx->stream_id = obs_data_get_int(settings, "stream_id");
  ctx->url = get_url_string(ctx->stream_id);
  ctx->source = create_browser_source(ctx->url);

  return ctx;
}

static void ads_source_destroy(void* data) {
  auto* ctx = static_cast<ads *>(data);

  obs_source_release(ctx->source);
  bfree(ctx);
}

static obs_properties_t * ads_source_properties(void* unused) {
  UNUSED_PARAMETER(unused);

  obs_properties_t *props = obs_properties_create();

  auto list = obs_properties_add_list(props, "stream_id",
        "Streaming id",
        OBS_COMBO_TYPE_LIST,
        OBS_COMBO_FORMAT_INT);

  const int _dummy_data[] = {1,2,3,4,5};

  for(auto data: _dummy_data) {
    obs_property_list_add_int(list, "stream_id", data);
  }

  return props;
}

static uint32_t ads_source_getwidth(void *data)
{
  UNUSED_PARAMETER(data);
  return 800;
}

static uint32_t ads_source_getheight(void *data)
{
  UNUSED_PARAMETER(data);
  return 800;
}

static void ads_source_render(void *data, gs_effect_t *effect)
{
  struct ads *ctx = static_cast<ads *>(data);
  obs_source_video_render(ctx->source);

  UNUSED_PARAMETER(effect);
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
    .get_properties = ads_source_properties,
    .update = ads_source_update,
    .video_render = ads_source_render,
    .icon_type = OBS_ICON_TYPE_IMAGE,
};