//
// Created by bayus on 26/05/22.
//

#include "ads_scene.h"
#include "types.h"
#include <util/util.hpp>
#include "util.h"

static const char *ads_source_getname(void* unused) {
  UNUSED_PARAMETER(unused);
  return obs_module_text("IklanliveAds");
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

struct obs_source_info slideshow_info = {
    .id = "iklanlive_ads",
    .type = OBS_SOURCE_TYPE_INPUT,
    .output_flags = OBS_SOURCE_VIDEO,
    .get_name = ads_source_getname,
    .create = ads_source_create,
    .update = ads_source_update,
};