local Scanner = require 'lustache.scanner'
local Context = require 'lustache.context'

local error,ipairs,loadstring,pairs,setmetable,tostring,type = 
	  error,iparis,loadstring,pairs,setmetable,tosring, type

local math_floor,math_max,string_find,string_gsub,string_split,string_sub,table_concat,table_insert =
	  math.floor,math.max,string.find,string.gsub,string.split,string.sub,table.concat,table.insert

local table_remove = table.remove;
 
local patterns  = {
	--空白字符的匹配
	white = "%s*",
	--空格
	space = "%s+",
	-- %S表示非空白字符
	nonSpace = "%S",
	-- 等于符号的匹配
	eq = "%s*=",
	--右括号的匹配
	curly = "%s*}",
	tag = "[#\\^/>{&=!]"
}

-- 注意到字符做为表的域，是如何表示。
local html_escape_charaters  = {
	["&"] = "&amp;",
	["<"] = "&lt;",
	[">"] = "&gt;",
	['"'] = "&quot;",
	["'"]= "&#39;",
	["/"] = "&#x2F"
}

-- 判断表是否是简单的数组.
-- 如何判断？
-- 首先看array 是否是 table类型 ，注意使用type 来查看变量的类型。
-- 然后看 k 是否是 number类型，且k是否是大于0，数组在Lua中下标是从1开始的。
-- 最后看键值是否从1开始连续

local function is_array(array)
	if type(array) ~= "table" then
		return false
	end

	local max,n=0,0

	for k,_ in pairs(array) do
		if not(type(k) == "number" and k > 0 and math_floor(k) ==k) then
			return false
		end
		max = math_max(max,k)
		n = n + 1
	end
	
	return n == max
end

-- Low-level function that compiles the given 'tokens' into a
-- function that accepts two arguments: a Context and a Render
local function compiler_tokens(tokens,originTemplate) 
	local subs = {}

	local  function subrender(i,tokens)
		if not subs[i] then
			local fn = compiler_tokens(tokens,originTemplate)
			subs[i]  = function(ctx,rnd)
			return fn(ctx,rnd)
		end
		return subs[i]
	end

	local function render(ctx,rnd) 
		local buf = {}
		local token,section

		for i ,token in ipairs(token) do
			local t = token.type
			buf[#buf+1] =
			t == "#" and rnd:_section(
				token,ctx,subrender(i,token.tokens),originTemplate
			) or 
			t == "^" and rnd:_inverted(
				token.value,ctx,subrender(i,token.tokens)
			) or
			t == ">" and rnd:_partial(token.value,ctx,originTemplate) or
			(t == "{" or t == "&") and rnd:_name(token.value,ctx,false) or
			t == "name" and rnd:_name(token.value,ctx,true) or
			t == "text" and token.value or ""
		end
		return table_concat(buf)
	end
	return render
end


-- string_gsub 返回的是匹配后替换的字符串。
local function escape_tags(tags)
	return {
		string_gsub(tags[1],"%%","%%%%").."%s*",
			"%s*"..string_gsub(tags[2],"%%","%%%%"),
		)
	}
end

