local string_find,string_split,tostring,type = string.find string.split,tostring,type
local context = {}
context.__index = context

-- Lua中一种面向对象的方式
function context:clean_cache()
    self.cache = {}
end

function context:push(view)
    return self.new(view,self)
end

--该函数根据提供的标签名获取对应view中的值
function context:lookup(name)
    local value = self.cache[name]
    --在缓存中存在。
    if not value then
        if name == "." then
            value = self.view
        else
            
            local context = self

            while context do 
            
                -- 对应的template是 {{name.first}} {{name.last}} {{age}}
                --[[
                    view是 
                    {
                        name = {
                            first = "Michael",
                            last = "Jackson"        
                        }
                        age = "RIP"
                    }
                    
                }}--]]
                
                --如果标签的名字包含.那么说明就是上面的template的形式
                --string.find返回的是第一个匹配.的索引
                if string_find(name,".") > 0 then
                    --返回一个名字数组
                    local names = string_split(name,".")
                    local i = 0
                    --获取整个view表
                    value = context.view

                    if(type(value) == "number") then
                        value = tostring(value)
                    end
                    
                    --一层层的遍历，获取最后对应的值
                    while value and i < #names do
                        i = i + 1
                        value = value[names[i]]
                    end
                else
                    --其余情况，直接返回键对应的值
                    value = context.view[name]
                end

                if value then
                    break
                end
                context = context.parent
            end -- 结束while 循环
        end 
        -- 缓存该标签对应的值
        self.cache[name] = value
    end
    --返回渲染后的值
    return value
end

-- 创建一个上下文,view是一个table，parent的是模板字符串
-- 比如 { person = false,name = "Chris"}
function context:new(view,parent)
    local out = {
        view = view,
        parent = parent,
        cache = {},
    }
    return setmetatable(out,{__index = self })
end

-- 这是Lua 中典型的引入一个包的方式
return context 
