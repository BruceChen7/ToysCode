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

function scanner:scan_until(pattern)
    local match
    local pos = string_find(self.tail,pattern)

    if pos == nil then
        match = self.tail
        self.pos = self.pos + #self.tail 
        self.tail = ""
    elseif  pos == 1 then
        match = nil 
    else 
        match = string_sub(self.tail,1,pos - 1)
        self.tail = string_sub(self.tail,pos)
        self.pos = self.pos + #match
    end
    return match 
end

function scanner:new(str)
    local out = {
        str = str,
        tail = str,
        pos = 1
    }
    return setmetatable(out ,{__index = self })
end

return scanner

