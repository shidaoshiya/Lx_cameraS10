--设备大类，暂未使用
--typedef enum LX_DEVICE_SERIALS {
--LX_SERIAL_GIGE = 1,
--LX_SERIAL_WK,
--LX_SERIAL_OTHER,
--LX_SERIAL_ALL,
--LX_SERIAL_LOCAL_LOOP, 本地回环(用于区分SDK与相机端程序运行在同一主机上的情况)
--}LX_DEVICE_SERIALS;

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

--功能：查找支持的相机
--参数：[out]LDcGetDeviceList   返回的相机信息
--参数  [out]devlist            查找到的相机列表
--参数  [out]devnum             查找到的相机数量
--LDcGetDeviceList() 执行后返回一个devlist(LxDeviceInfo结构体) 无需实现结构体直接调用结构体中的字段即可 如print(handle) print(id)等
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
if result ~=0 then
    print("LDcGetDeviceList.lua run failed.")
    print("DcGetdDeviceList result: "..result)
else
    print("LDcGetDeviceList.lua run success.")
end
print("Device handle: "..LxDeviceInfoList[1].handle)
print("Device dev_type: "..LxDeviceInfoList[1].dev_type)
print("Devic id: "..LxDeviceInfoList[1].id)
print("Device ip: "..LxDeviceInfoList[1].ip)
print("Device sn: "..LxDeviceInfoList[1].sn)
print("Device mac: "..LxDeviceInfoList[1].mac)
print("Device firmware: "..LxDeviceInfoList[1].firmware_ver)
print("Device algor_ver: "..LxDeviceInfoList[1].algor_ver)
print("Device name: "..LxDeviceInfoList[1].name)
print("Device reserve: "..LxDeviceInfoList[1].reserve)
print(LxDeviceInfoList[1].reserve2)
print(LxDeviceInfoList[1].reserve3)
print(LxDeviceInfoList[1].reserve4)
--print("Device2 hanlde: "..LxDeviceInfoList[2].handle)
--print("Device2 dev_type: "..LxDeviceInfoList[2].dev_type)
--print("Device2 name: "..LxDeviceInfoList[2].name)