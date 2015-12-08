## Introduction 
lustache is written by [Olivine Labs](https://github.com/Olivine-Labs),I used to familar with Lua usage and how to
parse a Mustache template.What's more,I add some anotations to it when I read the code.Sorry,I am more familiar with
Chinese than English,so I use Chinease as the annotation language.

## Usage

```lua
local lustache = require "lustache"
view_model = {
	title = "joe",
	calc = function() 
		return  2 + 4
	end
}

out_put = lustache:render("{{title}} spends {{calc}}", view_model )
```