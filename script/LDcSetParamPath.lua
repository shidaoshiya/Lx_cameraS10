--打开设备方式
-- 定义枚举
--LX_OPEN_MODE = {
--    OPEN_BY_INDEX = 0,
--    OPEN_BY_IP = 1,        -- 按搜索列表中对应ip方式打开，对应的参数为设备ip或ip:port
--    OPEN_BY_SN = 2,
--    OPEN_BY_ID = 3
--}

--功能：设置参数路径
--参数：[in]handle                  设备句柄
--     [in]filepath                参数文件路径，不包含文件名(大部分情况不需要调用，仅部分相型号机打开时需要参数，如M3，I2等)
--LDcSetParamPath
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
open_mode=1
param="192.168.100.82"
handle="0"
filepath="./param"
result=DcOpenDevice(open_mode,param,handle,LxDeviceInfo)
if result==0 then
    print("Device run success.")
else
    print("Device run failed.")
    print("DcOpenDevice result: "..result)
end
result1=DcSetParamPath(LxDeviceInfo.handle,filepath)
if result1 ~= 0 then
    print("LDcSetParamPath.lua run failed.")
    print("DcSetParamPath result: "..result1)
else
    print("LDcSetParamPath.lua run success.")
end
