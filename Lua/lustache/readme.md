## Introduction 

lustache is written by [Olivine Labs](https://github.com/Olivine-Labs),I use it to be familar with Lua usage and how to
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


## Template
A mustache template is a string that contains any number of mustache tags

### Variables

Template:

```
{{name}}
{{age}}
{{company}}
{{{company}}}
{{&company}}
```

View:

```
{
	name = "Chris",
	Company = "<b>Github</b>"	
}
```

Output:

```
* Chris
*
* &lt;b&gt;GitHub&lt;/b&gt;
* <b>Github</b>
* <b>Github</b>
```
