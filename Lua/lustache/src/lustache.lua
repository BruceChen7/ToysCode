--- 使用同一的风格将string.gmatch 用 Unix下命名的方式替代
local string_gmatch = string.gmatch

function string.split(str,sep)
    local out = {}
    for m in string_gmatch(str,"[^"..sep.."]+") do
        out[#out+1] = m
    end
    return out 
end


local lustache = {
    name = "lustache",
    version = "1.3.1", 
    renderer = require("lustache.renderer"):new(),
}

--- setmetable 将返回lustache
--- 设置lustache 表域对应的获取方式,和更新方式
return setmetatable(lustache,{ 
    __index = function(self,idx)
        if self.renderer[idx] then
            return self.renderer[idx] 
        end
    end,
    
    
    -- 当使用lunstache.tags = [[]],就是在设置模板的分割符号为[[]]
    __newindex = function(self,idx,val)
        if idx == "partials" then
            self.renderer.partials = val
        end
        if idx == "tags" then
            self.renderer.tags = val
        end
    end
 })
    
