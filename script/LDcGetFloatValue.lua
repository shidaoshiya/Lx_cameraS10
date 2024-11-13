--打开设备方式
-- 定义枚举
--LX_OPEN_MODE = {
--    OPEN_BY_INDEX = 0,
--    OPEN_BY_IP = 1,        -- 按搜索列表中对应ip方式打开，对应的参数为设备ip或ip:port
--    OPEN_BY_SN = 2,
--    OPEN_BY_ID = 3
--}

--直接调用结构体中的字段即可
--typedef struct LxFloatValueInfo
--{
--    bool set_available;     //当前值是否可设置, true-可设置，false-不可设置
--float cur_value;        //当前值
--float max_value;        //最大值
--float min_value;        //最小值
--float reserve[4];       //预留字段
--}LxFloatValueInfo;

--功能：获取float类型参数
--参数：[in]handle                  设备句柄
--     [in]cmd                     参考LX_CAMERA_FEATURE
--     [out]value                  返回参数结构体
--LDcGetFloatValue
LxDeviceInfo = {
    handle,              --设备唯一标识
    dev_type,              --设备类型
    id,                --设备id
    ip,                --设备ip:port
    sn,                --设备序列号
    mac,               --设备mac地址
    firmware_ver,        --设备软件版本号
    algor_ver,           --设备算法版本号
    name,            --设备名称，如：camera_M3_192.168.11.13_9803
    reserve,            --预留字段, 子网掩码 //add at 20231120
    reserve2,            --预留字段2, 网关ip  //add at 20231120
    reserve3,            --预留字段3
    reserve4            --预留字段4
}
LxFloatValueInfo = {
    set_available,
    cur_value,
    max_value,
    min_value,
    reserve
}
open_mode=1
param="192.168.100.82"
handle="0"
value=1
cmd=2007  --LX_DEVICE_TEMPLATURE
result=DcOpenDevice(open_mode,param,handle,LxDeviceInfo)
if result==0 then
    print("Device run success.")
else
    print("Device run failed.")
    print("DcOpenDevice result: "..result)
end
result1=DcGetFloatValue(LxDeviceInfo.handle,cmd,LxFloatValueInfo)
if result1 ~= 0 then
    print("LDcGetFloatValue.lua run failed.")
    print("DcGetFloatValue result: "..result1)
else
    print("LDcGetFloatValue.lua run success.")
end
print("LxFloatValueInfo.set_available: "..tostring(set_available))
print("LxFloatValueInfo.cur_value: "..LxFloatValueInfo.cur_value)
print("LxFloatValueInfo.max_value: "..LxFloatValueInfo.max_value)
print("LxFloatValueInfo.min_value: "..LxFloatValueInfo.min_value)
print(LxFloatValueInfo.reserve)