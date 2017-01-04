#include <stdbool.h>
#include <string.h>

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/array.h>
#include <mruby/numeric.h>

#include "glfw3_gamma_ramp.h"

static struct RClass* mrb_glfw3_gamma_ramp_class;

static void
mrb_glfw3_gamma_ramp_free(mrb_state* mrb, void* vptr)
{
  GLFWgammaramp* ptr = (GLFWgammaramp*)vptr;

  if (ptr) {
    if (ptr->red) {
      mrb_free(mrb, ptr->red);
      ptr->red = NULL;
    }

    if (ptr->green) {
      mrb_free(mrb, ptr->green);
      ptr->green = NULL;
    }

    if (ptr->blue) {
      mrb_free(mrb, ptr->blue);
      ptr->blue = NULL;
    }

    mrb_free(mrb, ptr);
  }
}

MRB_GLFW_EXTERN const struct mrb_data_type mrb_glfw3_gamma_ramp_type = { "GLFWgammaramp", mrb_glfw3_gamma_ramp_free };

static inline GLFWgammaramp*
get_gamma_ramp(mrb_state* mrb, mrb_value self)
{
  return (GLFWgammaramp*)mrb_data_get_ptr(mrb, self, &mrb_glfw3_gamma_ramp_type);
}

typedef short unsigned int glfw_gamma_int;

MRB_GLFW_EXTERN mrb_value
mrb_glfw3_gamma_ramp_value(mrb_state* mrb, const GLFWgammaramp* gramp)
{
  GLFWgammaramp* gammaramp;
  mrb_value result;
  result = mrb_obj_new(mrb, mrb_glfw3_gamma_ramp_class, 0, NULL);
  gammaramp = (GLFWgammaramp*)mrb_malloc(mrb, sizeof(GLFWgammaramp));
  gammaramp->size = gramp->size;
  gammaramp->red = (glfw_gamma_int*)mrb_malloc(mrb, sizeof(glfw_gamma_int) * gammaramp->size);
  gammaramp->green = (glfw_gamma_int*)mrb_malloc(mrb, sizeof(glfw_gamma_int) * gammaramp->size);
  gammaramp->blue = (glfw_gamma_int*)mrb_malloc(mrb, sizeof(glfw_gamma_int) * gammaramp->size);
  memcpy(gammaramp->red, gramp->red, sizeof(glfw_gamma_int) * gammaramp->size);
  memcpy(gammaramp->green, gramp->green, sizeof(glfw_gamma_int) * gammaramp->size);
  memcpy(gammaramp->blue, gramp->blue, sizeof(glfw_gamma_int) * gammaramp->size);
  mrb_data_init(result, gammaramp, &mrb_glfw3_gamma_ramp_type);
  return result;
}

static mrb_value
gamma_ramp_initialize(mrb_state* mrb, mrb_value self)
{
  GLFWgammaramp* gammaramp;
  mrb_int size = 0;
  mrb_get_args(mrb, "|i", &size);

  if (size != 0) {
    gammaramp = (GLFWgammaramp*)mrb_malloc(mrb, sizeof(GLFWgammaramp));
    gammaramp->size = size;
    gammaramp->red = (glfw_gamma_int*)mrb_malloc(mrb, sizeof(glfw_gamma_int) * gammaramp->size);
    gammaramp->green = (glfw_gamma_int*)mrb_malloc(mrb, sizeof(glfw_gamma_int) * gammaramp->size);
    gammaramp->blue = (glfw_gamma_int*)mrb_malloc(mrb, sizeof(glfw_gamma_int) * gammaramp->size);
    memset(gammaramp->red, 0, sizeof(glfw_gamma_int) * gammaramp->size);
    memset(gammaramp->green, 0, sizeof(glfw_gamma_int) * gammaramp->size);
    memset(gammaramp->blue, 0, sizeof(glfw_gamma_int) * gammaramp->size);
    mrb_data_init(self, gammaramp, &mrb_glfw3_gamma_ramp_type);
  }

  return self;
}

static mrb_value
gamma_ramp_get_row(mrb_state* mrb, mrb_value self)
{
  GLFWgammaramp* gammaramp;
  mrb_value vals[3];
  mrb_int row;
  mrb_get_args(mrb, "i", &row);
  gammaramp = get_gamma_ramp(mrb, self);

  if (row < 0 || row > (int)gammaramp->size) {
    mrb_raise(mrb, E_INDEX_ERROR, "row is out of range!");
    return mrb_nil_value();
  }

  vals[0] = mrb_fixnum_value(gammaramp->red[row]);
  vals[1] = mrb_fixnum_value(gammaramp->green[row]);
  vals[2] = mrb_fixnum_value(gammaramp->blue[row]);
  return mrb_ary_new_from_values(mrb, 3, vals);
}

static mrb_value
gamma_ramp_set_row(mrb_state* mrb, mrb_value self)
{
  GLFWgammaramp* gammaramp;
  mrb_int row;
  mrb_int r;
  mrb_int g;
  mrb_int b;
  mrb_get_args(mrb, "iiii", &row, &r, &g, &b);
  gammaramp = get_gamma_ramp(mrb, self);

  if (row < 0 || row > (int)gammaramp->size) {
    mrb_raise(mrb, E_INDEX_ERROR, "row is out of range!");
    return mrb_nil_value();
  }

  gammaramp->red[row] = (short)r;
  gammaramp->green[row] = (short)g;
  gammaramp->blue[row] = (short)b;
  return mrb_nil_value();
}

MRB_GLFW_EXTERN void
mrb_glfw3_gamma_ramp_init(mrb_state* mrb, struct RClass* mod)
{
  mrb_glfw3_gamma_ramp_class = mrb_define_class_under(mrb, mod, "GammaRamp", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_glfw3_gamma_ramp_class, MRB_TT_DATA);
  mrb_define_method(mrb, mrb_glfw3_gamma_ramp_class, "initialize", gamma_ramp_initialize, MRB_ARGS_ANY());
  mrb_define_method(mrb, mrb_glfw3_gamma_ramp_class, "get_row",    gamma_ramp_get_row,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_glfw3_gamma_ramp_class, "set_row",    gamma_ramp_set_row,    MRB_ARGS_REQ(4));
}
