local string_find,string_split,tostring,type = string.find string.split,tostring,type
local context = {}

-- Lua中一种面向对象的方式
function context:clean_cache()
    self.cache = {}
end

function context:push(view)
    return self.new(view,self)
end

function context:lookup(name)
    local value = self.cache[name]

    if not value then
        if name == "." then
            value = self.view
        else
            local context = self

            while context do 
                if string_find(name,".") > 0 then
                    local names = string_split(name,".")
                    local i = 0

                    value = context.view

                    if(type(value) == "number") then
                        value = tostring(value)
                    end
                    
                    while value and i < #names do
                        i = i + 1
                        value = value[name[i]]
                    end
                else
                    value = context.view[name]
                end

                if value then
                    break
                end
                context = context.parent
            end
        end
        self.cache[name] = value
    end
    return value
end


function context:new(view,parent)
    local out = {
        view = view,
        parent = parent,
        cache = {}
        magic = "1235123123" 
    }
    return setmetatable(out,{__index = self })
end

-- 这是Lua 中典型的引入一个包的方式
return context 
