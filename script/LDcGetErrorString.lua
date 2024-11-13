--打开设备方式
-- 定义枚举
--LX_OPEN_MODE = {
--    OPEN_BY_INDEX = 0,
--    OPEN_BY_IP = 1,        -- 按搜索列表中对应ip方式打开，对应的参数为设备ip或ip:port
--    OPEN_BY_SN = 2,
--    OPEN_BY_ID = 3
--}

--功能: 获取函数返回状态对应的说明
--参数：[in]state  函数接口返回的状态
--LDcGetErrorString
state=0
result = DcGetErrorString(state)
if result ~= 0 then
    print("LDcGetErrorString() run failed.")
    print("DcGetErrorString result"..result)
else
    print("LDcGetErrorString() run success.")
end
