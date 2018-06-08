-- This file was automatically generated for the LuaDist project.

package = "luaharfbuzz"
version = "0.0.2-0"
-- LuaDist source
source = {
  tag = "0.0.2-0",
  url = "git://github.com/LuaDist-testing/luaharfbuzz.git"
}
-- Original source
-- source = {
--   url = "git://github.com/deepakjois/luaharfbuzz",
--   tag = "v0.0.2"
-- }
description = {
  summary = "Lua bindings for the Harfbuzz text shaping library",
  homepage = "https://github.com/deepakjois/luaharfbuzz",
  license = "MIT",
  maintainer = "Deepak Jois <deepak.jois@gmail.com>"
}
dependencies = {
  "lua ~> 5.2"
}
build = {
  type = "make",
  install_variables = {
    INST_LIBDIR="$(LIBDIR)",
    INST_LUADIR="$(LUADIR)",
  }
}