#ifndef MRB_GLFW3_CURSOR_H
#define MRB_GLFW3_CURSOR_H

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>

#include <GLFW/glfw3.h>
#include "mrb_glfw_common.h"

MRB_GLFW_EXTERN const struct mrb_data_type mrb_glfw3_cursor_type;
MRB_GLFW_EXTERN void mrb_glfw3_cursor_init(mrb_state* mrb, struct RClass* mod);
MRB_GLFW_EXTERN mrb_value mrb_glfw3_cursor_value(mrb_state* mrb, GLFWcursor* cursor);

#endif