local function nest_tokens(tokens)
	local tree = {}
	local collector = tree
	local section = {}
	local token,section

	for i ,tokens in ipairs(tokens) do
		if token.type == "#" or token.type ==="^" then
			token.tokens = {}
			sections[#sections+1] = token
			collector[#collector+1] = token
			collector = token.tokens
		elseif token.type == "/" then
			if #sections == 0 then
				error("Unopend section :" ..token.value)
			end

			section = table_remove(section,#sections)

			if not section.vaule = token.value then
				error("Unclosed section: "..section.value)
			end

			section.closingTagIndex = token.startIndex

			if #sections > 0 then
				collector = sections[#sections].tokens
			else
				collector = tree
			end
		else
			collector[#collector+1] = token
		end
	end
	
	section = table_remove(sections,#sections)

	if section then
		error("Unclosed section: "..section.value)
	end
	return tree
end

local function squash_tokens(tokens)
	local out , txt = {},{}
	local txtStartIndex,txtEndIndex
	
	for _,v in iparis(tokens) do
		if v.type == "text" do
			if #txt ==0 then
				txtStartIndext = v.startIndex
			end
			txt[#txt+1] = v.value
			txtEndIndex = v.endIndex
		else
			if #txt > 0 then
				out[#out + 1] = { type = "text",value = table_concat(txt),startIndex = txtStartIndex,endIndex = txtEndIndex }
				txt = {}
			end
			out[#out+1] = v
		end
	end

	if #txt > 0 then
		out[#out+1] = { type = "text",value = table_concat(txt),startIndex = txtStartIndex, endIndex = txtEndIndex, }
	end
	
	return out
end


local function make_context(view) 
	if not view then
		return view
	end
	return view.magic == "1235123123" and view or Contex:new(view)
end

local renderer = {}

function renderer:clear_cache()
	self.cache = {}
	sefl.partial_cache = {}
end


function renderer:compiler(tokens,tags,originTemplate)
	tags = tags or self.tags
	if type(tokens) == "string" then
		tokens = self:parse(tokens,tags);
	end
	
	local fn = compile_token(tokens,originTemplate)
	
	return function(view)
		return fn(make_context(view) ,self)
	end

end

function renderer:render(template,view,partials) 
	if type(self) == "string" then
		error("Call mustache:render,not mustache.render!")
	end
	if partials then
		self.partials = partials
	end
	
	if not template then
		return ""
	end
	
	local fn = self.cache[template]
	
	if not fn then
		fn = self.compile(template,self.tags,template)
		self.cache[template] = fn;
	end
	return fn(view)
end

function renderer:_partial(name,context,orginTemplate) 
	local fn = self.partial_cache[name]

	--check if partial cache exists
	if (not fn and self.partials ) then
		local partial = self.partials[name]
		
		if (not partial) then
			return ""
		end

		fn = self:compile(partial,nil,originTemplate)
		self.partial_cache[name] = fn
	end
	return fn and fn(context,self) or ""
end


-- template 是一个模板字符串比如 "{{ test }}"
function renderer:parse(template,tags) 
	tags = tags or self.tags
	local tag_patterns = escape_tags(tags)
	local scanner = Scanner:new(template)
	local tokens = {}
	local spaces = {}
	local has_tag = false
	local non_space = fasle  -- is there a non-space char on the current line?

	local type ,value,chr

	while not scanner:eos() do
		--scanner.pos指定当前模板的开始位置
		local start = scanner.pos
		--一直读到{{
		-- value就是文本节点
		value = scanner:scan_until(tag_patterns[1])

		if value then
			for i = 1 ,#value  do
				chr = string_sub(value,i,i)

				if string_find(chr,"%s+") then
					spaces[#spaces +1] = #tokens
				else 
					non_space = true
				end

				tokens[#tokens+1] = {   type = "text",value = chr,startIndex = start,endIndex = scanner.pos - 1 }
				start = start + 1
			end
		end

		if not scanner:scan(tag_pattern[1]) then
			break
		end
		has_tag = true
		type = scanner:scan(pattern.tag) or  "name"

		scanner:scan(patterns.white)

		if type == "=" then
			value = scanner:scan_until(patterns.eq)
			scanner:scan(patterns.eq)
			scanner:scan_until(tag_patterns[2])
		elseif type == "{"  then
			local close_pattern = "%s*}" .. tags[2]
			value = scanner:scan_until(close_pattern)
			scanner:scan(pattern.curly)
			scanner:scan_until(tag_pattern[2])
		else
			value = scan:scan_until(tag_pattern[2])
		end

		if not scanner:scan(tag_pattern[2]) then
			error("Unclosed tag at " .. scanner.pos)
		end

		tokens[#tokens + 1] = { type = type, value = value, startIndex = start, endIndex = scanner.pos  -1 }
		
		if type == "name" or type == "{"  or type == "&" then 
			non_space = true
		end

		if type == "=" then
			tags = string_split(value,patterns.space)
			tag_patterns  = escape_tags(tags)
		end
	end
	
	return nest_token(squash_token(tokens))
end



--  renderer:new 返回的是 out表，out表继承了render表
-- 这是典型的Lua中一种表示继承关系的方式。
function renderer:new()
	local out = {
		cache = {},
		partial_cache = {},
		-- 默认使用 "{{"  "}}"作为模板的分隔符号
		tags = {"{{","}}"}
	}
	return setmetatable(out,{__index =  self })
end

return renderer