local patterns  = {
	whit = "%s*",
	space = "%s+",
	nonSpace = "%s",
	eq = "%s*=",
	curly = "%s*}",
	tag = "[#\\^/>{&=!]"
}

local html_escape_charaters  = {
	["&"] = "&amp;",
	["<"] = "&lt;",
	[">"] = "&gt;",
	['"'] = "&quot;",
	["'"]= "&#39;",
	["/"] = "&#x2F"
}

--- 判断表是否是简单的数组.
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


local function escape_tags(tags)
	return {
		string_gsub(tags[i],"%%","%%%%").."%s*",
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

local render = {}

function renderer:clear_cache()
	self.cache = {}
	sefl.partial_cache = {}
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



end


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
		local start = scanner.pos
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



function renderer:new()
	local out = {
		cache = {},
		partial_cache = {},
		tags = {"{{","}}"}
	}
	return setmetatable(out,{_index =  self })
end

return renderer