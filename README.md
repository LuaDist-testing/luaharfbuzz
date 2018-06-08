# _luaharfbuzz_

Lua bindings for [Harfbuzz].

[Harfbuzz]:http://harfbuzz.org

## Contents

* [Overview](#overview)
* [Installing Harfbuzz](#installing-harfbuzz)
* [Installing _luaharfbuzz_](#installing-luaharfbuzz)
* [Documentation](#documentation)
* [Sample Code](#sample-code)
* [Development](#development)
* [Contact](#contact)

## Overview
HarfBuzz is an OpenType text shaping engine. It is used in software like Qt,
Pango, Firefox, Chromium, XeTeX and LibreOffice.

_luaharfbuzz_ provides bindings for the most common types in Harfbuzz. The
initial motivation for building it is to use Harfbuzz with the [LuaTeX]
typesetting system. However, the module isn’t tied to LuaTeX in any way. It
can be used with any Lua codebase.

[LuaTeX]:luatex.org

## Installing Harfbuzz

Make sure [Harfbuzz] libraries and headers are installed. before trying to
install _luaharfbuzz_

#### OS X

Install via [Homebrew](http://brew.sh/)

```
brew install harfbuzz
```

#### Other Platforms
_Send a pull request if you want to include specific instructions to install
Harfbuzz on your preferred platform._

Before building, the Makefile looks for Harfbuzz headers and libraries using `pkg-config`. If the following commands run without errors, then it should be possible to install _luaharfbuzz_ by following instructions given in the next section.

```
pkg-config --cflags harfbuzz lua
pkg-config --libs harfbuzz
```

## Installing _luaharfbuzz_

#### Luarocks
If [Luarocks] is installed, _luaharfbuzz_ can be installed like this:

```
luarocks install luaharfbuzz
```

[Luarocks]: https://luarocks.org

#### Directly Using Makefile
See [Building](#building)

## Documentation
* [API Docs](http://deepakjois.github.io/luaharfbuzz/)
* [Wiki](http://github.com/deepakjois/luaharfbuzz/wiki)

## Sample Code

Here is some sample code, showcasing the core types and methods in the API.

```lua
local harfbuzz = require('harfbuzz')
local serpent  = require('serpent') -- luarocks install serpent

-- Harfbuzz API Version
print("Harfbuzz API version", harfbuzz.version())

-- Shapers available
print("Shapers:", serpent.line({ harfbuzz.shapers() }, {comment = false}))

-- harfbuzz.Face
local face = harfbuzz.Face.new('fonts/notonastaliq.ttf')
print('\nFace upem = '..face:get_upem())

-- harfbuzz.Font
local font = harfbuzz.Font.new(face)
local xs, xy = font:get_scale()
print("\nDefault font scale = X: "..xs..", Y: "..xy)

-- harfbuzz.Buffer
local text = "یہ" -- U+06CC U+06C1
local buf = harfbuzz.Buffer.new()
buf:add_utf8(text)

-- harfbuzz.shape (Shapes text)
print("\nShaping '"..text.."' set with Noto Nastaliq Urdu")
harfbuzz.shape(font, buf, { language = "urd", script = "Arab", direction = "rtl" })

local glyphs = buf:get_glyph_infos_and_positions()
print("No. of glyphs", #glyphs)
print(serpent.line(glyphs, {comment = false}))

local opts = { language = "eng", script = "Latn", direction = "ltr" }
local amiri_face = harfbuzz.Face.new('fonts/amiri-regular.ttf')
local amiri_font = harfbuzz.Font.new(amiri_face)

-- shaping '123' w/o features
print("\nShaping '123' set with Amiri Regular and no features")
buf= harfbuzz.Buffer.new()
buf:add_utf8("123")
harfbuzz.shape(amiri_font, buf, opts)
glyphs = buf:get_glyph_infos_and_positions()
print(serpent.line(glyphs, {comment = false}))

-- shaping '123' with '+numr' (numerators)
print("\nShaping '123' set with Amiri Regular with 'numr' feature turned on")
buf= harfbuzz.Buffer.new()
buf:add_utf8("123")
opts.features = "+numr"
harfbuzz.shape(amiri_font, buf, opts)
glyphs = buf:get_glyph_infos_and_positions()
print(serpent.line(glyphs, {comment = false}))
```

## Development

#### Building
It is possible to build _luaharfbuzz_ using the Makefile provided in the distribution. Running `make` will build the library `luaharfbuzz.so` in the root directory of the repo. The Lua source files are located under the `src` directory. To use them with Lua, you will need to update your `package.path` and `package.cpath` approrpriately.

#### Testing and Linting
In order to make changes to the code and run the tests, the following dependencies need to be installed:

* [Busted](http://olivinelabs.com/busted/) – `luarocks install busted`
* [luacheck](luacheck.readthedocs.org) – `luarocks install luacheck`

Run the test suite:
```
make spec
```

Lint the codebase:
```
make lint
```

## Contact
Open a Github issue, or email me at <deepak.jois@gmail.com>.
