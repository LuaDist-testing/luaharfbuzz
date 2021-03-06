#include "luaharfbuzz.h"

int shape_full (lua_State *L) {
  Font *font = (Font *)luaL_checkudata(L, 1, "harfbuzz.Font");
  Buffer *buf = (Buffer *)luaL_checkudata(L, 2, "harfbuzz.Buffer");
  luaL_checktype(L, 3, LUA_TTABLE);

  lua_len (L, 3);
  unsigned int num_features = luaL_checkinteger(L, 4);
  lua_pop(L, 1);

  Feature *features = (Feature *) malloc (num_features * sizeof(hb_feature_t));

  lua_pushnil(L); int i = 0;
  while (lua_next(L, 3) != 0) {
    Feature* f = (Feature *)luaL_checkudata(L, -1, "harfbuzz.Feature");
    features[i++] = *f;
    lua_pop(L, 1);
  }

  // Shape text
  hb_shape_full(*font, *buf, features, num_features, NULL);

  free(features);

  return 0;
}

int version (lua_State *L) {
  lua_pushstring(L, hb_version_string());
  return 1;
}

int list_shapers (lua_State *L) {
  const char **shaper_list = hb_shape_list_shapers ();
  int i = 0;

  for (; *shaper_list; shaper_list++) {
    i++;
    lua_pushstring(L, *shaper_list);
  }
  return i;
}

static const struct luaL_Reg lib_table [] = {
  {"shape_full", shape_full},
  {"version", version},
  {"shapers", list_shapers},
  {NULL, NULL}
};

int luaopen_luaharfbuzz (lua_State *L) {
  lua_newtable(L);

  register_blob(L);
  lua_setfield(L, -2, "Blob");

  register_face(L);
  lua_setfield(L, -2, "Face");

  register_font(L);
  lua_setfield(L, -2, "Font");

  register_buffer(L);
  lua_setfield(L, -2, "Buffer");

  register_feature(L);
  lua_setfield(L, -2, "Feature");

  register_tag(L);
  lua_setfield(L, -2, "Tag");

  register_script(L);
  lua_setfield(L, -2, "Script");

  register_direction(L);
  lua_setfield(L, -2, "Direction");

  register_language(L);
  lua_setfield(L, -2, "Language");

  register_unicode(L);
  lua_setfield(L, -2, "unicode");

  luaL_setfuncs(L, lib_table,0);

  return 1;
}

