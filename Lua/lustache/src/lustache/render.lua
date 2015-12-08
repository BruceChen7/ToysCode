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
	-- #\^/>{&=!
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
local function compile_tokens(tokens,originTemplate) 
	
	local subs = {}

	local  function subrender(i,tokens)
		if not subs[i] then
			local fn = compile_tokens(tokens,originTemplate)
			subs[i]  = function(ctx,rnd) return fn(ctx,rnd) end
		end
		return subs[i]
	end

	local function render(ctx,rnd) 
		local buf = {}
		local token,section

		for i ,token in ipairs(tokens) do
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

--tokens是一个数组，其中每个元素的类型是一个表，表中有键type，value等
local function nest_tokens(tokens)
	local tree = {}
	local collector = tree
	local sections = {}
	local token,section

	for i ,token in ipairs(tokens) do
		-- token 的type是section 和 inverted section
		if token.type == "#" or token.type =="^" then
			--添加一个新的键值tokens
			token.tokens = {}
			--添加该tokens到sections中
			sections[#sections+1] = token
			--将token添加collector中
			collector[#collector+1] = token
			--这里不知道为什么？？？
			collector = token.tokens
		-- 如果是结束section标签
		elseif token.type == "/" then
			--如果前面的section数目为空，那么提示错误。
			if #sections == 0 then
				error("Unopend section :" ..token.value)
			end
			--移除最后一个section，并返回最后一个section。
			section = table_remove(section,#sections)
			
			--如果当前section的值不等于 == token的值，那就不对了
			if not section.vaule == token.value then
				error("Unclosed section: "..section.value)
			end
			--添加了一个新的键
			section.closingTagIndex = token.startIndex
			--如果此时sections中还有section，那么说明是嵌套的section.
			if #sections > 0 then
				collector = sections[#sections].tokens
			else
				collector = tree
			end
		else
			--section中所有的token都添加到collector中
			collector[#collector+1] = token
		end
	end
	
	section = table_remove(sections,#sections)
	
	--如果还存在section
	if section then
		error("Unclosed section: "..section.value)
	end
	
	return tree
end

--tokens是一个token数组，每一个元素都有type,startIndex元素
--将tokens中单个的文本字符转成一个文本字符串
--然后返回合并后的tokens数组
local function squash_tokens(tokens)
	local out , txt = {},{}
	local txtStartIndex,txtEndIndex
	
	for _,v in iparis(tokens) do
		
		if v.type == "text" do
			-- 如果是文本字符串刚开始，那么设置文本开始的位置为当前字符的位置
			if #txt == 0 then
				txtStartIndext = v.startIndex
			end
			txt[#txt+1] = v.value
			txtEndIndex = v.endIndex
		-- 不是文本了，则txt中多个表合成一个表作为value的值
		else
			--如果之前txt表中有文本字符串了。
			-- table.concat是用来将一系列的文本或数组串联成一个字符串或数字。
			if #txt > 0 then
				out[#out + 1] = { 
					type = "text",
					value = table_concat(txt),
					startIndex = txtStartIndex,
					endIndex = txtEndIndex 
				}
				txt = {}
			end
			--不是本文，直接添加到out中即可
			out[#out+1] = v
		end
	end
	
	--最后部分仍然是文本，添加到out中。
	if #txt > 0 then
		out[#out+1] = { type = "text",value = table_concat(txt),startIndex = txtStartIndex, endIndex = txtEndIndex, }
	end
	
	return out
end

-- 创建一个上下文
local function make_context(view) 
	if not view then
		return view
	end
	return view.magic == "1235123123" and view or Context:new(view)
end

-- 创建一个render
local renderer = {}

function renderer:clear_cache()
	self.cache = {}
	sefl.partial_cache = {}
end

-- 返回的是一个函数
-- tokens是模板字符串，tags 是默认的分隔符号，比如 {{}}
-- 过程：
-- 首先将模板字符串分解成一个个token数组。这个
function renderer:compile(tokens,tags,originTemplate)
	tags = tags or self.tags
	
	--确保是字符串
	--然后将模板字符串解析成tokens
	if type(tokens) == "string" then
		tokens = self:parse(tokens,tags);
	end
	
	local fn = compile_token(tokens,originTemplate)
	
	return function(view)
		return fn(make_context(view) ,self) 
	end
end

-- template 是模板字符串
-- view 是用来填充的表。

--过程：
--首先判断template是否是字符串类型，如果不是直接报错，
-- 根据传入的第三个参数来设置partials
-- 根据模板字符串，来获取已经存入的解析函数
-- 如果没有，则编译这个模板，然后缓存解析函数
-- 然后根据调用这个解析函数，返回解析后的结果。
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
		--缓存这个模板字符串
		self.cache[template] = fn;
	end
	return fn(view)
end

function renderer:_seciton(token,context,callback,originTemplate) 
	local value = context:lookup(token.value)
	if type(value) == "table" then
		if is_array(value) then
			local buffer = ""
			for i ,v in ipairs(value) do
				buffer = buffer..callback(context:push（v),self)
			end
			return buffer
		end
		return callback(context:push(value),self)
	elseif type(value) == "function" then
		local section_text = string_sub(originTemplate,token,endIndex+1,token.closingTagIndex - 1)
		local scoped_render = function(template) 
			return self:render(template,context)
		end
		return value(section_text,scoped_render) or ""
	else
		if value then
			return callback(context,self)
		end
	end
	return ""
end

function renderer:_inverted(name,context,callback)
	local value = context:lookup(name)
	
	if value == nil or value == false or (type(value) == "table" and is_array(value) and #value == 0)  then
		return callback(context,self)
	end
	
	return ""
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
-- 返回的是解析后的token数组。
function renderer:parse(template,tags) 
	tags = tags or self.tags
	local tag_patterns = escape_tags(tags)
	local scanner = Scanner:new(template)
	local tokens = {} --token的缓存器
	local spaces = {} -- 空格字符串缓存器
	local has_tag = false
	local non_space = false -- is there a non-space char on the current line?
	
	local function strip_space()
		if has_tag and not non_space then
			while #spaces > 0 do
				table_remove(tokens,table_remove(spaces))
			end
		else 
			spaces = {}
		end
		has_tag = false
		non_space = false
		
	end
	local type ,value,chr

	while not scanner:eos() do
		--scanner.pos指定当前模板的开始位置
		local start = scanner.pos
		--一直读到{{
		-- value就是文本节点
		value = scanner:scan_until(tag_patterns[1])
		-- 如果有文本字符串。
		if value then
			--遍历文本字符串  
			for i = 1 ,#value  do
				--获取单个字符
				chr = string_sub(value,i,i)
				-- 如果是空白字符
				-- 记录在tokens中的位置
				if string_find(chr,"%s+") then
					spaces[#spaces+1] = #tokens
				else 
					non_space = true
				end
				--添加文本字符到tokens数组
				tokens[#tokens+1] = { type = "text",value = chr,startIndex = start,endIndex = scanner.pos - 1 }
				start = start + 1
				
				if chr == "\n" then
					strip_space()
				end
			end
		end  --结束对文本字符串的解析

		-- tag_pattern[1] = {{
		-- 如果没有 {{ 分隔符号
		-- 对整个模板字符串解析完成。
		if not scanner:scan(tag_pattern[1]) then
			break
		end
		--拥有{{ tag
		has_tag = true
		--type 设置为 #,/,^ 等不同的类型 
		type = scanner:scan(patterns.tag) or  "name"
		--移除template string中的空白字符串
		scanner:scan(patterns.white)
		
		--如果是类型为 "=",也就是设置分隔符号
		if type == "=" then
			--获取新的分隔符号
			value = scanner:scan_until(patterns.eq)
			scanner:scan(patterns.eq)
			scanner:scan_until(tag_patterns[2])
		--如果要设置对html不转义
		elseif type == "{"  then
			local close_pattern = "%s*}" .. tags[2]
			value = scanner:scan_until(close_pattern)
			--读取后面结束风格符号
			scanner:scan(patterns.curly)
			scanner:scan_until(tag_pattern[2])
		else
			--{{# name }}则将 type 设置为 # ,value 设置为name
			--其余类型全被读到value
			value = scan:scan_until(tag_pattern[2])
		end

		if not scanner:scan(tag_patterns[2]) then
			error("Unclosed tag at " .. scanner.pos)
		end
		
		--添加到tokens数组中
		tokens[#tokens + 1] = { type = type, value = value, startIndex = start, endIndex = scanner.pos  -1 }
		
		if type == "name" or type == "{"  or type == "&" then 
			non_space = true
		end
		--设置新的标签
		if type == "=" then
			tags = string_split(value,patterns.space)
			tag_patterns  = escape_tags(tags)
		end
	end  -- 结束对整个模板字符串的解析
	
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