#ifndef MRB_GLFW3_VID_MODE_H
#define MRB_GLFW3_VID_MODE_H

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>

#include <GLFW/glfw3.h>
#include "mrb_glfw_common.h"

MRB_GLFW_EXTERN const struct mrb_data_type mrb_glfw3_video_mode_type;
MRB_GLFW_EXTERN void mrb_glfw3_vid_mode_init(mrb_state* mrb, struct RClass* mod);
MRB_GLFW_EXTERN mrb_value mrb_glfw3_vid_mode_value(mrb_state* mrb, GLFWvidmode vidmode);

#endif
