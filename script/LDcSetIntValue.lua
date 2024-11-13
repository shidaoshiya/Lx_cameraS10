-- 定义枚举
--LX_OPEN_MODE = {
--    OPEN_BY_INDEX = 0,
--    OPEN_BY_IP = 1,        -- 按搜索列表中对应ip方式打开，对应的参数为设备ip或ip:port
--    OPEN_BY_SN = 2,
--    OPEN_BY_ID = 3
--}
--open_mode = LX_OPEN_MODE.OPEN_BY_IP

--功能: 打开数据流
--参数：[in]handle  设备句柄
--     [in]open_mode  打开方式
--     [in]param  打开参数 IP
--LDcSetIntValue
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
handle="0"
open_mode=1
param="192.168.100.82"  --根据IP打开相机
cmd=1065   --LX_INT_ALGORITHM_MODE
value=1    --MODE_AVOID_OBSTACLE2
result=-999
result=DcOpenDevice(open_mode,param,handle,LxDeviceInfo) --设置前需要打开相机
if result==0 then
    print("Device run success.")
else
    print("DcOpenDevice result: "..result)
end
result1=DcSetIntValue(LxDeviceInfo.handle,cmd,value)
if result1 ~= 0 then
    print("LDcSetIntValue.lua run failed.")
    print("DcSetIntValue result： "..result1)
else
    print("LDcSetIntValue.ua run success.")
end
