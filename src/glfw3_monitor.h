#ifndef MRB_GLFW3_MONITOR_H
#define MRB_GLFW3_MONITOR_H

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>

#include <GLFW/glfw3.h>
#include "mrb_glfw_common.h"

MRB_GLFW_EXTERN const struct mrb_data_type mrb_glfw3_monitor_type;
MRB_GLFW_EXTERN void mrb_glfw3_monitor_init(mrb_state* mrb, struct RClass* mod);
MRB_GLFW_EXTERN mrb_value mrb_glfw3_monitor_value(mrb_state* mrb, GLFWmonitor* mon);

static inline GLFWmonitor*
mrb_glfw3_get_monitor(mrb_state* mrb, mrb_value self)
{
  return (GLFWmonitor*)mrb_data_get_ptr(mrb, self, &mrb_glfw3_monitor_type);
}

#endif
