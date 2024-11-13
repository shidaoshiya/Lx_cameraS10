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

--功能:  设置相机IP相关参数
--      修改完之后设备列表会变化，需重新调用DcGetDeviceList接口重新获取新的设备列表
--参数：[in]handle                 设备句柄, (当未连接上设备情况下，需先通过搜索获取)
--     [in]ip                     设备IP
--     [in]netmask                子网掩码(若传空则内部默认"255.255.0.0")
--     [in]gateway                网关ip(若传空则内部默认将ip最后网段置为"1"后作为网关)
--LDcSetCameraIp
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
result=-999
result=DcOpenDevice(open_mode,param,handle,LxDeviceInfo) --设置ip前需要打开相机
if result==0 then
    print("Device run success.")
else
    print("Device run failed.")
    print("DcOpenDevice result: "..result)
end
--修改设备的信息
change_ip="192.168.100.81"   --设备ip
netmask="255.255.0.0"  --子网掩码
gateway="192.168.100.1"
result1=DcSetCameraIp(LxDeviceInfo.handle,change_ip,netmask,gateway)  --此时handle是传入的设备句柄
if result1==nil then
    print("LDcSetCameraIp.lua run failed.")
else
    print("LDcSetCameraIp.lua run success.")
    print("DcSetCameraIp result: "..result1)
end

