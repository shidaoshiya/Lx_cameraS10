--打开设备方式
-- 定义枚举
--LX_OPEN_MODE = {
--    OPEN_BY_INDEX = 0,
--    OPEN_BY_IP = 1,        -- 按搜索列表中对应ip方式打开，对应的参数为设备ip或ip:port
--    OPEN_BY_SN = 2,
--    OPEN_BY_ID = 3
--}
--open_mode = LX_OPEN_MODE.OPEN_BY_IP

--功能：从设备读取自定义内容,无需外部分配内存，但每次调用读取前会重置上次读取时分配的内存
--参数：[in]handle             设备句柄
--     [in]start_address      起始地址，从0开始
--     [out]data              读取内存的内容，最大支持128kb内容
--     [out]data_size         读取的内容长度，最大不超过128kb
--LDcReadUserData
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
start_adress=0
data=""
data_size=0
result=DcOpenDevice(open_mode,param,handle,LxDeviceInfo)
if result ~=0 then
    print("Device run success.")
    print("DcOpenDevicer result: "..result)
else
    print("Device run failed.")
end
result1=DcReadUserData(LxDeviceInfo.handle,start_adress,data,data_size)
if result1 ~=0 then
    print("LDcReadUserData.lua run failed.")
    print("DcReadUserData result: "..result1)
else
    print("LDcReadUserData.lua run success.")
end
print("data: "..data)
print("data_size "..data_size)