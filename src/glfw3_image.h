#ifndef MRB_GLFW3_IMAGE_H
#define MRB_GLFW3_IMAGE_H

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include "mrb_glfw_common.h"

MRB_GLFW_EXTERN const struct mrb_data_type mrb_glfw3_image_type;
MRB_GLFW_EXTERN void mrb_glfw3_image_init(mrb_state* mrb, struct RClass* mod);

#endif
