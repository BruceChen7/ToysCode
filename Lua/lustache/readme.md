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