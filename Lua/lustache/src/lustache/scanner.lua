local string_find,string_match,string_sub = string.find,string.match,string.sub
local scanner = {}

function scanner:eof()
    return  self.tail == ""
end

function scanner:scan(pattern)
    local match = string_match(self.tail,pattern)

    if match and string_find(self.tail,pattern) == 1 then
        self.tail = string_sub(self.tail,#match+1)
        self.pos = self.pos + #match
    end
end

--跳跃所有的文本节点，一直读到匹配的模式。返回所有的跳跃的文本。
--这里的模式一般是标签开始的字符串。`{{`
function scanner:scan_until(pattern)
    local match
    local pos = string_find(self.tail,pattern)
    --如果没有模板字符串没有开始标签，那么更新剩余的模板字符串为空
    --并且更新下一次解析模板字符开始的位置为文件末尾。
    if pos == nil then
        match = self.tail
        self.pos = self.pos + #self.tail 
        self.tail = ""
    --模板字符串就在开始，那么返回的文本就是空
    elseif  pos == 1 then
        match = nil 
    else 
        --获取{{之前的文本
        match = string_sub(self.tail,1,pos - 1)
        --更新下一次解析模板开始的位置。和字符串
        self.tail = string_sub(self.tail,pos)
        self.pos = self.pos + #match
    end
    return match 
end

-- str 是一个模板字符串比如 "{{ test }}" 
function scanner:new(str)
    local out = {
        str = str,
        tail = str,
        pos = 1
    }
    return setmetatable(out ,{__index = self })
end

return scanner

