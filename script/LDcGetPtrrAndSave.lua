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
if result ~= 0 then
    print("LDcGetDeviceList.lua run failed.")
    print("DcGetDeviceList result: "..result)
else
    print("LDcGetDeviceList.lua run success.")
end
open_mode=0
param="0"
handle="0"
result1=DcOpenDevice(open_mode,param,handle,LxDeviceInfo)
if result1 ~=0 then
    print("LDcOpenDevice.lua run failed.")
    print("LDcOpenDevice result: "..result1)
else
    print("LDcOpenDevice.lua run success.")
end
result2 = DcGetPtrValueAndSave(LxDeviceInfo.handle,6001);
if result2 ~= 0 then
    print("DcGetPtrValueAndSave run failed")
    print("DcGetPtrValueAndSave result: "..result2)
else
    print("LDcGetPtrValueAndSave run success")
end

