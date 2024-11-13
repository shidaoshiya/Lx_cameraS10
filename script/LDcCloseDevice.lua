-- 定义枚举
--LX_OPEN_MODE = {
--    OPEN_BY_INDEX = 0,
--    OPEN_BY_IP = 1,        -- 按搜索列表中对应ip方式打开，对应的参数为设备ip或ip:port
--    OPEN_BY_SN = 2,
--    OPEN_BY_ID = 3
--}
--open_mode = LX_OPEN_MODE.OPEN_BY_IP

--设备详细信息
--typedef struct LxDeviceInfo
--{
--DcHandle handle;               //设备唯一标识
--LX_DEVICE_TYPE dev_type;       //设备类型
--char id[32];                   //设备id
--char ip[32];                   //设备ip:port
--char sn[32];                   //设备序列号
--char mac[32];                  //设备mac地址
--char firmware_ver[32];         //设备软件版本号
--char algor_ver[32];            //设备算法版本号
--char name[32];                 //设备名称，如：camera_M3_192.168.11.13_9803
--char reserve[32];              //预留字段, 子网掩码 //add at 20231120
--char reserve2[32];             //预留字段2, 网关ip  //add at 20231120
--char reserve3[64];             //预留字段3
--char reserve4[128];            //预留字段4
--}LxDeviceInfo;

--功能: 关闭设备。与DcOpenDevice对应，释放权限和资源。
--参数：[in]handle  设备句柄
--     [in]open_mode  打开方式
--     [in]param  打开参数 IP
--LDcCloseDevice
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
LxDeviceInfoList = {
    {handle="",dev_type,id,ip,sn,mac,firmware_ver,algor_ver,name,reserve,reserve2,reserve3,reserve4},
    {handle="",dev_type,id,ip,sn,mac,firmware_ver,algor_ver,name,reserve,reserve2,reserve3,reserve4},
    {handle="",dev_type,id,ip,sn,mac,firmware_ver,algor_ver,name,reserve,reserve2,reserve3,reserve4},
    {handle="",dev_type,id,ip,sn,mac,firmware_ver,algor_ver,name,reserve,reserve2,reserve3,reserve4},
    {handle="",dev_type,id,ip,sn,mac,firmware_ver,algor_ver,name,reserve,reserve2,reserve3,reserve4},
    {handle="",dev_type,id,ip,sn,mac,firmware_ver,algor_ver,name,reserve,reserve2,reserve3,reserve4},
    {handle="",dev_type,id,ip,sn,mac,firmware_ver,algor_ver,name,reserve,reserve2,reserve3,reserve4},
    {handle="",dev_type,id,ip,sn,mac,firmware_ver,algor_ver,name,reserve,reserve2,reserve3,reserve4},
    {handle="",dev_type,id,ip,sn,mac,firmware_ver,algor_ver,name,reserve,reserve2,reserve3,reserve4},
    {handle="",dev_type,id,ip,sn,mac,firmware_ver,algor_ver,name,reserve,reserve2,reserve3,reserve4}
}
handle="0"
open_mode=0
param="0"
result1=-999
devnum= 0
mode=4   --LX_SERIAL_ALL

result= DcGetDeviceList(LxDeviceInfoList,devnum,mode)
if result == 0 then
    print("GetDeviceList success")
else
    print("LDcGetDeviceList failed")
    print("DcGetDeviceList result: "..result)
end
result1=DcOpenDevice(open_mode,param,handle,LxDeviceInfo) --关闭相机前前需要打开相机
print("Device handle: "..LxDeviceInfo.handle)
if result1 ==0 then
    print("Device run success.")
else
    print("Device run failed.")
    print("DcOpenDeivce result: "..result1)
end
result2=DcCloseDevice(LxDeviceInfo.handle)
if result2 ~= 0 then
    print("LDcCloseDevice.lua run failed.")
    print("DcClose result: "..result2)
else
    print("LDcCloseDevice.lua run success.")
end
