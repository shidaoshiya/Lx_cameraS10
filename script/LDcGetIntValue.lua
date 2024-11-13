--打开设备方式
-- 定义枚举
--LX_OPEN_MODE = {
--    OPEN_BY_INDEX = 0,
--    OPEN_BY_IP = 1,        -- 按搜索列表中对应ip方式打开，对应的参数为设备ip或ip:port
--    OPEN_BY_SN = 2,
--    OPEN_BY_ID = 3
--}

--直接调用结构体中的字段即可
--typedef struct LxIntValueInfo
--{
--bool set_available;   //当前值是否可设置, true-可设置，false-不可设置
--int cur_value;        //当前值
--int max_value;        //最大值
--int min_value;        //最小值
--int reserve[4];       //预留字段
--}LxIntValueInfo;

--功能：获取int类型参数
--参数：[in]handle                  设备句柄
--      [in]cmd                     参考LX_CAMERA_FEATURE
--      [out]value                  返回参数结构体
--LDcGetIntValue  返回LxIntValueInfo类型的结构体参数
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
LxIntValueInfo = {
    set_available,
    cur_value,
    max_value,
    min_value,
    reserve
}
handle="0"
open_mode=1
param="192.168.100.82"  --根据IP打开相机 可以不用获取参数列表
cmd=1065
result1=-999
result1=DcOpenDevice(open_mode,param,handle,LxDeviceInfo) --获取前需要打开相机
if result1 ==0 then
    print("Device run success.")
else
    print("Device run failed.")
    print("DcOpenDevice result: "..result1)
end
result=DcGetIntValue(LxDeviceInfo.handle,cmd,LxIntValueInfo)
if result ~= 0 then
    print("LDcGetIntValue.lua run failed.")
    print("DcGetIntValue result: "..result)
else
    print("LDcGetIntValue.lua run success.")
end
print("LxIntValueInfo.set_available: "..tostring(LxIntValueInfo.set_available))
print("LxIntValueInfo.cur_value: "..LxIntValueInfo.cur_value)
print("LxIntValueInfo.max_value: "..LxIntValueInfo.max_value)
print("LxIntValueInfo.min_value: "..LxIntValueInfo.min_value)
print(LxIntValueInfo.reserve)