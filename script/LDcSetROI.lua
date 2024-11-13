--打开设备方式
-- 定义枚举
--LX_OPEN_MODE = {
--    OPEN_BY_INDEX = 0,
--    OPEN_BY_IP = 1,        -- 按搜索列表中对应ip方式打开，对应的参数为设备ip或ip:port
--    OPEN_BY_SN = 2,
--    OPEN_BY_ID = 3
--}

--~chinese
--功能：设置ROI区域, 输入数值若不是8的整数倍,内部会自动处理为目标值最近的8的整倍数
--参数  [in]handle                  设备句柄
--     [in]offsetx                 起始点水平偏移像素
--     [in]offsety                 起始点垂直偏移参数
--     [in]width                   roi目标区域的宽
--     [in]height                  roi目标区域的高
--     [in]img_type                0-3D图像 1-2D图像
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
offsetx=0
offsety=0
width=640
height=480
img_tpye=0
result=DcOpenDevice(open_mode,param,handle,LxDeviceInfo)
if result==0 then
    print("Device run success.")
else
    print("Device run failed.")
    print("DcOpenDevice result: "..result)
end
result1=DcSetROI(handle,offsetx,offsety,width,height,img_tpye)
if result1 ~= 0 then
    print("LDcSetROI() run failed.")
else
    print("LDcSetROI() run success.")
    print("DcSetROI  result: "..result1)
end