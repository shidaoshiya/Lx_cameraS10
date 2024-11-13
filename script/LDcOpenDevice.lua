--打开设备方式
-- 定义枚举
--LX_OPEN_MODE = {
--    OPEN_BY_INDEX = 0,
--    OPEN_BY_IP = 1,        -- 按搜索列表中对应ip方式打开，对应的参数为设备ip或ip:port
--    OPEN_BY_SN = 2,
--    OPEN_BY_ID = 3
--}

--打开后获取的相机信息，直接调用变量名即可
--typedef struct LxDeviceInfo
--{
--    DcHandle handle;               //设备唯一标识
--    LX_DEVICE_TYPE dev_type;       //设备类型
--    char id[32];                   //设备id
--    char ip[32];                   //设备ip:port
--    char sn[32];                   //设备序列号
--    char mac[32];                  //设备mac地址
--    char firmware_ver[32];         //设备软件版本号
--    char algor_ver[32];            //设备算法版本号
--    char name[32];                 //设备名称，如：camera_M3_192.168.11.13_9803
--    char reserve[32];              //预留字段, 子网掩码 //add at 20231120
--    char reserve2[32];             //预留字段2, 网关ip  //add at 20231120
--    char reserve3[64];             //预留字段3
--    char reserve4[128];            //预留字段4
--}LxDeviceInfo;

--功能：打开设备。设备打开后会独占权限，其他进程无法再打开相机。如果程序强制结束没有调用DcCloseDevice，需要等待几秒等心跳超时释放权限
--参数：[in]open_mode           打开方式, 具体说明见LX_OPEN_MODE
--     [in]param               不同的打开方式，填写不同的参数(当sdk运行在相机内部时，此处填写"127.0.0.1")
--     [out]handle             连接成功后返回的设备句柄,后续所有接口访问都依赖该handle字段
--     [out]info               连接成功后返回的相机详细信息
--LDcOpenDevice() 执行后返回一个handle和info(LxDeviceInfo结构体)
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
devnum= 0
mode=4   --LX_SERIAL_ALL
result= DcGetDeviceList(LxDeviceInfoList,devnum,mode)
if result==nil then
    print("LDcGetDeviceList.lua run failed.")
else
    print("LDcGetDeviceList.lua run success.")
    print("DcGetDeviceList result: "..result)
end
open_mode=0
param="0"
handle="0"
result1=DcOpenDevice(open_mode,param,handle,LxDeviceInfo)
if result1 ~=0 then
    print("LDcOpenDevice.lua run failed.")
    print("DcOpenDevice result: "..result1)
else
    print("LDcOpenDevice.lua run success.")
end
print("LxDeviceInfo.handle: "..LxDeviceInfo.handle)
print("LxDeviceInfo.dev_type: "..LxDeviceInfo.dev_type)
print("LxDeviceInfo.id: "..LxDeviceInfo.id)
print("LxDeviceInfo.ip: "..LxDeviceInfo.ip)
print("LxDeviceInfo.sn: "..LxDeviceInfo.sn)
print("LxDeviceInfo.mac: "..LxDeviceInfo.mac)
print("LxDeviceInfo.firmware_ver: "..LxDeviceInfo.firmware_ver)
print("LxDeviceInfo.algor_ver: "..LxDeviceInfo.algor_ver)
print("LxDeviceInfo.name: "..LxDeviceInfo.name)
print(LxDeviceInfo.reserve)
print(LxDeviceInfo.reserve2)
print(LxDeviceInfo.reserve3)
print(LxDeviceInfo.reserve4)
